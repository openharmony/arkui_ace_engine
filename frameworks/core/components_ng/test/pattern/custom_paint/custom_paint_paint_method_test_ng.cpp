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

#include <cmath>
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
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/image/image_object.h"
#include "core/components/common/properties/decoration.h"

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
    void UpdateRecordingCanvas(SizeF frameSize, RefPtr<CanvasPaintMethod> paintMethod);
};

RefPtr<CanvasPaintMethod> CustomPaintPaintMethodTestNg::CreateCanvasPaintMethod()
{
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    RefPtr<RenderingContext2DModifier> contentModifier = AceType::MakeRefPtr<RenderingContext2DModifier>();
    return AceType::MakeRefPtr<CanvasPaintMethod>(pipelineContext, contentModifier);
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

void CustomPaintPaintMethodTestNg::UpdateRecordingCanvas(SizeF frameSize, RefPtr<CanvasPaintMethod> paintMethod)
{
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
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

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
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

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

#ifndef NEW_SKIA
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
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

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
    paintMethod->InitImagePaint(paintMethod->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);

    /**
     * @tc.steps3: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "low".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kLow_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityLow;
    paintMethod->InitImagePaint(paintMethod->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kLow_SkFilterQuality);

    /**
     * @tc.steps4: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "medium".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kMedium_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityMedium;
    paintMethod->InitImagePaint(paintMethod->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kMedium_SkFilterQuality);

    /**
     * @tc.steps5: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "high".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kHigh_SkFilterQuality.
     */
    paintMethod->smoothingQuality_ = qualityHigh;
    paintMethod->InitImagePaint(paintMethod->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kHigh_SkFilterQuality);

    /**
     * @tc.steps6: Test the function InitImagePaint with smoothingEnabled_ = false.
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod->SetSmoothingEnabled(false);
    paintMethod->InitImagePaint(paintMethod->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);
}
#endif

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
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath with rule = CanvasFillRule::NONZERO.
     * @tc.expected: The value of getFillType is SkPath::FillType::kWinding_FillType.
     */
    CanvasFillRule rule = CanvasFillRule::NONZERO;
    paintMethod->SetFillRuleForPath(rule);
#ifndef NEW_SKIA
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPath::FillType::kWinding_FillType);
#else
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPathFillType::kWinding);
#endif
    /**
     * @tc.steps2: Test the function SetFillRuleForPath with rule = CanvasFillRule::EVENODD.
     * @tc.expected: The value of getFillType is SkPath::FillType::kEvenOdd_FillType.
     */
    rule = CanvasFillRule::EVENODD;
    paintMethod->SetFillRuleForPath(rule);
#ifndef NEW_SKIA
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPath::FillType::kEvenOdd_FillType);
#else
    EXPECT_EQ(paintMethod->skPath_.getFillType(), SkPathFillType::kEvenOdd);
#endif
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
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function SetFillRuleForPath2D with rule = CanvasFillRule::NONZERO.
     * @tc.expected: The value of getFillType is SkPath::FillType::kWinding_FillType.
     */
    CanvasFillRule rule = CanvasFillRule::NONZERO;
    paintMethod->SetFillRuleForPath2D(rule);
#ifndef NEW_SKIA
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPath::FillType::kWinding_FillType);
#else
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPathFillType::kWinding);
#endif

    /**
     * @tc.steps2: Test the function SetFillRuleForPath2D with rule = CanvasFillRule::EVENODD.
     * @tc.expected: The value of getFillType is SkPath::FillType::kEvenOdd_FillType.
     */
    rule = CanvasFillRule::EVENODD;
    paintMethod->SetFillRuleForPath2D(rule);
