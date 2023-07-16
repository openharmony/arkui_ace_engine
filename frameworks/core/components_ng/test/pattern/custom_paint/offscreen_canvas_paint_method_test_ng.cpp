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
#include "include/core/SkColorFilter.h"
#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"
#include "core/components_ng/test/pattern/custom_paint/mock/mock_paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_interface.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#include "core/image/image_object.h"

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
 * @tc.desc: Test functions IsPercentStr, PxStrToDouble and BlurStrToDouble of OffscreenCanvasPaintMethod.
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
 * @tc.name: OffscreenCanvasPaintMethodTestNg002
 * @tc.desc: Test the function SetGrayFilter of OffscreenCanvasPaintMethod.
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
    float matrixGet[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetGrayFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("30%");
    constexpr float value = 1 - 0.3f;
    constexpr float matrix0 = LUMR + (1 - LUMR) * value;
    constexpr float matrix5 = LUMR - LUMR * value;
    constexpr float matrix10 = LUMR - LUMR * value;

    constexpr float matrix1 = LUMG - LUMG * value;
    constexpr float matrix6 = LUMG + (1 - LUMG) * value;
    constexpr float matrix11 = LUMG - LUMG * value;

    constexpr float matrix2 = LUMB - LUMB * value;
    constexpr float matrix7 = LUMB - LUMB * value;
    constexpr float matrix12 = LUMB + (1 - LUMB) * value;
    constexpr float matrix18 = 1.0f;

    paintMethod->SetGrayFilter(percentStr, paintMethod->imagePaint_);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrixGet);

    EXPECT_DOUBLE_EQ(matrixGet[0], matrix0);
    EXPECT_DOUBLE_EQ(matrixGet[5], matrix5);
    EXPECT_DOUBLE_EQ(matrixGet[10], matrix10);
    EXPECT_DOUBLE_EQ(matrixGet[1], matrix1);
    EXPECT_DOUBLE_EQ(matrixGet[6], matrix6);
    EXPECT_DOUBLE_EQ(matrixGet[11], matrix11);
    EXPECT_DOUBLE_EQ(matrixGet[2], matrix2);
    EXPECT_DOUBLE_EQ(matrixGet[7], matrix7);
    EXPECT_DOUBLE_EQ(matrixGet[12], matrix12);
    EXPECT_DOUBLE_EQ(matrixGet[18], matrix18);

    /**
     * @tc.steps3: Call the function SetGrayFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2");
    paintMethod->SetGrayFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], LUMR);
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR);
    EXPECT_DOUBLE_EQ(matrixGet[1], LUMG);
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG);
    EXPECT_DOUBLE_EQ(matrixGet[11], LUMG);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB);
    EXPECT_DOUBLE_EQ(matrixGet[7], LUMB);
    EXPECT_DOUBLE_EQ(matrixGet[12], LUMB);
    EXPECT_DOUBLE_EQ(matrixGet[18], matrix18);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg003
 * @tc.desc: Test the function SetSepiaFilter of OffscreenCanvasPaintMethod.
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
    float matrixGet[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetSepiaFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    float percentNum = 0.5f;
    paintMethod->SetSepiaFilter(percentStr, paintMethod->imagePaint_);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], 1.0f - percentNum * 0.607f);
    EXPECT_DOUBLE_EQ(matrixGet[1], percentNum * 0.769f);
    EXPECT_DOUBLE_EQ(matrixGet[2], percentNum * 0.189f);
    EXPECT_DOUBLE_EQ(matrixGet[5], percentNum * 0.349f);
    EXPECT_DOUBLE_EQ(matrixGet[6], 1.0f - percentNum * 0.314f);
    EXPECT_DOUBLE_EQ(matrixGet[7], percentNum * 0.168f);
    EXPECT_DOUBLE_EQ(matrixGet[10], percentNum * 0.272f);
    EXPECT_DOUBLE_EQ(matrixGet[11], percentNum * 0.534f);
    EXPECT_DOUBLE_EQ(matrixGet[12], 1.0f - percentNum * 0.869f);
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);

    /**
     * @tc.steps3: Call the function SetSepiaFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2");
    constexpr float matrix1_100percent = 0.769f;
    constexpr float matrix5_100percent = 0.349f;
    constexpr float matrix11_100percent = 0.534f;
    paintMethod->SetSepiaFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[1], matrix1_100percent);
    EXPECT_DOUBLE_EQ(matrixGet[5], matrix5_100percent);
    EXPECT_DOUBLE_EQ(matrixGet[11], matrix11_100percent);
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg004
 * @tc.desc: Test the function SetInvertFilter of OffscreenCanvasPaintMethod.
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
     * @tc.steps2: Call the function SetInvertFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.0;
    constexpr float matrix14 = 0.5;
    constexpr float matrix118 = 1.0;
    paintMethod->SetInvertFilter(percentStr, paintMethod->imagePaint_);
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
    constexpr float matrix20 = -1.0f;
    constexpr float matrix24 = 1.0f;
    constexpr float matrix218 = 1.0f;
    paintMethod->SetInvertFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix24);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg005
 * @tc.desc: Test the function SetOpacityFilter of OffscreenCanvasPaintMethod.
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
     * @tc.steps2: Call the function SetOpacityFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 1.0;
    constexpr float matrix118 = 0.5;
    paintMethod->SetOpacityFilter(percentStr, paintMethod->imagePaint_);
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
    constexpr float matrix218 = 1.0;
    paintMethod->SetOpacityFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg006
 * @tc.desc: Test the function SetBrightnessFilter of OffscreenCanvasPaintMethod.
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
     * @tc.steps2: Call the function SetBrightnessFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.5;
    constexpr float matrix118 = 1.0;
    paintMethod->SetBrightnessFilter(percentStr, paintMethod->imagePaint_);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix118);

    /**
     * @tc.steps3: Call the function SetBrightnessFilter with negative number.
     * @tc.expected: The function does not work.
     */
    std::string nonPercentStr("-2.0");
    paintMethod->SetBrightnessFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix10);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg007
 * @tc.desc: Test the function SetContrastFilter of OffscreenCanvasPaintMethod.
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
     * @tc.steps2: Call the function SetContrastFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    constexpr float matrix10 = 0.5;
    constexpr float matrix14 = 0.5 * (1 - 0.5);
    constexpr float matrix118 = 1.0;
    paintMethod->SetContrastFilter(percentStr, paintMethod->imagePaint_);
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
    paintMethod->SetContrastFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrix1);
    EXPECT_DOUBLE_EQ(matrix1[0], matrix20);
    EXPECT_DOUBLE_EQ(matrix1[4], matrix24);
    EXPECT_DOUBLE_EQ(matrix1[18], matrix218);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg008
 * @tc.desc: Test the function SetSaturateFilter of OffscreenCanvasPaintMethod.
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
    float matrixGet[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetSaturateFilter with percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string percentStr("50%");
    float percentNum = 0.5f;
    paintMethod->SetSaturateFilter(percentStr, paintMethod->imagePaint_);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], LUMR + (1 - LUMR) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR - LUMR * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR - LUMR * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[1], LUMG - LUMG * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG + (1 - LUMG) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[11], LUMG - LUMG * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB - LUMB * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[7], LUMB - LUMB * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[12], LUMB + (1 - LUMB) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);

    /**
     * @tc.steps3: Call the function SetSaturateFilter with non-percent string.
     * @tc.expected: The values at the corresponding positions of the matrix1 are calculated correctly.
     */
    std::string nonPercentStr("2.0");
    percentNum = 2.0f;
    paintMethod->SetSaturateFilter(nonPercentStr, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], LUMR + (1 - LUMR) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR - LUMR * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR - LUMR * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[1], LUMG - LUMG * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG + (1 - LUMG) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[11], LUMG - LUMG * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB - LUMB * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[7], LUMB - LUMB * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[12], LUMB + (1 - LUMB) * percentNum);
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg009
 * @tc.desc: Test the function SetHueRotateFilter of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    float matrixGet[20] = { 0 };

    /**
     * @tc.steps2: Call the function SetHueRotateFilter with "420deg".
     * @tc.expected: The value at the position 0 of the matrix1 is equal to 0.5.
     */
    std::string filterParam1("660deg");
    float radius = 660 / HALF_CIRCLE_ANGLE * M_PI;
    float cosValue = std::cos(radius);
    float sinValue = std::sin(radius);
    paintMethod->SetHueRotateFilter(filterParam1, paintMethod->imagePaint_);
    auto* skColorFilter1 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter1->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], LUMR + cosValue * (1 - LUMR) + sinValue * (-LUMR));
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR + cosValue * (-LUMR) + sinValue * 0.143f);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR + cosValue * (-LUMR) + sinValue * (LUMR - 1));
    EXPECT_DOUBLE_EQ(matrixGet[1], LUMG + cosValue * (-LUMG) + sinValue * (-LUMG));
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG + cosValue * (1 - LUMG) + sinValue * 0.140f);
    EXPECT_DOUBLE_EQ(matrixGet[11], LUMG + cosValue * (-LUMG) + sinValue * LUMG);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB + cosValue * (-LUMB) + sinValue * (1 - LUMB));
    EXPECT_DOUBLE_EQ(matrixGet[7], LUMB + cosValue * (-LUMB) + sinValue * (-0.283f));
    EXPECT_DOUBLE_EQ(matrixGet[12], LUMB + cosValue * (1 - LUMB) + sinValue * LUMB);
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);

    /**
     * @tc.steps3: Call the function SetHueRotateFilter with "3.142rad".
     * @tc.expected: The value at the position 1 of the matrix1 is equal to 0.5.
     */
    std::string filterParam2("3.14rad");
    cosValue = std::cos(3.14f);
    sinValue = std::sin(3.14f);
    paintMethod->SetHueRotateFilter(filterParam2, paintMethod->imagePaint_);
    auto* skColorFilter2 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter2->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[0], LUMR + cosValue * (1 - LUMR) + sinValue * (-LUMR));
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR + cosValue * (-LUMR) + sinValue * 0.143f);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR + cosValue * (-LUMR) + sinValue * (LUMR - 1));
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG + cosValue * (1 - LUMG) + sinValue * 0.140f);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB + cosValue * (-LUMB) + sinValue * (1 - LUMB));
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);

    /**
     * @tc.steps3: Call the function SetHueRotateFilter with "0.2turn".
     * @tc.expected: The value at the position 2 of the matrix1 is equal to 0.6.
     */
    std::string filterParam3("0.25turn");
    cosValue = std::cos(0.25f * 2 * M_PI);
    sinValue = std::sin(0.25f * 2 * M_PI);
    paintMethod->SetHueRotateFilter(filterParam3, paintMethod->imagePaint_);
    auto* skColorFilter3 = paintMethod->imagePaint_.getColorFilter();
    skColorFilter3->asAColorMatrix(matrixGet);
    EXPECT_DOUBLE_EQ(matrixGet[5], LUMR + cosValue * (-LUMR) + sinValue * 0.143f);
    EXPECT_DOUBLE_EQ(matrixGet[10], LUMR + cosValue * (-LUMR) + sinValue * (LUMR - 1));
    EXPECT_DOUBLE_EQ(matrixGet[6], LUMG + cosValue * (1 - LUMG) + sinValue * 0.140f);
    EXPECT_DOUBLE_EQ(matrixGet[2], LUMB + cosValue * (-LUMB) + sinValue * (1 - LUMB));
    EXPECT_DOUBLE_EQ(matrixGet[7], LUMB + cosValue * (-LUMB) + sinValue * (-0.283f));
    EXPECT_DOUBLE_EQ(matrixGet[18], 1.0f);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg010
 * @tc.desc: Test the function GetFilterType of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    const std::string nullStr;
    const std::string targetType("targetType");
    const std::string targetParam("targetParam");
    FilterType filterType;
    std::string filterParam;

    /**
     * @tc.steps2: Call the function GetFilterType with filterParam_ = "".
     * @tc.expected: The return value is false and the output string is null.
     */
    paintMethod->filterParam_ = "";
    EXPECT_FALSE(paintMethod->GetFilterType(filterType, filterParam));
    EXPECT_EQ(filterType, FilterType::NONE);
    EXPECT_EQ(filterParam, nullStr);

    /**
     * @tc.steps3: Call the function GetFilterType with filterParam_ = "targetType(targetParam".
     * @tc.expected: The return value is false and the output string is corrected.
     */
    paintMethod->filterParam_ = "blur(targetParam";
    EXPECT_FALSE(paintMethod->GetFilterType(filterType, filterParam));
    EXPECT_EQ(filterType, FilterType::BLUR);
    EXPECT_EQ(filterParam, targetParam);

    /**
     * @tc.steps4: Call the function GetFilterType with filterParam_ = "targetType(targetParam)".
     * @tc.expected: The return value is true and the output string is corrected.
     */
    paintMethod->filterParam_ = "blur(targetParam)";
    EXPECT_TRUE(paintMethod->GetFilterType(filterType, filterParam));
    EXPECT_EQ(filterType, FilterType::BLUR);
    EXPECT_EQ(filterParam, targetParam);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg011
 * @tc.desc: Test functions ImageObjReady and ImageObjFailed of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    const std::string nullSrc;
    const std::string loadingSrc("loading");

    /**
     * @tc.steps2: Call the function ImageObjFailed.
     * @tc.expected: The srcs of loadingSource_ and currentSource_ are equal to nullSrc.
     */
    paintMethod->ImageObjFailed();
    EXPECT_EQ(paintMethod->loadingSource_.GetSrc(), nullSrc);
    EXPECT_EQ(paintMethod->currentSource_.GetSrc(), nullSrc);

    /**
     * @tc.steps3: Call the function ImageObjReady with imageObj->isSvg_ = false.
     * @tc.expected: The srcs of currentSource_ is not equal to loadingSrc.
     */
    ImageSourceInfo source;
    Size imageSize;
    auto imageObj = AceType::MakeRefPtr<Ace::SvgSkiaImageObject>(source, imageSize, 0, nullptr);
    imageObj->isSvg_ = false;
    paintMethod->loadingSource_.SetSrc(loadingSrc);
    paintMethod->ImageObjReady(imageObj);
    EXPECT_NE(paintMethod->currentSource_.GetSrc(), loadingSrc);

    /**
     * @tc.steps4: Call the function ImageObjReady with imageObj->isSvg_ = true.
     * @tc.expected: The srcs of currentSource_ is equal to loadingSrc.
     */
    imageObj->isSvg_ = true;
    paintMethod->loadingSource_.SetSrc(loadingSrc);
    paintMethod->ImageObjReady(imageObj);
    EXPECT_EQ(paintMethod->currentSource_.GetSrc(), loadingSrc);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg012
 * @tc.desc: Test the function HasImageShadow of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    const std::string imageShadowAttr1("0px 0px 0px black");
    const std::string imageShadowAttr2("1px 0px 0px black");

    /**
     * @tc.steps2: Call the function HasImageShadow with imageShadowAttr1.
     * @tc.expected: The return value is false.
     */

    EXPECT_FALSE(paintMethod->HasImageShadow());
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg013
 * @tc.desc: Test the function GetBaselineOffset of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    std::unique_ptr<MockParagraph> mockParagraph = std::make_unique<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetMaxIntrinsicWidth()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetAlphabeticBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetIdeographicBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    std::unique_ptr<txt::Paragraph> paragraph(std::move(mockParagraph));

    /**
     * @tc.steps2: Test functions GetAlignOffset.
     * @tc.expected: The return value is affected by the second parameter.
     */
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::LEFT, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::RIGHT, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::CENTER, paragraph), -DEFAULT_DOUBLE10 / 2);
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::JUSTIFY, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::START, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->GetAlignOffset(TextAlign::END, paragraph), -DEFAULT_DOUBLE10);
}

/**
 * @tc.name: OffscreenCanvasPaintMethodTestNg014
 * @tc.desc: Test the function SetPaintImage of OffscreenCanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(OffscreenCanvasPaintMethodTestNg, OffscreenCanvasPaintMethodTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateOffscreenCanvasPaintMethod(CANVAS_WIDTH, CANVAS_HEIGHT);
    ASSERT_NE(paintMethod, nullptr);
    std::unique_ptr<MockParagraph> mockParagraph = std::make_unique<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetMaxIntrinsicWidth()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetAlphabeticBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetIdeographicBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    std::unique_ptr<txt::Paragraph> paragraph(std::move(mockParagraph));

    /**
     * @tc.steps2: Test functions GetBaselineOffset.
     * @tc.expected: The return value is affected by the first parameter.
     */
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::ALPHABETIC, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::IDEOGRAPHIC, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::TOP, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::BOTTOM, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::MIDDLE, paragraph), -DEFAULT_DOUBLE10 / 2);
    EXPECT_DOUBLE_EQ(paintMethod->GetBaselineOffset(TextBaseline::HANGING, paragraph), DEFAULT_DOUBLE0);
}
} // namespace OHOS::Ace::NG
