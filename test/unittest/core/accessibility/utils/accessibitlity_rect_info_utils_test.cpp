/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_rect_info_utils.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityRealRectInfoTest  : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    PointT<int32_t> defaultPoint_ = PointT<int32_t>(0, 0);
    VectorF defaultScale_ = VectorF(1.0f, 1.0f);

    int32_t componentX_ = 100;
    int32_t componentY_ = 200;
    float componentWidth_ = 300;
    float componentHeight_ = 400;
    float scaleX_ = 0.5f;
    float scaleY_ = 0.5f;
    float scaleIgnoreX_ = 1.0f;
    float scaleIgnoreY_ = 1.0f;
    int32_t defaultDegree_ = 90;
};

void AccessibilityRealRectInfoTest ::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityRealRectInfoTest ::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityRealRectInfo_Constructor_Initialization
 * @tc.desc: Verify constructor initializes member variables correctly
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, ConstructorInitialization)
{
    /**
     * @tc.step1: Create instance with initial parameters
     * @tc.expected: Internal state matches construction values
     */
    AccessibilityRealRectInfo rect(defaultPoint_, componentWidth_, componentHeight_, defaultDegree_, defaultScale_);

    /**
     * @tc.step2: Verify default rotation calculation
     * @tc.expected: Returns 0 rotation for identical points
     */
    EXPECT_EQ(rect.GetRotationByConner(defaultPoint_, defaultPoint_), 0);
}

/**
 * @tc.name: AccessibilityRealRectInfo_Rotation_Quadrant_Detection
 * @tc.desc: Test rotation calculation for all quadrants and edge cases
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, RotationCalculationFourQuadrants)
{
    struct RotationTestParam {
        PointT<int32_t> leftTop;
        PointT<int32_t> rightBottom;
        int32_t expectedRotation;
    };

    const std::vector<RotationTestParam> testCases = {
        { {10, 20}, {30, 40}, 0 },     // Normal bottom-right quadrant
        { {30, 20}, {10, 40}, 90 },     // Left quadrant rotation
        { {30, 40}, {10, 20}, 180 },    // Top-left quadrant
        { {10, 40}, {30, 20}, 270 },    // Bottom quadrant rotation
        { {10, 10}, {10, 10}, 0 }       // Identical points case
    };

    for (const auto& testCase : testCases) {
        /**
         * @tc.step1: Initialize instance with test parameters
         * @tc.expected: Instance created without errors
         */
        AccessibilityRealRectInfo rect(defaultPoint_, 0, 0, 0, defaultScale_);

        /**
         * @tc.step2: Calculate rotation for test points
         * @tc.expected: Rotation matches quadrant expectation
         */
        EXPECT_EQ(rect.GetRotationByConner(testCase.leftTop, testCase.rightBottom), testCase.expectedRotation);
    }
}

/**
 * @tc.name: AccessibilityRealRectInfo_Scale_Accumulation
 * @tc.desc: Verify scale factor multiplication logic
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, ScaleFactorAccumulation)
{
    /**
     * @tc.step1: Initialize with base scale (1.0, 1.0)
     * @tc.expected: Initial scale values set correctly
     */
    AccessibilityRealRectInfo rect(defaultPoint_, componentWidth_, componentHeight_, 0, VectorF(0.5f, 0.6f));

    /**
     * @tc.step2: Apply parent scale factors
     * @tc.expected: Scale values multiply correctly
     */
    VectorF parentScale(0.8f, 0.4f);
    rect.UpdateScale(parentScale);
    EXPECT_FLOAT_EQ(rect.scale_.x, 0.4f);
    EXPECT_FLOAT_EQ(rect.scale_.y, 0.24f);
}

/**
 * @tc.name: AccessibilityRealRectInfo_Coordinate_Mapping_NoRotation
 * @tc.desc: Test coordinate transformation without rotation
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, CoordinateMappingNoRotation)
{
    /**
     * @tc.step1: Create instance with 0° rotation
     * @tc.expected: Rotation initialized to 0 degrees
     */
    AccessibilityRealRectInfo rect(PointT<int32_t>(componentX_, componentY_),
        componentWidth_, componentHeight_, 0, VectorF(scaleX_, scaleY_));

    /**
     * @tc.step2: Apply scaling to test point
     * @tc.expected: Point coordinates scaled correctly
     */
    int32_t componentTestX = 50;
    int32_t componentTestY = 60;
    PointT<int32_t> testPoint(componentTestX, componentTestY);
    rect.UpdatePointWithScale(testPoint);
    EXPECT_EQ(testPoint.GetX(), componentTestX * scaleX_);
    EXPECT_EQ(testPoint.GetY(), componentTestY * scaleY_);

    /**
     * @tc.step3: Transform to real coordinates
     * @tc.expected: Final coordinates match expected values
     */
    rect.UpdatePointToReal(testPoint);

    EXPECT_EQ(testPoint.GetX(), componentX_ + componentTestX * scaleX_);
    EXPECT_EQ(testPoint.GetY(), componentY_ + componentTestY * scaleY_);
}