#ifndef NEW_SKIA
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPath::FillType::kEvenOdd_FillType);
#else
    EXPECT_EQ(paintMethod->skPath2d_.getFillType(), SkPathFillType::kEvenOdd);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg006
 * @tc.desc: Test the functions UpdatePaintShader of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function UpdatePaintShader with gradient.type = Ace::GradientType::LINEAR.
     * @tc.expected: The value of GetType is Ace::GradientType::LINEAR.
     */
    Ace::Gradient gradient;
    SkPaint paint;
    OffsetF offset(DEFAULT_DOUBLE10, DEFAULT_DOUBLE10);
    AnimationOption option = AnimationOption();
    gradient.SetType(Ace::GradientType::LINEAR);
    paintMethod->UpdatePaintShader(offset, paint, gradient);
    EXPECT_EQ(gradient.GetType(), Ace::GradientType::LINEAR);

    /**
     * @tc.steps3: Test the function UpdatePaintShader with gradient.type = Ace::GradientType::SWEEP.
     * @tc.expected: The value of GetType is Ace::GradientType::SWEEP.
     */
    gradient.SetType(Ace::GradientType::SWEEP);
    gradient.SetInnerRadius(DEFAULT_DOUBLE0);
    paintMethod->UpdatePaintShader(offset, paint, gradient);
    EXPECT_EQ(gradient.GetType(), Ace::GradientType::SWEEP);

    /**
     * @tc.steps3: Test the function UpdatePaintShader with InnerRadius = DEFAULT_DOUBLE10.
     * @tc.expected: The value of GetInnerRadius is DEFAULT_DOUBLE10.
     */
    gradient.SetType(Ace::GradientType::SWEEP);
    gradient.SetInnerRadius(DEFAULT_DOUBLE10);
    paintMethod->UpdatePaintShader(offset, paint, gradient);
    EXPECT_DOUBLE_EQ(gradient.GetInnerRadius(), DEFAULT_DOUBLE10);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg007
 * @tc.desc: Test the functions DrawSvgImage of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function DrawSvgImage with flag = DEFAULT_INSTANCE_ID.
     * @tc.expected: The value of canvasImage.flag is DEFAULT_INSTANCE_ID.
     */
    PaintWrapper* paintWrapper = nullptr;
    Ace::CanvasImage canvasImage;
    canvasImage.src = "loading";
    canvasImage.flag = DEFAULT_INSTANCE_ID;
    paintMethod->DrawSvgImage(paintWrapper, canvasImage);
    EXPECT_NE(paintMethod->currentSource_.GetSrc(), paintMethod->loadingSource_.GetSrc());
    EXPECT_EQ(canvasImage.flag, DEFAULT_INSTANCE_ID);

    /**
     * @tc.steps2: Test the function DrawSvgImage with flag = DEFAULT_INSTANCE_ID1.
     * @tc.expected: The value of canvasImage.flag is DEFAULT_INSTANCE_ID1.
     */
    canvasImage.flag = DEFAULT_INSTANCE_ID1;
    paintMethod->DrawSvgImage(paintWrapper, canvasImage);
    EXPECT_NE(paintMethod->currentSource_.GetSrc(), paintMethod->loadingSource_.GetSrc());
    EXPECT_EQ(canvasImage.flag, DEFAULT_INSTANCE_ID1);

    /**
     * @tc.steps2: Test the function DrawSvgImage with flag = DEFAULT_INSTANCE_ID2.
     * @tc.expected: The value of canvasImage.flag is DEFAULT_INSTANCE_ID2.
     */
    canvasImage.flag = DEFAULT_INSTANCE_ID2;
    paintMethod->DrawSvgImage(paintWrapper, canvasImage);
    EXPECT_NE(paintMethod->currentSource_.GetSrc(), paintMethod->loadingSource_.GetSrc());
    EXPECT_EQ(canvasImage.flag, DEFAULT_INSTANCE_ID2);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg008
 * @tc.desc: Test the functions PutImageData of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function PutImageData with  imageData.data is null.
     * @tc.expected: The value of imageData.data is null.
     */
    PaintWrapper* paintWrapper = nullptr;
    Ace::ImageData imageData;
    imageData.data = {};
    paintMethod->PutImageData(paintWrapper, imageData);
    EXPECT_TRUE(imageData.data.empty());
}

