/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float PERCENT_REFERENCE = 1.0;
constexpr float TEST_VALUE = 30.0;
constexpr bool USING_MAX_SIZE_TRUE = true;
constexpr bool USING_MAX_SIZE_FALSE = false;
const Dimension WIDTH { 50.0, DimensionUnit::PX };
const Dimension HEIGHT { 100.0, DimensionUnit::PX };
const Dimension CALC_TEST { 10.0, DimensionUnit::CALC };
const Dimension BORDER_WIDTH_PX { 10.0, DimensionUnit::PX };
const Dimension BORDER_WIDTH_VP { 10.0, DimensionUnit::VP };
const CalcSize TEST_CALC_SIZE { NG::CalcLength(WIDTH), NG::CalcLength(HEIGHT) };
const CalcLength CALC_LENGTH_WIDTH_PX { 20.0, DimensionUnit::PX };
const CalcLength CALC_LENGTH_CALC { 10.0, DimensionUnit::CALC };
const CalcLength PADDING_LENGTH_PX { 10.0, DimensionUnit::PX };
const CalcLength PADDING_LENGTH_VP { 10.0, DimensionUnit::VP };
const SizeF TEST_SIZE { 50.0, 50.0 };
const SizeF TEST_MIN_SIZE { 10.0, 10.0 };
const SizeF TEST_SELF_SIZE = { 1.0, 1.0 };
SizeF TEST_MAX_SIZE { 100.0, 100.0 };
SizeF ADD_SIZE = { 10.0, 10.0 };
SizeF AXIS_SIZE = { 20.0, 10.0 };
SizeF CHILDREN_SIZE = { 10, 20 };
const OffsetF TEST_OFFSET = { 10.0, 20.0 };
OptionalSizeF TEST_OPTIONAL_SIZE = { 10.0, 10.0 };
const PaddingPropertyF TEST_PROPERTY { 10.0, 10.0, 10.0, 10.0 };
PaddingPropertyF PADDING_PROPERTY = { 0, 0, 0, 0 };
PaddingPropertyF TEST_PADDING_PROPERTY = { 0, 0, 0, 0 };
const BorderWidthPropertyF BORDER_WIDTH_PROPERTY { 10.0, 10.0, 10.0, 10.0 };
const Axis AXIS_HORIZONTAL = Axis::HORIZONTAL;
const Axis AXIS_VERTICAL = Axis::VERTICAL;
const MeasureType MEASURE_TYPE_MATCH_PARENT = MeasureType::MATCH_PARENT;
const MeasureType MEASURE_TYPE_MATCH_CONTENT = MeasureType::MATCH_CONTENT;
const MeasureType MEASURE_TYPE_CROSS_AXIS = MeasureType::MATCH_PARENT_CROSS_AXIS;
const MeasureType MEASURE_TYPE_MAIN_AXIS = MeasureType::MATCH_PARENT_MAIN_AXIS;
} // namespace
class MeasureUtilsTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: MeasureUtilsTestNg001
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();

    /**
     * @tc.steps: step2. call ConvertToSize and set input size is TEST_SIZE.
     * @tc.expected: the return size is the same as TEST_SIZE.
     */
    SizeF retSize = ConvertToSize(TEST_CALC_SIZE, std::move(scaleProperty), TEST_SIZE);
    EXPECT_EQ(retSize.width_, WIDTH.value_);
    EXPECT_EQ(retSize.height_, HEIGHT.value_);
}

/**
 * @tc.name: MeasureUtilsTestNg002
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();

    /**
     * @tc.steps: step2. call ConvertToOptionalSize and set input size is TEST_SIZE.
     * @tc.expected: the return size is the same as TEST_SIZE.
     */
    OptionalSizeF retSize = ConvertToOptionalSize(TEST_CALC_SIZE, std::move(scaleProperty), TEST_SIZE);
    EXPECT_EQ(retSize.width_, WIDTH.value_);
    EXPECT_EQ(retSize.height_, HEIGHT.value_);
}

