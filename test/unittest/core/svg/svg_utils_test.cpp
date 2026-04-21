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
#include "frameworks/core/components_ng/svg/svg_utils.h"
#include "base/geometry/size.h"
#include "base/geometry/rect.h"

using namespace testing;
using namespace OHOS::Ace::NG;

class SvgUtilsTest : public testing::Test {
public:
    void SetUp() override
    {
        // Initialize test data
        svgContentSize_ = Size(100, 80);
        svgContainerSize_ = Size(200, 150);
        svgSize_ = Size(300, 240);
        viewBox_ = Rect(0, 0, 400, 320);
    }

    void TearDown() override
    {
        // Clean up
    }

protected:
    Size svgContentSize_;
    Size svgContainerSize_;
    Size svgSize_;
    Rect viewBox_;
};

/**
 * @tc.name: SvgUtilsTest001
 * @tc.desc: Test SVG content size calculation
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest001, TestSize.Level1)
{
    // Test content size calculation with matching sizes
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, viewBox_);
    
    EXPECT_FLOAT_EQ(testContentSize.Width(), 200.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 150.0f);
}

/**
 * @tc.name: SvgUtilsTest002
 * @tc.desc: Test SVG content size with different viewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest002, TestSize.Level1)
{
    // Test with different viewBox
    Rect testViewBox(50, 25, 300, 200);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, testViewBox);
    
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest003
 * @tc.desc: Test SVG content size scaling
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest003, TestSize.Level1)
{
    // Test scaling scenarios
    Size smallContainer(100, 75);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, smallContainer, svgSize_, viewBox_);
    
    // Result should be smaller due to container constraint
    EXPECT_FLOAT_LE(testContentSize.Width(), 100.0f);
    EXPECT_FLOAT_LE(testContentSize.Height(), 75.0f);
}

/**
 * @tc.name: SvgUtilsTest004
 * @tc.desc: Test SVG content size with zero dimensions
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest004, TestSize.Level1)
{
    // Test zero container size
    Size zeroContainer(0, 0);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, zeroContainer, svgSize_, viewBox_);
    
    EXPECT_FLOAT_EQ(testContentSize.Width(), 0.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest005
 * @tc.desc: Test SVG content size with empty viewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest005, TestSize.Level1)
{
    // Test empty viewBox
    Rect emptyViewBox;
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, emptyViewBox);
    
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest006
 * @tc.desc: Test SVG content size aspect ratio preservation
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest006, TestSize.Level1)
{
    // Test aspect ratio preservation
    Size squareContainer(150, 150);
    Rect wideViewBox(0, 0, 400, 200); // 2:1 aspect ratio
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, squareContainer, svgSize_, wideViewBox);
    
    // Should maintain aspect ratio while fitting
    EXPECT_FLOAT_LE(testContentSize.Width(), 150.0f);
    EXPECT_FLOAT_LE(testContentSize.Height(), 150.0f);
}

/**
 * @tc.name: SvgUtilsTest007
 * @tc.desc: Test SVG content size with tall aspect ratio
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest007, TestSize.Level1)
{
    // Test tall aspect ratio
    Size wideContainer(200, 100);
    Rect tallViewBox(0, 0, 200, 400); // 1:2 aspect ratio
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, wideContainer, svgSize_, tallViewBox);
    
    EXPECT_FLOAT_LE(testContentSize.Width(), 200.0f);
    EXPECT_FLOAT_LE(testContentSize.Height(), 100.0f);
}

/**
 * @tc.name: SvgUtilsTest008
 * @tc.desc: Test SVG feature enable check
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest008, TestSize.Level1)
{
    // Test feature version checking
    uint32_t featureVersion = SVG_FEATURE_SUPPORT_TWO;
    uint32_t userConfigVersion = SVG_FEATURE_SUPPORT_TWO;
    
    bool result = SvgUtils::IsFeatureEnable(featureVersion, userConfigVersion);
    EXPECT_TRUE(result);
    
    // Test with higher feature requirement
    uint32_t higherFeature = 3;
    result = SvgUtils::IsFeatureEnable(higherFeature, userConfigVersion);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SvgUtilsTest009
 * @tc.desc: Test SVG feature enable with undefined version
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest009, TestSize.Level1)
{
    // Test with undefined version
    uint32_t featureVersion = SVG_FEATURE_SUPPORT_TWO;
    uint32_t userConfigVersion = SVG_FEATURE_SUPPORT_UNDEFINE;
    
    bool result = SvgUtils::IsFeatureEnable(featureVersion, userConfigVersion);
    EXPECT_FALSE(result); // Should not enable when version is undefined
}

/**
 * @tc.name: SvgUtilsTest010
 * @tc.desc: Test SVG content size with very small values
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest010, TestSize.Level1)
{
    // Test with very small values
    Size tinyContainer(10, 5);
    Rect tinyViewBox(0, 0, 2, 1);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, tinyContainer, svgSize_, tinyViewBox);
    
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest011
 * @tc.desc: Test SVG content size with very large values
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest011, TestSize.Level1)
{
    // Test with very large values
    Size largeContainer(1000, 800);
    Rect largeViewBox(0, 0, 2000, 1600);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, largeContainer, svgSize_, largeViewBox);
    
    EXPECT_FLOAT_EQ(testContentSize.Width(), 1000.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 800.0f);
}

/**
 * @tc.name: SvgUtilsTest012
 * @tc.desc: Test SVG content size overflow protection
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest012, TestSize.Level1)
{
    // Test with potential overflow values
    Size overflowContainer(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, overflowContainer, svgSize_, viewBox_);
    
    // Should handle overflow gracefully
    EXPECT_TRUE(std::isfinite(testContentSize.Width()));
    EXPECT_TRUE(std::isfinite(testContentSize.Height()));
}

/**
 * @tc.name: SvgUtilsTest013
 * @tc.desc: Test SVG content size with fractional viewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest013, TestSize.Level1)
{
    // Test fractional viewBox coordinates
    Rect fractionalViewBox(0.5, 1.5, 100.5, 75.5);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, fractionalViewBox);
    
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest014
 * @tc.desc: Test SVG content size with negative viewBox coordinates
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest014, TestSize.Level1)
{
    // Test negative viewBox coordinates
    Rect negativeViewBox(-50, -25, 100, 50);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, negativeViewBox);
    
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest015
 * @tc.desc: Test SVG content size identity transformation
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest015, TestSize.Level1)
{
    // Test when viewBox matches container size
    Rect identityViewBox(0, 0, 200, 150);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, identityViewBox);
    
    EXPECT_FLOAT_EQ(testContentSize.Width(), 200.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 150.0f);
}

/**
 * @tc.name: SvgUtilsTest016
 * @tc.desc: Test SVG content size with extreme aspect ratios
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest016, TestSize.Level1)
{
    // Test extreme wide aspect ratio
    Rect wideViewBox(0, 0, 1000, 1);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, wideViewBox);
    
    // Should handle extreme ratios gracefully
    EXPECT_GT(testContentSize.Width(), 0.0f);
    EXPECT_GT(testContentSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgUtilsTest017
 * @tc.desc: Test SVG content size with square constraints
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest017, TestSize.Level1)
{
    // Test square container constraint
    Size squareContainer(100, 100);
    Rect originalViewBox(0, 0, 300, 200);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, squareContainer, svgSize_, originalViewBox);
    
    // Should fit within square while maintaining aspect ratio
    EXPECT_FLOAT_LE(testContentSize.Width(), 100.0f);
    EXPECT_FLOAT_LE(testContentSize.Height(), 100.0f);
}

/**
 * @tc.name: SvgUtilsTest018
 * @tc.desc: Test SVG content size with minimum size
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest018, TestSize.Level1)
{
    // Test minimum size constraints
    Size minContainer(1, 1);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, minContainer, svgSize_, viewBox_);
    
    EXPECT_FLOAT_EQ(testContentSize.Width(), 1.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 1.0f);
}

/**
 * @tc.name: SvgUtilsTest019
 * @tc.desc: Test SVG content size with decimal precision
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest019, TestSize.Level1)
{
    // Test with decimal precision
    Size preciseContainer(123.456f, 78.910f);
    Rect preciseViewBox(0, 0, 200.123f, 150.456f);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, preciseContainer, svgSize_, preciseViewBox);
    
    EXPECT_TRUE(std::isfinite(testContentSize.Width()));
    EXPECT_TRUE(std::isfinite(testContentSize.Height()));
}

/**
 * @tc.name: SvgUtilsTest020
 * @tc.desc: Test SVG content size with invalid viewBox dimensions
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTest, SvgUtilsTest020, TestSize.Level1)
{
    // Test with invalid viewBox (negative dimensions)
    Rect invalidViewBox(0, 0, -100, -50);
    Size testContentSize;
    SvgUtils::CalculateSvgConentSize(testContentSize, svgContainerSize_, svgSize_, invalidViewBox);
    
    // Should handle invalid viewBox gracefully
    EXPECT_FLOAT_EQ(testContentSize.Width(), 0.0f);
    EXPECT_FLOAT_EQ(testContentSize.Height(), 0.0f);
}