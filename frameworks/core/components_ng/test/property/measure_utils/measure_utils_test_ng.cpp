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

#include "gtest/gtest.h"

#include <memory>
#include <optional>

#define protected public
#define private public

#include "core/components_ng/property/measure_utils.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MeasureUtilsTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineBase::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: MeasureUtilsTestNgTest001
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToSize and set input size.width_ is 50, size.height_ is 100.
     * @tc.expected: step1. the return size is the same as input size.
     */
    Dimension width {50.0, DimensionUnit::PX};
    Dimension height {100.0, DimensionUnit::PX};
    CalcSize testCalcSize {NG::CalcLength(width), NG::CalcLength(height)};
    ScaleProperty scaleProperty;
    SizeF testSize(2.0, 2.0);

    SizeF retSize = ConvertToSize(testCalcSize, std::move(scaleProperty), testSize);
    EXPECT_EQ(retSize.width_, 50.0);
    EXPECT_EQ(retSize.height_, 100.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest002
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToOptionalSize and set input size.width_ is 30, size.height_ is 80.
     * @tc.expected: step1. the return size is the same as input size.
     */
    Dimension width {30.0, DimensionUnit::PX};
    Dimension height {80.0, DimensionUnit::PX};
    CalcSize testCalcSize {NG::CalcLength(width), NG::CalcLength(height)};
    ScaleProperty scaleProperty;
    SizeF testSize(1.0, 2.0);

    OptionalSizeF retSize = ConvertToOptionalSize(testCalcSize, std::move(scaleProperty), testSize);
    EXPECT_EQ(retSize.width_, 30.0);
    EXPECT_EQ(retSize.height_, 80.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest003
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToPx and set input value is 20.
     * @tc.expected: step1. the return size is the same as input value.
     */
    CalcLength width {20.0, DimensionUnit::PX};
    ScaleProperty scaleProperty;

    std::optional<float> retSize = ConvertToPx(width, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, 20.0);
    /**
     * @tc.steps: step2. call ConvertToPx and set input DimensionUnit is CALC.
     * @tc.expected: step2. the return value is nullopt.
     */
    CalcLength calc {10.0, DimensionUnit::CALC};

    retSize = ConvertToPx(calc, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNgTest004
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToPx and set input value is null.
     * @tc.expected: step1. the return value is nullopt.
     */
    std::optional<CalcLength> testCalcSize;
    ScaleProperty scaleProperty;

    std::optional<float> retSize = ConvertToPx(testCalcSize, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, std::nullopt);
    /**
     * @tc.steps: step2. call ConvertToPx and set input DimensionUnit is CALC.
     * @tc.expected: step2. the return value is nullopt.
     */
    Dimension calcWidth {30.0, DimensionUnit::CALC};

    retSize = ConvertToPx(CalcLength(calcWidth), std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNgTest005
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    Dimension width {30.0, DimensionUnit::PX};
    ScaleProperty scaleProperty;

    std::optional<float> retSize = ConvertToPx(width, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, 30.0);
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    Dimension calc {30.0, DimensionUnit::CALC};

    retSize = ConvertToPx(calc, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retSize, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNgTest006
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    SizeF testSize {50, 50};
    SizeF testMinSize {10, 10};
    SizeF testMaxSize {100, 100};

    SizeF retSize = ConstrainSize(testSize, testMinSize, testMaxSize);
    EXPECT_EQ(retSize, testSize);
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    testSize = {50, 50};
    testMinSize = {10, 10};
    testMaxSize = {0, 0};

    retSize = ConstrainSize(testSize, testMinSize, testMaxSize);
    EXPECT_EQ(retSize, testSize);
}

/**
 * @tc.name: MeasureUtilsTestNgTest007
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToMarginPropertyF and set input margin is null.
     * @tc.expected: step1. the return value is null.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    std::unique_ptr<MarginProperty> testMarginProperty = nullptr;

    PaddingPropertyF retProperty = ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), 1.0);
    /**
     * @tc.steps: step2. call ConvertToMarginPropertyF and set input margin is not null.
     * @tc.expected: step2. return expected value.
     */
    CalcLength left {10.0, DimensionUnit::PX};
    CalcLength right {10.0, DimensionUnit::PX};
    CalcLength top {10.0, DimensionUnit::PX};
    CalcLength bottom {10.0, DimensionUnit::PX};

    testPadding.left = left;
    testPadding.right = right;
    testPadding.top = top;
    testPadding.bottom = bottom;
    PaddingPropertyF testProperty = {10.0, 10.0, 10.0, 10.0};

    testMarginProperty = std::make_unique<MarginProperty>(std::move(testPadding));
    retProperty = ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retProperty, testProperty);
}

/**
 * @tc.name: MeasureUtilsTestNgTest008
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToMarginPropertyF and set input margin is PaddingProperty.
     * @tc.expected: step1. return expected value.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    CalcLength left {20.0, DimensionUnit::PX};
    CalcLength right {20.0, DimensionUnit::PX};
    CalcLength top {20.0, DimensionUnit::PX};
    CalcLength bottom {20.0, DimensionUnit::PX};

    testPadding.left = left;
    testPadding.right = right;
    testPadding.top = top;
    testPadding.bottom = bottom;
    PaddingPropertyF testProperty = {20.0, 20.0, 20.0, 20.0};

    MarginProperty testMarginProperty = testPadding;
    PaddingPropertyF retProperty = ConvertToMarginPropertyF(testMarginProperty, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retProperty, testProperty);
}

/**
 * @tc.name: MeasureUtilsTestNgTest009
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToBorderWidthPropertyF and set input borderWidth is null.
     * @tc.expected: step1. the return value is null.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    std::unique_ptr<BorderWidthProperty> testBorderWidthProperty = nullptr;

    BorderWidthPropertyF retProperty =
        ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), 1.0);
    /**
     * @tc.steps: step2. call ConvertToMarginPropertyF and set input borderWidth is not null.
     * @tc.expected: step2. return expected value.
     */
    BorderWidthPropertyT<Dimension> testPropertyT;
    Dimension left {10.0, DimensionUnit::PX};
    Dimension right {10.0, DimensionUnit::PX};
    Dimension top {10.0, DimensionUnit::PX};
    Dimension bottom {10.0, DimensionUnit::PX};

    testPropertyT.leftDimen = left;
    testPropertyT.rightDimen = right;
    testPropertyT.topDimen = top;
    testPropertyT.bottomDimen = bottom;
    BorderWidthPropertyF testProperty = {10.0, 10.0, 10.0, 10.0};

    testBorderWidthProperty = std::make_unique<BorderWidthProperty>(std::move(testPropertyT));
    retProperty = ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retProperty, testProperty);
}