/**
 * @tc.name: MeasureUtilsTestNg003
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();

    /**
     * @tc.steps: step2. call ConvertToPx and set input value is CALC_LENGTH_WIDTH.
     * @tc.expected: the return size is the same as input value.
     */
    std::optional<float> retSize = ConvertToPx(CALC_LENGTH_WIDTH_PX, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, CALC_LENGTH_WIDTH_PX.dimension_.value_);

    /**
     * @tc.steps: step3. call ConvertToPx and set input value is CALC_LENGTH_CALC.
     * @tc.expected: the return value is nullopt.
     */
    retSize = ConvertToPx(CALC_LENGTH_CALC, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNg004
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testCalcSize.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    std::optional<CalcLength> testCalcSize;

    /**
     * @tc.steps: step2. call ConvertToPx and set input value is null.
     * @tc.expected: the return value is nullopt.
     */
    std::optional<float> retSize = ConvertToPx(testCalcSize, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, std::nullopt);

    /**
     * @tc.steps: step3. call ConvertToPx and set input value is CALC_LENGTH_CALC.
     * @tc.expected: the return value is nullopt.
     */
    testCalcSize = std::make_optional<CalcLength>(CALC_TEST);
    retSize = ConvertToPx(testCalcSize, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNg005
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();

    /**
     * @tc.steps: step2. call ConvertToPx and set input value is WIDTH.
     * @tc.expected: the return value is the same as WIDTH.value_.
     */
    std::optional<float> retSize = ConvertToPx(WIDTH, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, WIDTH.value_);

    /**
     * @tc.steps: step3. call ConvertToPx and set input value is CALC_TEST.
     * @tc.expected: the return value is nullopt.
     */
    retSize = ConvertToPx(CALC_TEST, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNg006
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConstrainSize.
     * @tc.expected: the return value is the same as TEST_SIZE.
     */
    SizeF retSize = ConstrainSize(TEST_SIZE, TEST_MIN_SIZE, TEST_MAX_SIZE);
    EXPECT_EQ(retSize, TEST_SIZE);

    /**
     * @tc.steps: step2. call ConstrainSize and set TEST_MIN_SIZE.width_ is 0.
     * @tc.expected: the return value is the same as TEST_SIZE.
     */
    TEST_MAX_SIZE = { 0, 0 };

    retSize = ConstrainSize(TEST_SIZE, TEST_MIN_SIZE, TEST_MAX_SIZE);
    EXPECT_EQ(retSize, TEST_SIZE);
}

/**
 * @tc.name: MeasureUtilsTestNg007
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;

    /**
     * @tc.steps: step2. call ConvertToMarginPropertyF and set input margin is null.
     */
    std::unique_ptr<MarginProperty> testMarginProperty = nullptr;
    PaddingPropertyF retProperty =
        ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), PERCENT_REFERENCE);

    /**
     * @tc.steps: step3. set testMarginProperty is not null.
     */
    testPadding.left = PADDING_LENGTH_PX;
    testPadding.right = PADDING_LENGTH_PX;
    testPadding.top = PADDING_LENGTH_PX;
    testPadding.bottom = PADDING_LENGTH_PX;
    testMarginProperty = std::make_unique<MarginProperty>(std::move(testPadding));

    /**
     * @tc.steps: step4. call ConvertToMarginPropertyF.
     * @tc.expected: the return value is the same as TEST_PROPERTY.
     */
    retProperty = ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty, TEST_PROPERTY);
}

/**
 * @tc.name: MeasureUtilsTestNg008
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;

    /**
     * @tc.steps: step2. set testMarginProperty is not null.
     */
    testPadding.left = PADDING_LENGTH_PX;
    testPadding.right = PADDING_LENGTH_PX;
    testPadding.top = PADDING_LENGTH_PX;
    testPadding.bottom = PADDING_LENGTH_PX;
    MarginProperty testMarginProperty = testPadding;

    /**
     * @tc.steps: step3. call ConvertToMarginPropertyF and set input margin is PaddingProperty.
     * @tc.expected: the return value is the same as TEST_PROPERTY.
     */
    PaddingPropertyF retProperty =
        ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty, TEST_PROPERTY);
}

/**
 * @tc.name: MeasureUtilsTestNg009
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;

    /**
     * @tc.steps: step2. call ConvertToBorderWidthPropertyF and set input borderWidth is null.
     */
    std::unique_ptr<BorderWidthProperty> testBorderWidthProperty = nullptr;
    BorderWidthPropertyF retProperty =
        ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), PERCENT_REFERENCE);

    /**
     * @tc.steps: step3. set testBorderWidthProperty is not null.
     */
    BorderWidthPropertyT<Dimension> testPropertyT;

    testPropertyT.leftDimen = BORDER_WIDTH_PX;
    testPropertyT.rightDimen = BORDER_WIDTH_PX;
    testPropertyT.topDimen = BORDER_WIDTH_PX;
    testPropertyT.bottomDimen = BORDER_WIDTH_PX;

    testBorderWidthProperty = std::make_unique<BorderWidthProperty>(std::move(testPropertyT));

    /**
     * @tc.steps: step4. call ConvertToMarginPropertyF.
     * @tc.expected: the return value is the same as BORDER_WIDTH_PROPERTY.
     */
    retProperty = ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty, BORDER_WIDTH_PROPERTY);
}

