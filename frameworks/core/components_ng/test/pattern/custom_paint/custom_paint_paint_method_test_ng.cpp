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
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/image/image_object.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class CustomPaintPaintMethodTestNg : public testing::Test {
public:
    static RefPtr<CanvasPaintMethod> CreateCanvasPaintMethod();
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

RefPtr<CanvasPaintMethod> CustomPaintPaintMethodTestNg::CreateCanvasPaintMethod()
{
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    return AceType::MakeRefPtr<CanvasPaintMethod>(pipelineContext);
}

void CustomPaintPaintMethodTestNg::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPaintMethodTestNg SetUpTestCase";
}

void CustomPaintPaintMethodTestNg::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPaintMethodTestNg TearDownTestCase";
}

void CustomPaintPaintMethodTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "CustomPaintPaintMethodTestNg SetUp";
}

void CustomPaintPaintMethodTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "CustomPaintPaintMethodTestNg TearDown";
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg001
 * @tc.desc: Test the function HasShadow of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function InitFilterFunc.
     * @tc.expected: Some of the specified functions are added to the map HasShadow.
     */
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE0);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE0);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE0);
    EXPECT_FALSE(paintMethod->HasShadow());
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg002
 * @tc.desc: Test the function SetLineDash of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function SetLineDash.
     * @tc.expected: Some of the specified value are added to the LineDash.lineDash.
     */
    SkPaint paint;
    EXPECT_EQ(paint.getPathEffect(), nullptr);
    const std::vector<double> lineDash1 = {};
    paintMethod->strokeState_.SetLineDash(lineDash1);
    paintMethod->UpdateLineDash(paint);
    EXPECT_EQ(paint.getPathEffect(), nullptr);

    /**
     * @tc.steps3: Call the function SetLineDash.
     * @tc.expected: Some of the specified value are added to the LineDash.lineDash.
     */
    const std::vector<double> lineDash2 = {10, 20};
    paintMethod->strokeState_.SetLineDash(lineDash2);
    paintMethod->UpdateLineDash(paint);
    EXPECT_NE(paint.getPathEffect(), nullptr);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg003
 * @tc.desc: Test the functions InitImagePaint of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps1: initialize parameters.
     */
    const std::string qualityUndefined("undefined");
    const std::string qualityLow("low");
    const std::string qualityMedium("medium");
    const std::string qualityHigh("high");

    /**
     * @tc.steps2: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "undefined".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod->SetSmoothingEnabled(true);
    paintMethod->smoothingQuality_ = qualityUndefined;
    paintMethod->InitImagePaint();
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);

    /**
     * @tc.steps3: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "low".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kLow_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityLow;
    paintMethod->InitImagePaint();
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kLow_SkFilterQuality);

    /**
     * @tc.steps4: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "medium".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kMedium_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityMedium;
    paintMethod->InitImagePaint();
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kMedium_SkFilterQuality);

    /**
     * @tc.steps5: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "high".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kHigh_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityHigh;
    paintMethod->InitImagePaint();
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kHigh_SkFilterQuality);

    /**
     * @tc.steps6: Test the function InitImagePaint with smoothingEnabled_ = false.
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod->SetSmoothingEnabled(false);
    paintMethod->InitImagePaint();
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg004
 * @tc.desc: Test the functions SetFillRuleForPath of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath with rule = CanvasFillRule::NONZERO.
     * @tc.expected: The value of getFillType is SkPath::FillType::kWinding_FillType.
     */
    CanvasFillRule rule = CanvasFillRule::NONZERO;
    paintMethod->SetFillRuleForPath(rule);
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPath::FillType::kWinding_FillType);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath with rule = CanvasFillRule::EVENODD.
     * @tc.expected: The value of getFillType is SkPath::FillType::kEvenOdd_FillType.
     */
    rule = CanvasFillRule::EVENODD;
    paintMethod->SetFillRuleForPath(rule);
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPath::FillType::kEvenOdd_FillType);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg005
 * @tc.desc: Test the functions SetFillRuleForPath2D of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath2D with rule = CanvasFillRule::NONZERO.
     * @tc.expected: The value of getFillType is SkPath::FillType::kWinding_FillType.
     */
    CanvasFillRule rule = CanvasFillRule::NONZERO;
    paintMethod->SetFillRuleForPath2D(rule);
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPath::FillType::kWinding_FillType);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath2D with rule = CanvasFillRule::EVENODD.
     * @tc.expected: The value of getFillType is SkPath::FillType::kEvenOdd_FillType.
     */
    rule = CanvasFillRule::EVENODD;
    paintMethod->SetFillRuleForPath2D(rule);
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPath::FillType::kEvenOdd_FillType);
}
} // namespace OHOS::Ace::NG