#ifndef NEW_SKIA
/**
 * @tc.name: CustomPaintPaintMethodTestNg009
 * @tc.desc: Test the functions GetStrokePaint of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test the function GetStrokePaint with Alpha = DEFAULT_DOUBLE1.
     * @tc.expected: The value of getAlphaf is DEFAULT_DOUBLE1.
     */
    SkPaint paint;
    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE1);
    paintMethod->GetStrokePaint(paint);
    EXPECT_DOUBLE_EQ(paint.getAlphaf(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Test the function GetStrokePaint with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of getFillType is not equal to DEFAULT_DOUBLE1.
     */
    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE10);
    paintMethod->GetStrokePaint(paint);
    EXPECT_NE(paint.getAlphaf(), DEFAULT_DOUBLE1);
}
#endif

/**
 * @tc.name: CustomPaintPaintMethodTestNg010
 * @tc.desc: Test the functions FillRect of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function FillRect with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of HasGlobalAlpha is true.
     */
    PaintWrapper* paintWrapper = nullptr;
    Rect rect;
    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE10);
    paintMethod->FillRect(paintWrapper, rect);
    EXPECT_TRUE(paintMethod->globalState_.HasGlobalAlpha());

    /**
     * @tc.steps3: Test the function FillRect with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->FillRect(paintWrapper, rect);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps4: Test the function FillRect with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->FillRect(paintWrapper, rect);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps5: Test the function FillRect with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->FillRect(paintWrapper, rect);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg011
 * @tc.desc: Test the functions StrokeRect of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function StrokeRect with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    PaintWrapper* paintWrapper = nullptr;
    Rect rect;
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->StrokeRect(paintWrapper, rect);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps3: Test the function StrokeRect with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->StrokeRect(paintWrapper, rect);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps4: Test the function StrokeRect with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->StrokeRect(paintWrapper, rect);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg012
 * @tc.desc: Test the functions FillRect of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Fill with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of HasGlobalAlpha is true.
     */

    PaintWrapper* paintWrapper = nullptr;

    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE10);
    paintMethod->Fill(paintWrapper);
    EXPECT_TRUE(paintMethod->globalState_.HasGlobalAlpha());

    /**
     * @tc.steps3: Test the function Fill with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->Fill(paintWrapper);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps4: Test the function Fill with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->Fill(paintWrapper);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps5: Test the function Fill with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->Fill(paintWrapper);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg013
 * @tc.desc: Test the functions Path2DFill of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Path2DFill HasGlobalAlpha.
     * @tc.expected: The value of HasGlobalAlpha is true.
     */

    OffsetF offset;
    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE10);
    paintMethod->Path2DFill(offset);
    EXPECT_TRUE(paintMethod->globalState_.HasGlobalAlpha());

    /**
     * @tc.steps3: Test the function Path2DFill with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->Path2DFill(offset);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps4: Test the function Path2DFill with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->Path2DFill(offset);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps5: Test the function Path2DFill with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->Path2DFill(offset);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg014
 * @tc.desc: Test the functions Stroke of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Stroke with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    PaintWrapper* paintWrapper = nullptr;
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->Stroke(paintWrapper);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps3: Test the function Stroke with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->Stroke(paintWrapper);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps4: Test the function Stroke with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->Stroke(paintWrapper);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg015
 * @tc.desc: Test the functions Path2DStroke of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Path2DStroke with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    OffsetF offset;
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->Path2DStroke(offset);
    EXPECT_TRUE(paintMethod->HasShadow());
#ifndef NEW_SKIA
    /**
     * @tc.steps3: Test the function Path2DStroke with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_OVER.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->Path2DStroke(offset);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_BEGIN);

    /**
     * @tc.steps4: Test the function Path2DStroke with SetType.
     * @tc.expected: The value of GetType is CompositeOperation::SOURCE_IN.
     */
    paintMethod->globalState_.SetType(CompositeOperation::SOURCE_IN);
    paintMethod->Path2DStroke(offset);
    EXPECT_EQ(static_cast<int>(paintMethod->cachePaint_.getBlendMode()), BLENDMODE_VALUE_END);