/**
 * @tc.name: MeasureUtilsTestNg010
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;

    /**
     * @tc.steps: step2. call ConvertToBorderWidthPropertyF and set borderWidth Dimension is null.
     * @tc.expected: the return value is std::nullopt.
     */
    BorderWidthPropertyT<Dimension> testPropertyT;

    std::unique_ptr<BorderWidthProperty> testBorderWidthProperty =
        std::make_unique<BorderWidthProperty>(std::move(testPropertyT));
    BorderWidthPropertyF retProperty =
        ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty.leftDimen, std::nullopt);

    /**
     * @tc.steps: step3. set testPropertyT DimensionUnit is VP.
     */
    testPropertyT.leftDimen = BORDER_WIDTH_VP;
    testPropertyT.rightDimen = BORDER_WIDTH_VP;
    testPropertyT.topDimen = BORDER_WIDTH_VP;
    testPropertyT.bottomDimen = BORDER_WIDTH_VP;

    testBorderWidthProperty = std::make_unique<BorderWidthProperty>(std::move(testPropertyT));

    /**
     * @tc.steps: step4. call ConvertToBorderWidthPropertyF.
     * @tc.expected: the return value is the same as BORDER_WIDTH_PROPERTY.
     */
    retProperty = ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty, BORDER_WIDTH_PROPERTY);

    /**
     * @tc.steps: step5. set testPropertyT.leftDimen is CALC_TEST and call ConvertToBorderWidthPropertyF.
     * @tc.expected: retProperty.leftDimen is std::nullopt.
     */
    testPropertyT.leftDimen = CALC_TEST;
    testBorderWidthProperty = std::make_unique<BorderWidthProperty>(std::move(testPropertyT));
    retProperty = ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), PERCENT_REFERENCE);
    EXPECT_EQ(retProperty.leftDimen, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNg011
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;

    /**
     * @tc.steps: step2. call UpdatePaddingPropertyF and set input Padding is null.
     * @tc.expected: testPaddingPropertyF is not update.
     */
    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), TEST_SELF_SIZE, PADDING_PROPERTY);
    EXPECT_EQ(PADDING_PROPERTY, TEST_PADDING_PROPERTY);

    /**
     * @tc.steps: step3. set testPadding.left is PADDING_LENGTH_PX.
     */
    testPadding.left = PADDING_LENGTH_PX;
    testPadding.right = PADDING_LENGTH_PX;
    testPadding.top = PADDING_LENGTH_PX;
    testPadding.bottom = PADDING_LENGTH_PX;
    TEST_PADDING_PROPERTY = { 10.0, 10.0, 10.0, 10.0 };

    /**
     * @tc.steps: step2. call UpdatePaddingPropertyF and set input Padding is not null.
     * @tc.expected: step2. testPaddingPropertyF is update and it value is the same as testPadding.
     */
    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), TEST_SELF_SIZE, PADDING_PROPERTY);
    EXPECT_EQ(PADDING_PROPERTY, TEST_PADDING_PROPERTY);
}

/**
 * @tc.name: MeasureUtilsTestNg012
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scaleProperty and testPadding.
     */
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    PaddingProperty testPadding;
    PADDING_PROPERTY = { 0, 0, 0, 0 };
    TEST_PADDING_PROPERTY = { 10.0, 10.0, 10.0, 10.0 };

    /**
     * @tc.steps: step2. set testPadding.left is PADDING_LENGTH_VP.
     */
    testPadding.left = PADDING_LENGTH_VP;
    testPadding.right = PADDING_LENGTH_VP;
    testPadding.top = PADDING_LENGTH_VP;
    testPadding.bottom = PADDING_LENGTH_VP;

    /**
     * @tc.steps: step3. call UpdatePaddingPropertyF and set input Padding DimensionUnit is VP.
     * @tc.expected: testPaddingPropertyF is not update.
     */
    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), TEST_SELF_SIZE, PADDING_PROPERTY);
    EXPECT_EQ(PADDING_PROPERTY, TEST_PADDING_PROPERTY);
}

/**
 * @tc.name: MeasureUtilsTestNg013
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call AddPaddingToSize and set input Padding is zero.
     * @tc.expected: the testSize is not changed.
     */
    PADDING_PROPERTY = { 0, 0, 0, 0 };

    AddPaddingToSize(PADDING_PROPERTY, ADD_SIZE);
    EXPECT_EQ(ADD_SIZE.width_, 10.0);
    EXPECT_EQ(ADD_SIZE.height_, 10.0);

    /**
     * @tc.steps: step2. call AddPaddingToSize and set input Padding is not zero.
     * @tc.expected: the testSize is changed into expected values.
     */
    PADDING_PROPERTY = { 10.0, 20.0, 30.0, 40.0 };

    AddPaddingToSize(PADDING_PROPERTY, ADD_SIZE);
    EXPECT_EQ(ADD_SIZE.width_, 40.0);
    EXPECT_EQ(ADD_SIZE.height_, 80.0);
}