/**
 * @tc.name: MeasureUtilsTestNgTest010
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ConvertToBorderWidthPropertyF and set borderWidth Dimension is null.
     * @tc.expected: step1. the return value is std::nullopt.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    BorderWidthPropertyT<Dimension> testPropertyT;

    std::unique_ptr<BorderWidthProperty> testBorderWidthProperty =
        std::make_unique<BorderWidthProperty>(std::move(testPropertyT));
    BorderWidthPropertyF retProperty =
        ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retProperty.leftDimen, std::nullopt);
    /**
     * @tc.steps: step1. call ConvertToBorderWidthPropertyF and set borderWidth DimensionUnit is VP.
     * @tc.expected: step1. the return value is std::nullopt.
     */
    Dimension left {10.0, DimensionUnit::VP};
    Dimension right {10.0, DimensionUnit::VP};
    Dimension top {10.0, DimensionUnit::VP};
    Dimension bottom {10.0, DimensionUnit::VP};

    testPropertyT.leftDimen = left;
    testPropertyT.rightDimen = right;
    testPropertyT.topDimen = top;
    testPropertyT.bottomDimen = bottom;

    testBorderWidthProperty = std::make_unique<BorderWidthProperty>(std::move(testPropertyT));
    retProperty = ConvertToBorderWidthPropertyF(testBorderWidthProperty, std::move(scaleProperty), 1.0);
    EXPECT_EQ(retProperty.leftDimen, std::nullopt);
}

