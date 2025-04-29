/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/common/properties/text_style.h"
#include "base/geometry/dimension.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double DEFAULT_DOUBLE = 1.0;
const double ZERO_DOUBLE = 0.0;

const Dimension DIMENSION_PX(DEFAULT_DOUBLE, DimensionUnit::PX);
const Dimension DIMENSION_VP(DEFAULT_DOUBLE, DimensionUnit::VP);
const Dimension DIMENSION_FP(DEFAULT_DOUBLE, DimensionUnit::FP);
const Dimension DIMENSION_LPX(DEFAULT_DOUBLE, DimensionUnit::LPX);
const Dimension DIMENSION_PCT(DEFAULT_DOUBLE, DimensionUnit::PERCENT);
const Dimension DIMENSION_AUTO(DEFAULT_DOUBLE, DimensionUnit::AUTO);
const Dimension DIMENSION_CALC(DEFAULT_DOUBLE, DimensionUnit::CALC);
const Dimension DIMENSION_NONE(DEFAULT_DOUBLE, DimensionUnit::NONE);

const std::string DIMENSION_PX_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("px");
const std::string DIMENSION_VP_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("vp");
const std::string DIMENSION_FP_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("fp");
const std::string DIMENSION_LPX_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("lpx");
const std::string DIMENSION_PCT_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE * 100).append("%");
const std::string DIMENSION_AUTO_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("auto");
const std::string DIMENSION_NONE_STR = StringUtils::DoubleToString(DEFAULT_DOUBLE).append("none");
} // namespace

class DimensionTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: DimensionTest001
 * @tc.desc: Test the function ConvertToVp of the class Dimension.
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ConvertToVp of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE or ZERO_DOUBLE
     */
    EXPECT_DOUBLE_EQ(DIMENSION_PX.ConvertToVp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_VP.ConvertToVp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_FP.ConvertToVp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_LPX.ConvertToVp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_PCT.ConvertToVp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_AUTO.ConvertToVp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_CALC.ConvertToVp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_NONE.ConvertToVp(), DEFAULT_DOUBLE);
}