/**
 * @tc.name: MeasureUtilsTestNg014
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call MinusPaddingToSize and set input Padding is zero.
     * @tc.expected: the testSize is not changed.
     */
    PADDING_PROPERTY = { 0, 0, 0, 0 };
    ADD_SIZE = { 100.0, 100.0 };

    MinusPaddingToSize(PADDING_PROPERTY, ADD_SIZE);
    EXPECT_EQ(ADD_SIZE.width_, 100.0);
    EXPECT_EQ(ADD_SIZE.height_, 100.0);

    /**
     * @tc.steps: step2. call MinusPaddingToSize and set input Padding is not zero.
     * @tc.expected: the testSize is changed into expected values.
     */
    PADDING_PROPERTY = { 10.0, 20.0, 30.0, 40.0 };

    MinusPaddingToSize(PADDING_PROPERTY, ADD_SIZE);
    EXPECT_EQ(ADD_SIZE.width_, 70.0);
    EXPECT_EQ(ADD_SIZE.height_, 30.0);
}

/**
 * @tc.name: MeasureUtilsTestNg015
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call AddPaddingToSize and set input Padding is zero.
     * @tc.expected: the testOptionalSize is not changed.
     */
    PADDING_PROPERTY = { 0, 0, 0, 0 };

    AddPaddingToSize(PADDING_PROPERTY, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 10.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 10.0);

    /**
     * @tc.steps: step2. call AddPaddingToSize and set input Padding is not zero.
     * @tc.expected: the testOptionalSize is changed into expected values.
     */
    PADDING_PROPERTY = { 40.0, 30.0, 20.0, 10.0 };

    AddPaddingToSize(PADDING_PROPERTY, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 80.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 40.0);
}

/**
 * @tc.name: MeasureUtilsTestNg016
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call MinusPaddingToSize and set input Padding is zero.
     * @tc.expected: the testOptionalSize is not changed.
     */
    PADDING_PROPERTY = { 0, 0, 0, 0 };
    TEST_OPTIONAL_SIZE = { 100.0, 100.0 };

    MinusPaddingToSize(PADDING_PROPERTY, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 100.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 100.0);

    /**
     * @tc.steps: step2. call MinusPaddingToSize and set input Padding is not zero.
     * @tc.expected: the testOptionalSize is changed into expected values.
     */
    PADDING_PROPERTY = { 40.0, 30.0, 20.0, 10.0 };

    MinusPaddingToSize(PADDING_PROPERTY, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 30.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 70.0);
}

/**
 * @tc.name: MeasureUtilsTestNg017
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisOffset and set input Axis is HORIZONTAL.
     * @tc.expected: the return value is equal to TEST_OFFSET.x_.
     */
    float retMainOffset = GetMainAxisOffset(TEST_OFFSET, AXIS_HORIZONTAL);
    EXPECT_EQ(retMainOffset, TEST_OFFSET.x_);

    /**
     * @tc.steps: step2. call GetMainAxisOffset and set input Axis is HORIZONTAL.
     * @tc.expected: the return value is equal to TEST_OFFSET.y_.
     */
    retMainOffset = GetMainAxisOffset(TEST_OFFSET, AXIS_VERTICAL);
    EXPECT_EQ(retMainOffset, TEST_OFFSET.y_);
}

/**
 * @tc.name: MeasureUtilsTestNg018
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: the return value is equal to AXIS_SIZE.Width.
     */
    float retMainSize = GetMainAxisSize(AXIS_SIZE, AXIS_HORIZONTAL);
    EXPECT_EQ(retMainSize, AXIS_SIZE.width_);

    /**
     * @tc.steps: step2. call GetMainAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: the return value is equal to AXIS_SIZE.Height.
     */
    retMainSize = GetMainAxisSize(AXIS_SIZE, AXIS_VERTICAL);
    EXPECT_EQ(retMainSize, AXIS_SIZE.height_);
}

/**
 * @tc.name: MeasureUtilsTestNg019
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetCrossAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: the return value is equal to AXIS_SIZE.Height.
     */
    float retCrossSize = GetCrossAxisSize(AXIS_SIZE, AXIS_HORIZONTAL);
    EXPECT_EQ(retCrossSize, AXIS_SIZE.height_);

    /**
     * @tc.steps: step2. call GetCrossAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: the return value is equal to AXIS_SIZE.Width.
     */
    retCrossSize = GetCrossAxisSize(AXIS_SIZE, AXIS_VERTICAL);
    EXPECT_EQ(retCrossSize, AXIS_SIZE.width_);
}