/**
 * @tc.name: MeasureUtilsTestNgTest011
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdatePaddingPropertyF and set input Padding is null.
     * @tc.expected: step1. testPaddingPropertyF is not update.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    SizeF testSelfSize = {1.0, 1.0};
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    PaddingPropertyF testProperty = {0, 0, 0, 0};

    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), testSelfSize, testPaddingPropertyF);
    EXPECT_EQ(testPaddingPropertyF, testProperty);
    /**
     * @tc.steps: step2. call UpdatePaddingPropertyF and set input Padding is not null.
     * @tc.expected: step2. testPaddingPropertyF is update and it value is the same as testPadding.
     */
    CalcLength left {30.0, DimensionUnit::PX};
    CalcLength right {30.0, DimensionUnit::PX};
    CalcLength top {30.0, DimensionUnit::PX};
    CalcLength bottom {30.0, DimensionUnit::PX};

    testPadding.left = left;
    testPadding.right = right;
    testPadding.top = top;
    testPadding.bottom = bottom;
    testProperty = {30.0, 30.0, 30.0, 30.0};

    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), testSelfSize, testPaddingPropertyF);
    EXPECT_EQ(testPaddingPropertyF, testProperty);
}

/**
 * @tc.name: MeasureUtilsTestNgTest012
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdatePaddingPropertyF and set input Padding DimensionUnit is VP.
     * @tc.expected: step1. testPaddingPropertyF is not update.
     */
    ScaleProperty scaleProperty;
    PaddingProperty testPadding;
    SizeF testSelfSize = {1.0, 1.0};
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    PaddingPropertyF testProperty = {0, 0, 0, 0};

    CalcLength left {30.0, DimensionUnit::VP};
    CalcLength right {30.0, DimensionUnit::VP};
    CalcLength top {30.0, DimensionUnit::VP};
    CalcLength bottom {30.0, DimensionUnit::VP};

    testPadding.left = left;
    testPadding.right = right;
    testPadding.top = top;
    testPadding.bottom = bottom;

    UpdatePaddingPropertyF(testPadding, std::move(scaleProperty), testSelfSize, testPaddingPropertyF);
    EXPECT_EQ(testPaddingPropertyF, testProperty);
}