/**
 * @tc.name: AccessibilityRealRectInfo_90Degree_Rotation_Transform
 * @tc.desc: Verify coordinate transformation with 90° rotation
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, CoordinateMapping90DegreeRotation)
{
    /**
     * @tc.step1: Create instance with 90° rotation
     * @tc.expected: Rotation initialized to 90 degrees
     */
    AccessibilityRealRectInfo rect(PointT<int32_t>(componentX_, componentY_),
        componentWidth_, componentHeight_, defaultDegree_, VectorF(scaleIgnoreX_, scaleIgnoreY_));

    /**
     * @tc.step2: Transform test coordinates
     * @tc.expected: Coordinates follow rotation matrix calculation
     */
    int32_t componentTestX = 50;
    int32_t componentTestY = 60;
    PointT<int32_t> testPoint(componentTestX, componentTestY);
    rect.UpdatePointToReal(testPoint);
    EXPECT_EQ(testPoint.GetX(), componentX_ - componentTestY);
    EXPECT_EQ(testPoint.GetY(), componentY_ + componentTestX);
}

/**
 * @tc.name: AccessibilityRealRectInfo_Rect_Generation_Workflow
 * @tc.desc: Test complete rectangle generation process
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, RectInfoGenerationWorkflow)
{
    /**
     * @tc.step1: Initialize parent rectangle parameters and Define relative corner points
     * @tc.expected: Parent properties set correctly
     */
    int32_t parentScaleX = 2.0f;
    int32_t parentScaleY = 2.0f;
    int32_t parentDegree = 90;
    AccessibilityRealRectInfo parentRect(
        PointT<int32_t>(0, 0), 200.0f, 300.0f, parentDegree, VectorF(parentScaleX, parentScaleY));
    int32_t componentTestX = 10;
    int32_t componentTestY = 20;
    PointT<int32_t> leftTop(componentTestX, componentTestY);
    int32_t componentTestWidth = 20;
    int32_t componentTestHeight = 30;
    PointT<int32_t> rightBottom(componentTestX + componentTestWidth, componentTestY + componentTestHeight);
    float componentTestScaleX = 1.5f;
    float componentTestScaleY = 1.5f;
    VectorF scale(componentTestScaleX, componentTestScaleY);

    /**
     * @tc.step2: Generate new rectangle info
     * @tc.expected: Dimensions and rotation match expectations
     */
    auto newRect = parentRect.GenerateRectInfoByRelativeConner(leftTop, rightBottom, scale);

    EXPECT_FLOAT_EQ(newRect.width_, componentTestHeight * parentScaleY);
    EXPECT_EQ(newRect.rotation_, parentDegree);
    EXPECT_FLOAT_EQ(newRect.scale_.x, componentTestScaleX * parentScaleX);
    EXPECT_FLOAT_EQ(newRect.scale_.y, componentTestScaleY * parentScaleY);
}

/**
 * @tc.name: AccessibilityRealRectInfo_Zero_Dimension_Handling
 * @tc.desc: Verify zero dimension handling logic
 * @tc.type: FUNC
 */
TEST_F(AccessibilityRealRectInfoTest, ZeroDimensionHandling)
{
    /**
     * @tc.step1: Create instance with zero dimensions
     * @tc.expected: Width/height initialized to zero
     */
    AccessibilityRealRectInfo rect(PointT<int32_t>(componentX_, componentY_),
        0, 0, 0, VectorF(1.0f, 1.0f));

    /**
     * @tc.step2: Transform origin point
     * @tc.expected: Coordinates remain at original position
     */
    PointT<int32_t> testPoint(0, 0);
    rect.UpdatePointToReal(testPoint);
    EXPECT_EQ(testPoint.GetX(), componentX_);
    EXPECT_EQ(testPoint.GetY(), componentY_);
}
} // namespace OHOS::Ace::NG