/**
 * @tc.name: MeasureUtilsTestNg020
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: AXIS_SIZE.height_ is set to the TEST_VALUE.
     */
    SetCrossAxisSize(TEST_VALUE, AXIS_HORIZONTAL, AXIS_SIZE);
    EXPECT_EQ(AXIS_SIZE.height_, TEST_VALUE);

    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: AXIS_SIZE.width_ is set to the TEST_VALUE.
     */
    AXIS_SIZE = { 10.0, 20.0 };

    SetCrossAxisSize(TEST_VALUE, AXIS_VERTICAL, AXIS_SIZE);
    EXPECT_EQ(AXIS_SIZE.width_, TEST_VALUE);
}

/**
 * @tc.name: MeasureUtilsTestNg021
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: TEST_OPTIONAL_SIZE.width_ is set to the TEST_VALUE.
     */
    TEST_OPTIONAL_SIZE = { 10.0, 20.0 };

    SetMainAxisSize(TEST_VALUE, AXIS_HORIZONTAL, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 20.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 30.0);

    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: TEST_OPTIONAL_SIZE.height_ is set to the TEST_VALUE.
     */
    TEST_OPTIONAL_SIZE = { 10.0, 20.0 };

    SetMainAxisSize(TEST_VALUE, AXIS_VERTICAL, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 30.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNg022
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected:  the return value is equal to TEST_OPTIONAL_SIZE.width_.
     */
    TEST_OPTIONAL_SIZE = { 10.0, 20.0 };

    std::optional<float> retMainSize = GetMainAxisSize(TEST_OPTIONAL_SIZE, AXIS_HORIZONTAL);
    EXPECT_EQ(retMainSize, TEST_OPTIONAL_SIZE.width_);

    /**
     * @tc.steps: step2. call GetMainAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: the return value is equal to TEST_OPTIONAL_SIZE.height_.
     */
    retMainSize = GetMainAxisSize(TEST_OPTIONAL_SIZE, AXIS_VERTICAL);
    EXPECT_EQ(retMainSize, TEST_OPTIONAL_SIZE.height_);
}

/**
 * @tc.name: MeasureUtilsTestNg023
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetCrossAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: the return value is equal to TEST_OPTIONAL_SIZE.height_.
     */
    std::optional<float> retCrossSize = GetCrossAxisSize(TEST_OPTIONAL_SIZE, AXIS_HORIZONTAL);
    EXPECT_EQ(retCrossSize, TEST_OPTIONAL_SIZE.height_);

    /**
     * @tc.steps: step2. call GetCrossAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: the return value is equal to TEST_OPTIONAL_SIZE.width_.
     */
    retCrossSize = GetCrossAxisSize(TEST_OPTIONAL_SIZE, AXIS_VERTICAL);
    EXPECT_EQ(retCrossSize, TEST_OPTIONAL_SIZE.width_);
}

/**
 * @tc.name: MeasureUtilsTestNg024
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is AXIS_HORIZONTAL.
     * @tc.expected: TEST_OPTIONAL_SIZE.height_ is set to the TEST_VALUE.
     */
    SetCrossAxisSize(TEST_VALUE, AXIS_HORIZONTAL, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 30.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 10.0);

    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is AXIS_VERTICAL.
     * @tc.expected: TEST_OPTIONAL_SIZE.width_ is set to the TEST_VALUE.
     */
    TEST_OPTIONAL_SIZE = { 10.0, 20.0 };

    SetCrossAxisSize(TEST_VALUE, AXIS_VERTICAL, TEST_OPTIONAL_SIZE);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.height_, 20.0);
    EXPECT_EQ(TEST_OPTIONAL_SIZE.width_, 30.0);
}

/**
 * @tc.name: MeasureUtilsTestNg025
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateIdealSize and set input usingMaxSize is USING_MAX_SIZE_TRUE.
     * @tc.expected: the return retIdealSize is the same as layoutConstraint.maxSize.
     */
    LayoutConstraintF layoutConstraint;

    SizeF retIdealSize =
        CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MATCH_PARENT, USING_MAX_SIZE_TRUE);
    EXPECT_EQ(retIdealSize, layoutConstraint.maxSize);

    /**
     * @tc.steps: step2. call CreateIdealSize and set input usingMaxSize is USING_MAX_SIZE_FALSE.
     * @tc.expected: the return retIdealSize.width_ and retIdealSize.height_ is not equal 0.
     */
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_VERTICAL, MEASURE_TYPE_MATCH_PARENT, USING_MAX_SIZE_FALSE);
    EXPECT_NE(retIdealSize.width_, 0);
    EXPECT_NE(retIdealSize.height_, 0);
}