/**
 * @tc.name: MeasureUtilsTestNgTest013
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call AddPaddingToSize and set input Padding is zero.
     * @tc.expected: step1. the testSize is not changed.
     */
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    SizeF testSize = {10.0, 10.0};

    AddPaddingToSize(testPaddingPropertyF, testSize);
    EXPECT_EQ(testSize.width_, 10.0);
    EXPECT_EQ(testSize.height_, 10.0);

    /**
     * @tc.steps: step2. call AddPaddingToSize and set input Padding is not zero.
     * @tc.expected: step2. the testSize is changed into expected values.
     */
    testPaddingPropertyF = {10.0, 20.0, 30.0, 40.0};

    AddPaddingToSize(testPaddingPropertyF, testSize);
    EXPECT_EQ(testSize.width_, 40.0);
    EXPECT_EQ(testSize.height_, 80.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest014
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call MinusPaddingToSize and set input Padding is zero.
     * @tc.expected: step1. the testSize is not changed.
     */
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    SizeF testSize = {100.0, 100.0};

    MinusPaddingToSize(testPaddingPropertyF, testSize);
    EXPECT_EQ(testSize.width_, 100.0);
    EXPECT_EQ(testSize.height_, 100.0);

    /**
     * @tc.steps: step2. call MinusPaddingToSize and set input Padding is not zero.
     * @tc.expected: step2. the testSize is changed into expected values.
     */
    testPaddingPropertyF = {10.0, 20.0, 30.0, 40.0};

    MinusPaddingToSize(testPaddingPropertyF, testSize);
    EXPECT_EQ(testSize.width_, 70.0);
    EXPECT_EQ(testSize.height_, 30.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest015
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call AddPaddingToSize and set input Padding is zero.
     * @tc.expected: step1. the testOptionalSize is not changed.
     */
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    OptionalSizeF testOptionalSize = {10.0, 10.0};

    AddPaddingToSize(testPaddingPropertyF, testOptionalSize);
    EXPECT_EQ(testOptionalSize.width_, 10.0);
    EXPECT_EQ(testOptionalSize.height_, 10.0);

    /**
     * @tc.steps: step2. call AddPaddingToSize and set input Padding is not zero.
     * @tc.expected: step2. the testOptionalSize is changed into expected values.
     */
    testPaddingPropertyF = {40.0, 30.0, 20.0, 10.0};

    AddPaddingToSize(testPaddingPropertyF, testOptionalSize);
    EXPECT_EQ(testOptionalSize.width_, 80.0);
    EXPECT_EQ(testOptionalSize.height_, 40.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest016
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call MinusPaddingToSize and set input Padding is zero.
     * @tc.expected: step1. the testOptionalSize is not changed.
     */
    PaddingPropertyF testPaddingPropertyF = {0, 0, 0, 0};
    OptionalSizeF testOptionalSize = {100.0, 100.0};

    MinusPaddingToSize(testPaddingPropertyF, testOptionalSize);
    EXPECT_EQ(testOptionalSize.width_, 100.0);
    EXPECT_EQ(testOptionalSize.height_, 100.0);

    /**
     * @tc.steps: step2. call MinusPaddingToSize and set input Padding is not zero.
     * @tc.expected: step2. the testOptionalSize is changed into expected values.
     */
    testPaddingPropertyF = {40.0, 30.0, 20.0, 10.0};

    MinusPaddingToSize(testPaddingPropertyF, testOptionalSize);
    EXPECT_EQ(testOptionalSize.width_, 30.0);
    EXPECT_EQ(testOptionalSize.height_, 70.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest017
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisOffset and set input Axis is HORIZONTAL.
     * @tc.expected: step1. return Offset.X.
     */
    OffsetF testOffset = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;

    float retMainOffset = GetMainAxisOffset(testOffset, testAxis);
    EXPECT_EQ(retMainOffset, 10.0);
    /**
     * @tc.steps: step2. call GetMainAxisOffset and set input Axis is HORIZONTAL.
     * @tc.expected: step2. return Offset.Y.
     */
    testAxis = Axis::VERTICAL;

    retMainOffset = GetMainAxisOffset(testOffset, testAxis);
    EXPECT_EQ(retMainOffset, 20.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest018
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. return size.Width.
     */
    SizeF testSize = {20.0, 10.0};
    Axis testAxis = Axis::HORIZONTAL;

    float retMainSize = GetMainAxisSize(testSize, testAxis);
    EXPECT_EQ(retMainSize, 20.0);
    /**
     * @tc.steps: step2. call GetMainAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. return size.Height.
     */
    testAxis = Axis::VERTICAL;

    retMainSize = GetMainAxisSize(testSize, testAxis);
    EXPECT_EQ(retMainSize, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest019
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetCrossAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. return size.Height.
     */
    SizeF testSize = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;

    float retCrossSize = GetCrossAxisSize(testSize, testAxis);
    EXPECT_EQ(retCrossSize, 20.0);
    /**
     * @tc.steps: step2. call GetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. return size.Width.
     */
    testAxis = Axis::VERTICAL;

    retCrossSize = GetCrossAxisSize(testSize, testAxis);
    EXPECT_EQ(retCrossSize, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest020
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. testSize.height is set to the testValue.
     */
    SizeF testSize = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;
    float testValue = 30.0;

    SetCrossAxisSize(testValue, testAxis, testSize);
    EXPECT_EQ(testSize.height_, 30.0);
    EXPECT_EQ(testSize.width_, 10.0);
    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. testSize.width is set to the testValue.
     */
    testSize = {10.0, 20.0};
    testAxis = Axis::VERTICAL;

    SetCrossAxisSize(testValue, testAxis, testSize);
    EXPECT_EQ(testSize.height_, 20.0);
    EXPECT_EQ(testSize.width_, 30.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest021
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. testOptionalSize.width is set to the testValue.
     */
    OptionalSizeF testOptionalSize = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;
    float testValue = 30.0;

    SetMainAxisSize(testValue, testAxis, testOptionalSize);
    EXPECT_EQ(testOptionalSize.height_, 20.0);
    EXPECT_EQ(testOptionalSize.width_, 30.0);
    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. testOptionalSize.height is set to the testValue.
     */
    testOptionalSize = {10.0, 20.0};
    testAxis = Axis::VERTICAL;

    SetMainAxisSize(testValue, testAxis, testOptionalSize);
    EXPECT_EQ(testOptionalSize.height_, 30.0);
    EXPECT_EQ(testOptionalSize.width_, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest022
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetMainAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. return testOptionalSize.Width.
     */
    OptionalSizeF testOptionalSize = {20.0, 10.0};
    Axis testAxis = Axis::HORIZONTAL;

    std::optional<float> retMainSize = GetMainAxisSize(testOptionalSize, testAxis);
    EXPECT_EQ(retMainSize, 20.0);
    /**
     * @tc.steps: step2. call GetMainAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. return testOptionalSize.Height.
     */
    testAxis = Axis::VERTICAL;

    retMainSize = GetMainAxisSize(testOptionalSize, testAxis);
    EXPECT_EQ(retMainSize, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest023
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call GetCrossAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. return testOptionalSize.Height.
     */
    OptionalSizeF testOptionalSize = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;

    std::optional<float> retCrossSize = GetCrossAxisSize(testOptionalSize, testAxis);
    EXPECT_EQ(retCrossSize, 20.0);
    /**
     * @tc.steps: step2. call GetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. return testOptionalSize.Height.
     */
    testAxis = Axis::VERTICAL;

    retCrossSize = GetCrossAxisSize(testOptionalSize, testAxis);
    EXPECT_EQ(retCrossSize, 10.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest024
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetCrossAxisSize and set input Axis is HORIZONTAL.
     * @tc.expected: step1. testSize.height is set to the testValue.
     */
    OptionalSizeF testOptionalSize = {10.0, 20.0};
    Axis testAxis = Axis::HORIZONTAL;
    float testValue = 30.0;

    SetCrossAxisSize(testValue, testAxis, testOptionalSize);
    EXPECT_EQ(testOptionalSize.height_, 30.0);
    EXPECT_EQ(testOptionalSize.width_, 10.0);
    /**
     * @tc.steps: step2. call SetCrossAxisSize and set input Axis is VERTICAL.
     * @tc.expected: step2. testSize.width is set to the testValue.
     */
    testOptionalSize = {10.0, 20.0};
    testAxis = Axis::VERTICAL;

    SetCrossAxisSize(testValue, testAxis, testOptionalSize);
    EXPECT_EQ(testOptionalSize.height_, 20.0);
    EXPECT_EQ(testOptionalSize.width_, 30.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest025
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateIdealSize and set input usingMaxSize is true.
     * @tc.expected: step1. the return retIdealSize is the same as layoutConstraint.maxSize.
     */
    LayoutConstraintF layoutConstraint;
    Axis testAxis = Axis::HORIZONTAL;
    MeasureType testMeasureType = MeasureType::MATCH_PARENT;
    bool usingMaxSize = true;

    SizeF retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType, usingMaxSize);
    EXPECT_EQ(retIdealSize, layoutConstraint.maxSize);
    /**
     * @tc.steps: step2. call CreateIdealSize and set input usingMaxSize is false.
     * @tc.expected: step2. the return retIdealSize.width_ and retIdealSize.height_ is not equal 0.
     */
    usingMaxSize = false;
    retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType, usingMaxSize);
    EXPECT_NE(retIdealSize.width_, 0);
    EXPECT_NE(retIdealSize.height_, 0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest026
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateIdealSize and set layoutConstraint.maxSize.height_ is 100.
     * @tc.expected: step1. the return retIdealSize.height_ is the same as layoutConstraint.maxSize.height_.
     */
    LayoutConstraintF layoutConstraint;
    Axis testAxis = Axis::HORIZONTAL;
    MeasureType testMeasureType = MeasureType::MATCH_PARENT_CROSS_AXIS;

    layoutConstraint.maxSize = {100.0, 100.0};
    OptionalSizeF retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType);
    EXPECT_EQ(retIdealSize.height_, layoutConstraint.maxSize.height_);

    /**
     * @tc.steps: step1. call CreateIdealSize and set layoutConstraint.parentIdealSize.height_ is 20.
     * @tc.expected: step1. the return retIdealSize.height_ is the same as layoutConstraint.parentIdealSize.height_.
     */
    layoutConstraint.parentIdealSize = {10.0, 20.0};
    retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType);
    EXPECT_EQ(retIdealSize.height_, 20.0);
}

/**
 * @tc.name: MeasureUtilsTestNgTest027
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateIdealSize and set layoutConstraint.maxSize.width_ is 100.
     * @tc.expected: step1. the return retIdealSize.height_ is the same as layoutConstraint.maxSize.width_.
     */
    LayoutConstraintF layoutConstraint;
    Axis testAxis = Axis::HORIZONTAL;
    MeasureType testMeasureType = MeasureType::MATCH_PARENT_MAIN_AXIS;

    layoutConstraint.maxSize = {100.0, 100.0};
    OptionalSizeF retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType);
    EXPECT_EQ(retIdealSize.width_, 100.0);
    /**
     * @tc.steps: step1. call CreateIdealSize and set layoutConstraint.parentIdealSize.width_ is 20.
     * @tc.expected: step1. the return retIdealSize.height_ is the same as layoutConstraint.parentIdealSize.width_.
     */
    layoutConstraint.parentIdealSize = {20.0, 10.0};
    retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType);
    EXPECT_EQ(retIdealSize.width_, 20.0);
    /**
     * @tc.steps: step1. call CreateIdealSize and set testMeasureType is MATCH_CONTENT.
     * @tc.expected: step1. the return retIdealSize is the same as testOptionalSize.
     */
    OptionalSizeF testOptionalSize;
    testMeasureType = MeasureType::MATCH_CONTENT;

    retIdealSize = CreateIdealSize(layoutConstraint, testAxis, testMeasureType);
    EXPECT_EQ(retIdealSize, testOptionalSize);
}

/**
 * @tc.name: MeasureUtilsTestNgTest028
 * @tc.desc: Set one index value into MeasureUtilsTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(MeasureUtilsTestNg, MeasureUtilsTestNgTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateChildrenConstraint and set testPadding to have no value.
     * @tc.expected: step1. the input testSize is not changed.
     */
    SizeF testSize = {10.0, 20.0};
    PaddingPropertyF testPadding;

    CreateChildrenConstraint(testSize, testPadding);
    EXPECT_EQ(testSize.width_, 10.0);
    EXPECT_EQ(testSize.height_, 20.0);
    /**
     * @tc.steps: step1. call CreateChildrenConstraint and set testPadding to have no value.
     * @tc.expected: step1. the input testSize is changed to the expected value.
     */
    testPadding = {10.0, 10.0, 10.0, 10.0};

    CreateChildrenConstraint(testSize, testPadding);
    EXPECT_EQ(testSize.width_, -10.0);
    EXPECT_EQ(testSize.height_, 0);
}
} // namespace OHOS::Ace::NG