#endif
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg016
 * @tc.desc: Test the functions Arc of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Arc with angle.
     * @tc.expected: The value of angle is true.
     */
    PaintWrapper* paintWrapper = nullptr;
    ArcParam param;
    param.startAngle = 1.5 * M_PI;    // start angle of the circle
    param.endAngle = 3.5 * M_PI;
    double sweepAngle = (param.endAngle - param.startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Arc(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, FULL_CIRCLE_ANGLE);

    /**
     * @tc.steps3: Test the function Arc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.startAngle = 3.5 * M_PI;    // start angle of the circle
    param.endAngle = 1.3 * M_PI;
    sweepAngle = (param.endAngle - param.startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Arc(paintWrapper, param);
    double results = std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(results, SPECIAL_CIRCLE_ANGLE);

    /**
     * @tc.steps4: Test the function Arc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.startAngle = 1.0 * M_PI;    // start angle of the circle
    param.endAngle = 3.5 * M_PI;
    sweepAngle = (param.endAngle - param.startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    double results2 = FULL_CIRCLE_ANGLE + 0.5 * HALF_CIRCLE_ANGLE;
    paintMethod->Arc(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, results2);

    /**
     * @tc.steps5: Test the function Arc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.anticlockwise = true;
    param.startAngle = 3.5 * M_PI;    // start angle of the circle
    param.endAngle = 0.5 * M_PI;
    sweepAngle = (param.endAngle - param.startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Arc(paintWrapper, param);
    results2 = - FULL_CIRCLE_ANGLE - HALF_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(sweepAngle, results2);

    /**
     * @tc.steps6: Test the function Arc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.anticlockwise = true;
    param.startAngle = 1.5 * M_PI;    // start angle of the circle
    param.endAngle = 3.5 * M_PI;
    sweepAngle = (param.endAngle - param.startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Arc(paintWrapper, param);
    results = std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(results, -FULL_CIRCLE_ANGLE);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg017
 * @tc.desc: Test the functions Path2DArc of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Path2DArc with angle.
     * @tc.expected: The value of angle is true.
     */
    OffsetF offset;
    PathArgs param;
    param.para4 = 1.5 * M_PI;    // start angle of the circle
    param.para5 = 3.5 * M_PI;
    double sweepAngle = (param.para5 - param.para4) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Path2DArc(offset, param);
    EXPECT_DOUBLE_EQ(sweepAngle, FULL_CIRCLE_ANGLE);

    /**
     * @tc.steps3: Test the function Path2DArc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.para4 = 3.5 * M_PI;    // start angle of the circle
    param.para5 = 1.3 * M_PI;
    sweepAngle = (param.para5 - param.para4) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Path2DArc(offset, param);
    double results = std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(results, SPECIAL_CIRCLE_ANGLE);

    /**
     * @tc.steps4: Test the function Path2DArc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.para4 = 1.0 * M_PI;    // start angle of the circle
    param.para5 = 3.5 * M_PI;
    sweepAngle = (param.para5 - param.para4) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Path2DArc(offset, param);
    double results2 = FULL_CIRCLE_ANGLE + 0.5 * HALF_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(sweepAngle, results2);

    /**
     * @tc.steps5: Test the function Path2DArc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.para6 = 1.0;
    param.para4 = 3.5 * M_PI;    // start angle of the circle
    param.para5 = 0.5 * M_PI;
    sweepAngle = (param.para5 - param.para4) * HALF_CIRCLE_ANGLE / M_PI;
    results2 = -HALF_CIRCLE_ANGLE - FULL_CIRCLE_ANGLE;
    paintMethod->Path2DArc(offset, param);
    EXPECT_DOUBLE_EQ(sweepAngle, results2);

    /**
     * @tc.steps6: Test the function Path2DArc with angle.
     * @tc.expected: The value of angle is true.
     */
    param.para6 = 1.0;
    param.para4 = 1.5 * M_PI;    // start angle of the circle
    param.para5 = 3.5 * M_PI;
    sweepAngle = (param.para5 - param.para4) * HALF_CIRCLE_ANGLE / M_PI;
    paintMethod->Path2DArc(offset, param);
    results = std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE;
    EXPECT_DOUBLE_EQ(results, - FULL_CIRCLE_ANGLE);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg018
 * @tc.desc: Test the functions Ellipse of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Ellipse with angle.
     * @tc.expected: The value of angle is true.
     */
    PaintWrapper* paintWrapper = nullptr;
    EllipseParam param;
    param.startAngle = 1.5 * M_PI;    // start angle of the Ellipse
    param.endAngle = 3.5 * M_PI;
    double startAngle = std::fmod(param.startAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = std::fmod(param.endAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    paintMethod->Ellipse(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);

    /**
     * @tc.steps3: Test the function Ellipse with angle.
     * @tc.expected: The value of angle is true.
     */
    param.startAngle = 3.5 * M_PI;    // start angle of the Ellipse
    param.endAngle = 1.3 * M_PI;
    startAngle = std::fmod(param.startAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(param.endAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Ellipse(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, SPECIAL2_CIRCLE_ANGLE);

    /**
     * @tc.steps4: Test the function Ellipse with angle.
     * @tc.expected: The value of angle is true.
     */
    param.anticlockwise = true;
    param.startAngle = -1.5 * M_PI;    // start angle of the Ellipse
    param.endAngle = -3.5 * M_PI;
    startAngle = std::fmod(param.startAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(param.endAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Ellipse(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);

    /**
     * @tc.steps5: Test the function Ellipse with angle.
     * @tc.expected: The value of angle is true.
     */
    param.anticlockwise = true;
    param.rotation = 1.0;
    param.startAngle = -5.5 * M_PI;    // start angle of the Ellipse
    param.endAngle = -2.5 * M_PI;
    startAngle = std::fmod(param.startAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(param.endAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Ellipse(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, HALF_CIRCLE_ANGLE);

    /**
     * @tc.steps6: Test the function Ellipse with angle.
     * @tc.expected: The value of angle is true.
     */
    param.anticlockwise = true;
    param.startAngle = 1.5 * M_PI;    // start angle of the Ellipse
    param.endAngle = 1.5 * M_PI;
    startAngle = std::fmod(param.startAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(param.endAngle, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Ellipse(paintWrapper, param);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg019
 * @tc.desc: Test the functions Path2DEllipse of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Path2DEllipse with angle.
     * @tc.expected: The value of angle is true.
     */
    OffsetF offset;
    PathArgs args;
    args.para6 = 1.5 * M_PI;    // start angle of the Ellipse
    args.para7 = 3.5 * M_PI;
    double startAngle = std::fmod(args.para6, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = std::fmod(args.para7, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    paintMethod->Path2DEllipse(offset, args);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);

    /**
     * @tc.steps3: Test the function Path2DEllipse with angle.
     * @tc.expected: The value of angle is true.
     */
    args.para6 = 3.5 * M_PI;    // start angle of the Ellipse
    args.para7 = 1.3 * M_PI;
    startAngle = std::fmod(args.para6, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(args.para7, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Path2DEllipse(offset, args);
    EXPECT_DOUBLE_EQ(sweepAngle, SPECIAL2_CIRCLE_ANGLE);

    /**
     * @tc.steps4: Test the function Path2DEllipse with angle.
     * @tc.expected: The value of angle is true.
     */
    args.para8 = true;
    args.para6 = -1.5 * M_PI;    // start angle of the Ellipse
    args.para7 = -3.5 * M_PI;
    startAngle = std::fmod(args.para6, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(args.para7, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Path2DEllipse(offset, args);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);

    /**
     * @tc.steps5: Test the function Path2DEllipse with angle.
     * @tc.expected: The value of angle is true.
     */
    args.para8 = true;
    args.para5 = 1.0;
    args.para6 = -5.5 * M_PI;    // start angle of the Ellipse
    args.para7 = -2.5 * M_PI;
    startAngle = std::fmod(args.para6, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(args.para7, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Path2DEllipse(offset, args);
    EXPECT_DOUBLE_EQ(sweepAngle, HALF_CIRCLE_ANGLE);

    /**
     * @tc.steps6: Test the function Path2DEllipse with angle.
     * @tc.expected: The value of angle is true.
     */
    args.para8 = true;
    args.para6 = 1.5 * M_PI;    // start angle of the Ellipse
    args.para7 = 1.5 * M_PI;
    startAngle = std::fmod(args.para6, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = std::fmod(args.para7, M_PI * 2.0) * HALF_CIRCLE_ANGLE / M_PI;
    sweepAngle = endAngle - startAngle;
    paintMethod->Path2DEllipse(offset, args);
    EXPECT_DOUBLE_EQ(sweepAngle, DEFAULT_DOUBLE0);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg020
 * @tc.desc: Test the functions MakeConicGradient of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg020, TestSize.Level1)
{
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    SkPaint paint;
    Ace::Gradient gradient;
    gradient.SetType(Ace::GradientType::CONIC);
    auto result = paintMethod->MakeConicGradient(paint, gradient);
    EXPECT_EQ(result, nullptr);

    AnimatableDimension animatableDimension(2.0);
    gradient.GetConicGradient().centerX = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().centerX.has_value(), true);
    result = paintMethod->MakeConicGradient(paint, gradient);
    EXPECT_EQ(result, nullptr);

    gradient.GetConicGradient().centerY = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().centerY.has_value(), true);
    result = paintMethod->MakeConicGradient(paint, gradient);
    EXPECT_EQ(result, nullptr);

    gradient.GetConicGradient().startAngle = animatableDimension;
    EXPECT_EQ(gradient.GetConicGradient().startAngle.has_value(), true);
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    OHOS::Ace::GradientColor gradientColor3(Color::BLUE);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    gradient.AddColor(gradientColor3);
    result = paintMethod->MakeConicGradient(paint, gradient);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg021
 * @tc.desc: Test the functions UpdatePaintShader of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg021, TestSize.Level1)
{
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    SizeF frameSize;
    UpdateRecordingCanvas(frameSize, paintMethod);

    SkPaint paint;
    Ace::Gradient gradient;
    OffsetF offset(10.0, 10.0);
    gradient.SetType(Ace::GradientType::LINEAR);
    paintMethod->UpdatePaintShader(offset, paint, gradient);
    EXPECT_EQ(paint.getShader(), nullptr);

    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    paintMethod->UpdatePaintShader(offset, paint, gradient);
    EXPECT_NE(paint.getShader(), nullptr);
}

/**
 * @tc.name: CustomPaintPaintMethodTestNg021
 * @tc.desc: Test the functions GetMatrixFromPattern of CustomPaintPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPaintMethodTestNg, CustomPaintPaintMethodTestNg022, TestSize.Level1)
{
    auto paintMethod = CreateCanvasPaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    Ace::Pattern pattern;
    pattern.SetScaleX(1.0f);
    pattern.SetScaleY(1.0f);
    SkMatrix matrix = paintMethod->GetMatrixFromPattern(pattern);
    EXPECT_EQ(matrix.getScaleX(), pattern.GetScaleX());
    EXPECT_EQ(matrix.getScaleY(), pattern.GetScaleY());
    EXPECT_EQ(matrix.getSkewX(), pattern.GetSkewX());
    EXPECT_EQ(matrix.getSkewY(), pattern.GetSkewY());
    EXPECT_EQ(matrix.getTranslateX(), pattern.GetTranslateX());
    EXPECT_EQ(matrix.getTranslateY(), pattern.GetTranslateY());
}
} // namespace OHOS::Ace::NG