/**
 * @tc.name: MeasureUtilsTestNg026
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutConstraint.
     */
    LayoutConstraintF layoutConstraint;

    /**
     * @tc.steps: step1. call CreateIdealSize and set layoutConstraint.maxSize.height_ is 100.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.maxSize.height_.
     */
    layoutConstraint.maxSize = { 100.0, 100.0 };
    OptionalSizeF retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_CROSS_AXIS);
    EXPECT_EQ(retIdealSize.height_, layoutConstraint.maxSize.height_);

    /**
     * @tc.steps: step2. call CreateIdealSize and set layoutConstraint.parentIdealSize.height_ is 20.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.parentIdealSize.height_.
     */
    layoutConstraint.parentIdealSize = { 10.0, 20.0 };
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_CROSS_AXIS);
    EXPECT_EQ(retIdealSize.height_, layoutConstraint.parentIdealSize.height_);
}

/**
 * @tc.name: MeasureUtilsTestNg027
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutConstraint.
     */
    LayoutConstraintF layoutConstraint;

    /**
     * @tc.steps: step2. call CreateIdealSize and set layoutConstraint.maxSize.width_ is 100.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.maxSize.width_.
     */
    layoutConstraint.maxSize = { 100.0, 100.0 };
    OptionalSizeF retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MAIN_AXIS);
    EXPECT_EQ(retIdealSize.width_, layoutConstraint.maxSize.width_);

    /**
     * @tc.steps: step3. call CreateIdealSize and set layoutConstraint.parentIdealSize.width_ is 20.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.parentIdealSize.width_.
     */
    layoutConstraint.parentIdealSize = { 20.0, 10.0 };
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MAIN_AXIS);
    EXPECT_EQ(retIdealSize.width_, layoutConstraint.parentIdealSize.width_);

    /**
     * @tc.steps: step4. call CreateIdealSize and set testMeasureType is MEASURE_TYPE_MATCH_CONTENT.
     * @tc.expected: the return retIdealSize is the same as testOptionalSize.
     */
    OptionalSizeF testOptionalSize;

    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MATCH_CONTENT);
    EXPECT_EQ(retIdealSize, testOptionalSize);

    /**
     * @tc.steps: step5. call CreateIdealSize and set layoutConstraint.selfIdealSize.width_ is 20.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.selfIdealSize.width_ and return is
     * Valid.
     */
    layoutConstraint.selfIdealSize = { 20.0, 10.0 };
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MAIN_AXIS);
    EXPECT_EQ(retIdealSize.width_, layoutConstraint.selfIdealSize.width_);
    EXPECT_TRUE(retIdealSize.IsValid());

    /**
     * @tc.steps: step6. call CreateIdealSize and set layoutConstraint.selfIdealSize.width_ is 20 and measure type =
     * MEASURE_TYPE_CROSS_AXIS..
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.selfIdealSize.width_
     */
    layoutConstraint.selfIdealSize.Reset();
    layoutConstraint.selfIdealSize.SetHeight(20.0);
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_CROSS_AXIS);
    EXPECT_EQ(retIdealSize.height_, layoutConstraint.selfIdealSize.height_);

    /**
     * @tc.steps: step7. call CreateIdealSize and set layoutConstraint.selfIdealSize.width_ is 20 and measure type =
     * MEASURE_TYPE_MAIN_AXIS.
     * @tc.expected: the return retIdealSize.height_ is the same as layoutConstraint.selfIdealSize.width_
     */
    layoutConstraint.selfIdealSize.Reset();
    layoutConstraint.selfIdealSize.SetWidth(20.0);
    retIdealSize = CreateIdealSize(layoutConstraint, AXIS_HORIZONTAL, MEASURE_TYPE_MAIN_AXIS);
    EXPECT_EQ(retIdealSize.width_, layoutConstraint.selfIdealSize.width_);
}

/**
 * @tc.name: MeasureUtilsTestNg028
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testPadding.
     */
    PaddingPropertyF testPadding;

    /**
     * @tc.steps: step2. call CreateChildrenConstraint and set testPadding to have no value.
     * @tc.expected: the input CHILDREN_SIZE is not changed.
     */
    CreateChildrenConstraint(CHILDREN_SIZE, testPadding);
    EXPECT_EQ(CHILDREN_SIZE.width_, 10.0);
    EXPECT_EQ(CHILDREN_SIZE.height_, 20.0);

    /**
     * @tc.steps: step3. call CreateChildrenConstraint and set testPadding to have no value.
     * @tc.expected: step1. the input CHILDREN_SIZE is changed to the expected value.
     */
    testPadding = TEST_PROPERTY;

    CreateChildrenConstraint(CHILDREN_SIZE, testPadding);
    EXPECT_EQ(CHILDREN_SIZE.width_, -10.0);
    EXPECT_EQ(CHILDREN_SIZE.height_, 0);
}

