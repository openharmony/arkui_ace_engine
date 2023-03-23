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
    void CreateBitmap(SizeF frameSize, RefPtr<CanvasPaintMethod> paintMethod);
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

void CustomPaintPaintMethodTestNg::CreateBitmap(SizeF frameSize, RefPtr<CanvasPaintMethod> paintMethod)
{
    auto imageInfo = SkImageInfo::Make(frameSize.Width(), frameSize.Height(),
        SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    paintMethod->canvasCache_.reset();
    paintMethod->cacheBitmap_.reset();
    paintMethod->canvasCache_.allocPixels(imageInfo);
    paintMethod->cacheBitmap_.allocPixels(imageInfo);
    paintMethod->canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    paintMethod->cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    paintMethod->skCanvas_ = std::make_unique<SkCanvas>(paintMethod->canvasCache_);
    paintMethod->cacheCanvas_ = std::make_unique<SkCanvas>(paintMethod->cacheBitmap_);
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
    CreateBitmap(frameSize, paintMethod);

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
    CreateBitmap(frameSize, paintMethod);

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
    SizeF frameSize;
    CreateBitmap(frameSize, paintMethod);

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
    SizeF frameSize;
    CreateBitmap(frameSize, paintMethod);

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
    SizeF frameSize;
    CreateBitmap(frameSize, paintMethod);

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
    EXPECT_EQ(gradient.GetInnerRadius(), DEFAULT_DOUBLE10);
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
    PaintWrapper* paintWrapper;
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
    PaintWrapper* paintWrapper;
    Ace::ImageData imageData;
    imageData.data = {};
    paintMethod->PutImageData(paintWrapper, imageData);
    EXPECT_TRUE(imageData.data.empty());
}

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
    paint = paintMethod->GetStrokePaint();
    EXPECT_EQ(paint.getAlphaf(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Test the function GetStrokePaint with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of getFillType is not equal to DEFAULT_DOUBLE1.
     */
    paintMethod->globalState_.SetAlpha(DEFAULT_DOUBLE10);
    paint = paintMethod->GetStrokePaint();
    EXPECT_NE(paint.getAlphaf(), DEFAULT_DOUBLE1);
}

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
    CreateBitmap(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function FillRect with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of HasGlobalAlpha is true.
     */
    PaintWrapper* paintWrapper;
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
    CreateBitmap(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function StrokeRect with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    PaintWrapper* paintWrapper;
    Rect rect;
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->StrokeRect(paintWrapper, rect);
    EXPECT_TRUE(paintMethod->HasShadow());

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
    CreateBitmap(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Fill with Alpha = DEFAULT_DOUBLE10.
     * @tc.expected: The value of HasGlobalAlpha is true.
     */

    PaintWrapper* paintWrapper;
  
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
    CreateBitmap(frameSize, paintMethod);

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
    CreateBitmap(frameSize, paintMethod);

    /**
     * @tc.steps2: Test the function Stroke with shadow_.
     * @tc.expected: The value of HasShadow is true.
     */
    PaintWrapper* paintWrapper;
    paintMethod->shadow_.SetBlurRadius(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetX(DEFAULT_DOUBLE1);
    paintMethod->shadow_.SetOffsetY(DEFAULT_DOUBLE1);
    paintMethod->Stroke(paintWrapper);
    EXPECT_TRUE(paintMethod->HasShadow());

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
    CreateBitmap(frameSize, paintMethod);

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
}
} // namespace OHOS::Ace::NG
