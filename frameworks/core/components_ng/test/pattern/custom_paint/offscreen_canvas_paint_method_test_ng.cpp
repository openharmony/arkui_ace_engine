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
#include <optional>

#include "gtest/gtest.h"

#include "core/common/ace_engine.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/test/unittest/geometry/mock_pipeline_base.h"
#include "base/test/unittest/geometry/mock_container.h"
#include "include/core/SkColorFilter.h"


#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"
#include "core/components_ng/test/pattern/custom_paint/mock/mock_paragraph.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class OffscreenCanvasPaintMethodTestNg : public testing::Test {
public:
    // Create the pointer of the class OffscreenCanvasPattern
    static RefPtr<OffscreenCanvasPaintMethod> CreateOffscreenCanvasPaintMethod(int32_t width, int32_t height);
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

RefPtr<OffscreenCanvasPaintMethod> OffscreenCanvasPaintMethodTestNg::CreateOffscreenCanvasPaintMethod(
    int32_t width, int32_t height)
{
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    return AceType::MakeRefPtr<OffscreenCanvasPaintMethod>(pipelineContext, width, height);
}

void OffscreenCanvasPaintMethodTestNg::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "OffscreenCanvasPaintMethodTestNg SetUpTestCase";
}

void OffscreenCanvasPaintMethodTestNg::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "OffscreenCanvasPaintMethodTestNg TearDownTestCase";
}

void OffscreenCanvasPaintMethodTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "OffscreenCanvasPaintMethodTestNg SetUp";
}

void OffscreenCanvasPaintMethodTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "OffscreenCanvasPaintMethodTestNg TearDown";
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg001
 * @tc.desc: Test the function InitFilterFunc of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function InitFilterFunc.
     * @tc.expected: Some of the specified functions are added to the map filterFunc_.
     */
    paintMethod->InitFilterFunc();
    for (const auto& item : FUNCTION_NAMES) {
        EXPECT_NE(paintMethod->filterFunc_.find(item), paintMethod->filterFunc_.end());
    }
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg002
 * @tc.desc: Test functions IsPercentStr, PxStrToDouble and BlurStrToDouble of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function IsPercentStr with percent string.
     * @tc.expected: The return value is true.
     */
    std::string percentStr("50%");
    std::string nonPercentStr("50");
    EXPECT_TRUE(paintMethod->IsPercentStr(percentStr));
    EXPECT_EQ(percentStr, nonPercentStr);

    /**
     * @tc.steps3: Call the function IsPercentStr with non-percent string.
     * @tc.expected: The return value is false.
     */
    EXPECT_FALSE(paintMethod->IsPercentStr(nonPercentStr));
    EXPECT_EQ(nonPercentStr, nonPercentStr);

    /**
     * @tc.steps4: Call the function IsPercentStr with px and non-px string.
     * @tc.expected: The return values are DEFAULT_DOUBLE2 and DEFAULT_DOUBLE0.
     */
    std::string pxStr("2px");
    std::string nonPxStr("2");
    EXPECT_DOUBLE_EQ(paintMethod->PxStrToDouble(pxStr), DEFAULT_DOUBLE2);
    EXPECT_DOUBLE_EQ(paintMethod->PxStrToDouble(nonPxStr), DEFAULT_DOUBLE0);

    /**
     * @tc.steps5: Call the function IsPercentStr with blueStr and non-blueStr string.
     * @tc.expected: The return values are DEFAULT_DOUBLE2 and DEFAULT_DOUBLE0.
     */
    std::string blurStr1("2px");
    std::string blurStr2("2rem");
    std::string nonBlurStr("2");
    constexpr double coefficient = 15.0;
    EXPECT_DOUBLE_EQ(paintMethod->BlurStrToDouble(blurStr1), DEFAULT_DOUBLE2);
    EXPECT_DOUBLE_EQ(paintMethod->BlurStrToDouble(blurStr2), DEFAULT_DOUBLE2 * coefficient);
    EXPECT_DOUBLE_EQ(paintMethod->BlurStrToDouble(nonBlurStr), DEFAULT_DOUBLE0);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg003
 * @tc.desc: Test the function SetGrayFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetGrayFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("30%");
    constexpr float matrix10 = 0.8;
    constexpr float matrix11 = 0.1;
    constexpr float matrix118 = 1.0;
    paintMethod->SetGrayFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[1], matrix11);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetGrayFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2");
    constexpr float matrix21 = 1.0 / 3;
    constexpr float matrix20 = 1 - 2 * matrix21;
    constexpr float matrix218 = 1.0;
    paintMethod->SetGrayFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[1], matrix21);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg004
 * @tc.desc: Test the function SetSepiaFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetSepiaFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 1.0f - 0.5 * 0.6412f;
    constexpr float matrix11 = 0.5 * 0.7044f;
    constexpr float matrix118 = 1.0;
    paintMethod->SetSepiaFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[1], matrix11);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetSepiaFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2");
    constexpr float matrix20 = 1.0f - 1.0 * 0.6412f;
    constexpr float matrix21 = 1.0 * 0.7044f;
    constexpr float matrix218 = 1.0;
    paintMethod->SetSepiaFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[1], matrix21);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg005
 * @tc.desc: Test the function SetInvertFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetInvertFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.0;
    constexpr float matrix14 = 0.5;
    constexpr float matrix118 = 1.0;
    paintMethod->SetInvertFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix14);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetInvertFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2.0");
    constexpr float matrix20 = 1.0 - 2.0 * 2;
    constexpr float matrix24 = 2.0;
    constexpr float matrix218 = 1.0;
    paintMethod->SetInvertFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix24);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg006
 * @tc.desc: Test the function SetOpacityFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetOpacityFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 1.0;
    constexpr float matrix118 = 0.5;
    paintMethod->SetOpacityFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetOpacityFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2.0");
    constexpr float matrix20 = 1.0;
    constexpr float matrix218 = 2.0;
    paintMethod->SetOpacityFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg007
 * @tc.desc: Test the function SetBrightnessFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetBrightnessFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.5;
    constexpr float matrix118 = 1.0;
    paintMethod->SetBrightnessFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetBrightnessFilter with negative number.
     * @tc.expected: The function does not work.
     */
    std::string nonPercentStr("-2.0");
    paintMethod->SetBrightnessFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg008
 * @tc.desc: Test the function SetContrastFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrix1[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetContrastFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.5;
    constexpr float matrix14 = 0.5 * (1 - 0.5);
    constexpr float matrix118 = 1.0;
    paintMethod->SetContrastFilter(percentStr);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix14);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetContrastFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2.0");
    constexpr float matrix20 = 2.0;
    constexpr float matrix24 = 0.5 * (1 - 2.0);
    constexpr float matrix218 = 1.0;
    paintMethod->SetContrastFilter(nonPercentStr);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix24);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}
} // namespace OHOS::Ace::NG