/**
 * @tc.name: MeasureUtilsTestNg029
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testPadding.
     */
    PaddingProperty testPadding;
    std::optional<CalcDimension> top, bottom, left, right;

    /**
     * @tc.steps: step2. call ConvertToCalcPaddingProperty and set testPadding to have no value.
     * @tc.expected: the input CHILDREN_SIZE is not changed.
     */
    PaddingProperty res = ConvertToCalcPaddingProperty(top, bottom, left, right);
    EXPECT_EQ(testPadding, res);

    /**
     * @tc.steps: step3. call ConvertToCalcPaddingProperty and set testPadding to have CalcValue.
     * @tc.expected: step1. the input CHILDREN_SIZE is changed to the expected value.
     */
    top = CALC_TEST;
    bottom = CALC_TEST;
    left = CALC_TEST;
    right = CALC_TEST;
    testPadding.top = NG::CalcLength(top.value().CalcValue());
    testPadding.bottom = NG::CalcLength(bottom.value().CalcValue());
    testPadding.left = NG::CalcLength(left.value().CalcValue());
    testPadding.right = NG::CalcLength(right.value().CalcValue());
    res = ConvertToCalcPaddingProperty(top, bottom, left, right);
    EXPECT_EQ(testPadding, res);

    /**
     * @tc.steps: step4. call ConvertToCalcPaddingProperty and set testPadding to have value.
     * @tc.expected: step1. the input CHILDREN_SIZE is changed to the expected value.
     */
    top = BORDER_WIDTH_PX;
    bottom = BORDER_WIDTH_PX;
    left = BORDER_WIDTH_PX;
    right = BORDER_WIDTH_PX;
    testPadding.top = NG::CalcLength(top.value());
    testPadding.bottom = NG::CalcLength(bottom.value());
    testPadding.left = NG::CalcLength(left.value());
    testPadding.right = NG::CalcLength(right.value());
    res = ConvertToCalcPaddingProperty(top, bottom, left, right);
    EXPECT_EQ(testPadding, res);
}

/**
 * @tc.name: MeasureUtilsTestNg030
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testPadding and sizeF.
     */
    PaddingPropertyF testPadding;
    testPadding.left = 1.0f;
    testPadding.right = 2.0f;
    testPadding.top = 3.0f;
    testPadding.bottom = 4.0f;

    SizeF temp_size { 50.0, 50.0 };

    /**
     * @tc.steps: step2. call MinusPaddingToNonNegativeSize.
     * @expected: excute succuss.
     */
    MinusPaddingToNonNegativeSize(testPadding, temp_size);
    EXPECT_EQ(temp_size.width_, 47);
    EXPECT_EQ(temp_size.height_, 43);
}

/**
 * @tc.name: MeasureUtilsTestNg031
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create OptionalSizeF,MeasureProperty and SizeF.
     */
    OptionalSizeF frameSize = { 10.0, 10.0 };
    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    SizeF percentReference = { 20, 20 };

    /**
     * @tc.steps: step2. call UpdateOptionSizeByCalcLayoutConstraint with out MeasureProperty.
     * @expected: frameResult is equal with frameSize.
     */
    OptionalSizeF frameResult = UpdateOptionSizeByCalcLayoutConstraint(frameSize, nullptr, percentReference);
    EXPECT_EQ(frameResult.Height(), 10);
    EXPECT_EQ(frameResult.Width(), 10);

    /**
     * @tc.steps: step3. call UpdateOptionSizeByCalcLayoutConstraint with MeasureProperty
     * without calcLayoutConstraintMaxMinSize.
     * @expected: update fail
     */
    frameResult = UpdateOptionSizeByCalcLayoutConstraint(frameSize, calcLayoutConstraint, percentReference);
    EXPECT_EQ(frameResult.Height(), 10);
    EXPECT_EQ(frameResult.Width(), 10);

    /**
     * @tc.steps: step4. call UpdateOptionSizeByCalcLayoutConstraint with MeasureProperty without maxSize.
     * @expected: update fail
     */
    calcLayoutConstraint->maxSize = std::make_optional<CalcSize>();
    calcLayoutConstraint->maxSize->width_.reset();
    calcLayoutConstraint->maxSize->height_.reset();
    frameResult = UpdateOptionSizeByCalcLayoutConstraint(frameSize, calcLayoutConstraint, percentReference);
    EXPECT_EQ(frameResult.Height(), 10);
    EXPECT_EQ(frameResult.Width(), 10);

    /**
     * @tc.steps: step5. call UpdateOptionSizeByCalcLayoutConstraint with MeasureProperty
     * and with calcLayoutConstraintMaxMinSize.
     * @expected: update seccuess
     */
    calcLayoutConstraint->maxSize = std::make_optional<CalcSize>(CalcLength(50.0), CalcLength(100.0));
    calcLayoutConstraint->minSize = std::make_optional<CalcSize>(CalcLength(15), CalcLength(15));
    frameResult = UpdateOptionSizeByCalcLayoutConstraint(frameSize, calcLayoutConstraint, percentReference);
    EXPECT_EQ(frameResult.Height(), 15);
    EXPECT_EQ(frameResult.Width(), 15);
}