/**
 * @tc.name: DimensionTest002
 * @tc.desc: Test the function ConvertToPx of the class Dimension.
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ConvertToPx of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE or ZERO_DOUBLE.
     */
    EXPECT_DOUBLE_EQ(DIMENSION_PX.ConvertToPx(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_VP.ConvertToPx(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_FP.ConvertToPx(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_LPX.ConvertToPx(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_PCT.ConvertToPx(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_AUTO.ConvertToPx(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_CALC.ConvertToPx(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_NONE.ConvertToPx(), DEFAULT_DOUBLE);
}

/**
 * @tc.name: DimensionTest003
 * @tc.desc: Test the function ToString of the class Dimension.
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ToString of the class Dimension.
     * @tc.expected: The return values are equal to DIMENSION_STR of PX, VP, FP, LPX, PCT and AUTO.
     */
    EXPECT_EQ(DIMENSION_PX.ToString(), DIMENSION_PX_STR);
    EXPECT_EQ(DIMENSION_VP.ToString(), DIMENSION_VP_STR);
    EXPECT_EQ(DIMENSION_FP.ToString(), DIMENSION_FP_STR);
    EXPECT_EQ(DIMENSION_LPX.ToString(), DIMENSION_LPX_STR);
    EXPECT_EQ(DIMENSION_PCT.ToString(), DIMENSION_PCT_STR);
    EXPECT_EQ(DIMENSION_AUTO.ToString(), DIMENSION_AUTO_STR);
    Dimension dimension(DEFAULT_DOUBLE);
    dimension.SetUnit(static_cast<DimensionUnit>(7));
    EXPECT_EQ(dimension.ToString(), DIMENSION_PX_STR);
    dimension.SetUnit(DimensionUnit::NONE);
    EXPECT_EQ(dimension.ToString(), DIMENSION_NONE_STR);
}

/**
 * @tc.name: DimensionTest004
 * @tc.desc: Test the function NormalizeToPx of the class Dimension with -DEFAULT_DOUBLE.
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function NormalizeToPx of the class Dimension with DIMENSION_PX.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    double result = 0;
    EXPECT_TRUE(DIMENSION_PX.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps2: Test the function NormalizeToPx of the class Dimension with DIMENSION_VP.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_VP.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps3: Test the function NormalizeToPx of the class Dimension with DIMENSION_FP.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_FP.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps4: Test the function NormalizeToPx of the class Dimension with DIMENSION_LPX.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_LPX.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps5: Test the function NormalizeToPx of the class Dimension with DIMENSION_PCT.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_PCT.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps6: Test the function NormalizeToPx of the class Dimension with DIMENSION_AUTO.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_AUTO.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps7: Test the function NormalizeToPx of the class Dimension with DIMENSION_CALC.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(
        DIMENSION_CALC.NormalizeToPx(-DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, -DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);
}

/**
 * @tc.name: DimensionTest005
 * @tc.desc: Test the function NormalizeToPx of the class Dimension with DEFAULT_DOUBLE.
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function NormalizeToPx of the class Dimension with DIMENSION_PX.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    double result = 0;
    EXPECT_TRUE(DIMENSION_PX.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps2: Test the function NormalizeToPx of the class Dimension with DIMENSION_VP.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    result = 0;
    EXPECT_TRUE(DIMENSION_VP.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps3: Test the function NormalizeToPx of the class Dimension with DIMENSION_FP.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    result = 0;
    EXPECT_TRUE(DIMENSION_FP.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps4: Test the function NormalizeToPx of the class Dimension with DIMENSION_LPX.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    result = 0;
    EXPECT_TRUE(DIMENSION_LPX.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps5: Test the function NormalizeToPx of the class Dimension with DIMENSION_PCT.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE.
     */
    result = 0;
    EXPECT_TRUE(DIMENSION_PCT.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, DEFAULT_DOUBLE);

    /**
     * @tc.steps6: Test the function NormalizeToPx of the class Dimension with DIMENSION_AUTO.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(DIMENSION_AUTO.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);

    /**
     * @tc.steps7: Test the function NormalizeToPx of the class Dimension with DIMENSION_CALC.
     * @tc.expected: The return values are equal to ZERO_DOUBLE.
     */
    result = 0;
    EXPECT_FALSE(DIMENSION_CALC.NormalizeToPx(DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, DEFAULT_DOUBLE, result));
    EXPECT_DOUBLE_EQ(result, ZERO_DOUBLE);
}

/**
 * @tc.name: DimensionTest006
 * @tc.desc: ConvertToFp().
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ConvertToFp of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE or ZERO_DOUBLE
     */
    EXPECT_DOUBLE_EQ(DIMENSION_PX.ConvertToFp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_VP.ConvertToFp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_FP.ConvertToFp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_LPX.ConvertToFp(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_PCT.ConvertToFp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_AUTO.ConvertToFp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_CALC.ConvertToFp(), ZERO_DOUBLE);
    EXPECT_DOUBLE_EQ(DIMENSION_NONE.ConvertToFp(), DEFAULT_DOUBLE);
}

/**
 * @tc.name: DimensionTest007
 * @tc.desc: FromString().
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function FromString of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE or ZERO_DOUBLE
     */
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_PX_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_VP_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_FP_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_LPX_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_PCT_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString(DIMENSION_AUTO_STR).Value(), DEFAULT_DOUBLE);
    EXPECT_DOUBLE_EQ(Dimension::FromString("").Value(), ZERO_DOUBLE);
}

/**
 * @tc.name: DimensionTest008
 * @tc.desc: ConvertToPxWithSize().
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest008, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ConvertToPxWithSize of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE * size.
     */
    Dimension dimension(DEFAULT_DOUBLE, DimensionUnit::PERCENT);
    EXPECT_DOUBLE_EQ(dimension.ConvertToPxWithSize(5.0), DEFAULT_DOUBLE * 5.0);
    dimension.SetUnit(DimensionUnit::PX);
    EXPECT_DOUBLE_EQ(dimension.ConvertToPxWithSize(5.0), DEFAULT_DOUBLE);
}

/**
 * @tc.name: DimensionTest009
 * @tc.desc: ConvertToPxDistribute().
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest009, TestSize.Level1)
{
    /**
     * @tc.steps1: Test the function ConvertToPxDistribute of the class Dimension.
     * @tc.expected: The return values are equal to DEFAULT_DOUBLE * size.
     */
    TextStyle textStyle;
    auto defaultFp = DIMENSION_FP.ConvertToPxDistribute(textStyle.GetMaxFontScale(), textStyle.GetMinFontScale());
    EXPECT_DOUBLE_EQ(defaultFp, DEFAULT_DOUBLE);
}
} // namespace OHOS::Ace