/**
 * @tc.name: MeasureUtilsTestNg032
 * @tc.desc: Test cast to MeasureUtilsTestNg.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create OptionalSizeF and axis.
     */
    LayoutConstraintF layoutConstraint;
    Axis axis = Axis::HORIZONTAL;

    layoutConstraint.selfIdealSize = { 10.0, 10.0 };
    layoutConstraint.parentIdealSize = { 10.0, 30.0 };
    layoutConstraint.percentReference = { 20.0, 20.0 };
    layoutConstraint.maxSize = { Infinity<float>(), Infinity<float>() };
    layoutConstraint.minSize = { 0, 0 };

    /**
     * @tc.steps: step2. call CreateIdealSizeByPercentRef with selfIdealSize Valid.
     * @expected: result is equal with selfIdealSize
     */
    OptionalSizeF optionResult = CreateIdealSizeByPercentRef(layoutConstraint, axis, MEASURE_TYPE_MATCH_PARENT, true);
    EXPECT_EQ(optionResult.Height(), 10.0);
    EXPECT_EQ(optionResult.Width(), 10.0);

    /**
     * @tc.steps: step3. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_MATCH_PARENT.
     */
    layoutConstraint.selfIdealSize.Reset();
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, axis, MEASURE_TYPE_MATCH_PARENT, true);
    EXPECT_EQ(optionResult.Height(), 30.0);
    EXPECT_EQ(optionResult.Width(), 10.0);

    /**
     * @tc.steps: step4. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_CROSS_AXIS.
     * @expected: height set success.
     */
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, axis, MEASURE_TYPE_CROSS_AXIS, true);
    EXPECT_EQ(optionResult.Height(), 30.0);
    EXPECT_EQ(optionResult.Width(), std::nullopt);

    /**
     * @tc.steps: step5. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_CROSS_AXIS.
     */
    layoutConstraint.parentIdealSize.Reset();
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, axis, MEASURE_TYPE_CROSS_AXIS, true);
    EXPECT_EQ(optionResult.Height(), 20.0);
    EXPECT_EQ(optionResult.Width(), std::nullopt);

    /**
     * @tc.steps: step6. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_MAIN_AXIS.
     */
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, Axis::VERTICAL, MEASURE_TYPE_MAIN_AXIS, true);
    EXPECT_EQ(optionResult.Height(), 20);
    EXPECT_EQ(optionResult.Width(), std::nullopt);

    /**
     * @tc.steps: step7. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_MAIN_AXIS.
     */
    layoutConstraint.parentIdealSize = { 10.0, 30.0 };
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, Axis::HORIZONTAL, MEASURE_TYPE_MAIN_AXIS, true);
    EXPECT_EQ(optionResult.Height(), std::nullopt);
    EXPECT_EQ(optionResult.Width(), 10.0);

    /**
     * @tc.steps: step8. call CreateIdealSizeByPercentRef withOut selfIdealSize Valid
     * and Measure is MEASURE_TYPE_MATCH_CONTENT.
     */
    optionResult = CreateIdealSizeByPercentRef(layoutConstraint, axis, MEASURE_TYPE_MATCH_CONTENT, false);
    EXPECT_EQ(optionResult.Height(), std::nullopt);
    EXPECT_EQ(optionResult.Width(), std::nullopt);
}

/**
 * @tc.name: AdjacentExpandToRectTest
 * @tc.desc: Test cast to AdjacentExpandToRect.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, AdjacentExpandToRectTest, TestSize.Level1)
{
    RectF adjustingRect(20.0f, 10.0f, 60.0f, 100.0f);
    RectF frameRect(10.0f, 10.0f, 100.0f, 100.0f);
    PaddingPropertyF frameExpand = {
        .left = 10.0f,
        .right = 20.0f,
        .top = 30.0f,
        .bottom = 40.0f
    };
    PaddingPropertyF expectRes = {
        .left = std::nullopt,
        .right = std::nullopt,
        .top = 30.0f,
        .bottom = 40.0f
    };
    auto filteredExpand = AdjacentExpandToRect(adjustingRect, frameExpand, frameRect);
    EXPECT_EQ(filteredExpand, expectRes);
}
} // namespace OHOS::Ace::NG
