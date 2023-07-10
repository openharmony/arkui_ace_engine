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

#include <optional>
#include <sys/types.h>

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"
#include "core/components_ng/test/pattern/custom_paint/mock/mock_paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_interface.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class CanvasPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
private:
    static RefPtr<CanvasPaintMethod> paintMethod_;
};

RefPtr<CanvasPaintMethod> CanvasPaintMethodTestNg::paintMethod_ = nullptr;

void CanvasPaintMethodTestNg::SetUpTestSuite()
{
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    RefPtr<RenderingContext2DModifier> contentModifier = AceType::MakeRefPtr<RenderingContext2DModifier>();
    paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(pipelineContext, contentModifier);
}

void CanvasPaintMethodTestNg::TearDownTestSuite()
{
    paintMethod_ =  nullptr;
}

/**
 * @tc.name: CanvasPaintMethodTestNg001
 * @tc.desc: Test all properties related to the object paintMethod_ itself.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set".
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    EXPECT_DOUBLE_EQ(paintMethod_->GetWidth(), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->GetHeight(), DEFAULT_DOUBLE0);
    paintMethod_->SetSmoothingEnabled(true);
    EXPECT_TRUE(paintMethod_->smoothingEnabled_);
    paintMethod_->SetSmoothingEnabled(false);
    EXPECT_FALSE(paintMethod_->smoothingEnabled_);
    EXPECT_FALSE(paintMethod_->HasTask());
    auto task = [](CanvasPaintMethod& paintMethod_, PaintWrapper* paintWrapper) {
        GTEST_LOG_(INFO) << "The first task to be push to tasks";
    };
    paintMethod_->PushTask(task);
    EXPECT_TRUE(paintMethod_->HasTask());

    for (uint32_t i = 0; i < CANDIDATE_CANVAS_FILL_RULES.size(); ++i) {
        paintMethod_->SetFillRuleForPath(CANDIDATE_CANVAS_FILL_RULES[i]);
        paintMethod_->SetFillRuleForPath2D(CANDIDATE_CANVAS_FILL_RULES[i]);
        EXPECT_EQ(paintMethod_->skPath_.getFillType(), CANDIDATE_SKPATH_FILL_TYPES[i]);
        EXPECT_EQ(paintMethod_->skPath2d_.getFillType(), CANDIDATE_SKPATH_FILL_TYPES[i]);
    }
}

/**
 * @tc.name: CanvasPaintMethodTestNg002
 * @tc.desc: Test all properties related to the variable fillState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable fillState_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    for (auto color : CANDIDATE_COLORS) {
        paintMethod_->SetFillColor(color);
        EXPECT_EQ(paintMethod_->fillState_.GetColor(), color);
        EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetTextColor(), color);
    }

    Ace::Pattern imagePattern;
    paintMethod_->SetFillPattern(imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod_->fillState_.GetPattern().GetImageWidth(), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->fillState_.GetPattern().GetImageHeight(), DEFAULT_DOUBLE0);
    EXPECT_EQ(paintMethod_->fillState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod_->fillState_.GetPattern().GetRepetition(), NULL_STR);
    imagePattern.SetImageWidth(IDEAL_WIDTH);
    imagePattern.SetImageHeight(IDEAL_HEIGHT);
    imagePattern.SetImgSrc(IMAGE_SRC);
    imagePattern.SetRepetition(REPETITION_STR);
    paintMethod_->SetFillPattern(imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod_->fillState_.GetPattern().GetImageWidth(), IDEAL_WIDTH);
    EXPECT_DOUBLE_EQ(paintMethod_->fillState_.GetPattern().GetImageHeight(), IDEAL_HEIGHT);
    EXPECT_EQ(paintMethod_->fillState_.GetPattern().GetImgSrc(), IMAGE_SRC);
    EXPECT_EQ(paintMethod_->fillState_.GetPattern().GetRepetition(), REPETITION_STR);

    Ace::Gradient gradient;
    paintMethod_->SetFillGradient(gradient);
    EXPECT_FALSE(paintMethod_->fillState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    paintMethod_->SetFillGradient(gradient);
    EXPECT_TRUE(paintMethod_->fillState_.GetGradient().GetRepeat());

    for (auto textAlign : CANDIDATE_TEXT_ALIGNS) {
        paintMethod_->SetTextAlign(textAlign);
        EXPECT_EQ(paintMethod_->fillState_.GetTextAlign(), textAlign);
    }
    for (auto textBaseline : CANDIDATE_TEXT_BASELINES) {
        paintMethod_->SetTextBaseline(textBaseline);
        EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetTextBaseline(), textBaseline);
    }
    for (auto fontSize : CANDIDATE_DIMENSIONS) {
        paintMethod_->SetFontSize(fontSize);
        EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetFontSize(), fontSize);
    }
    for (auto fontStyle : CANDIDATE_FONT_STYLES) {
        paintMethod_->SetFontStyle(fontStyle);
        EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetFontStyle(), fontStyle);
    }
    for (auto fontWeight : CANDIDATE_FONT_WEIGHTS) {
        paintMethod_->SetFontWeight(fontWeight);
        EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetFontWeight(), fontWeight);
    }
    paintMethod_->SetFontFamilies(FONT_FAMILY);
    EXPECT_EQ(paintMethod_->fillState_.GetTextStyle().GetFontFamilies(), FONT_FAMILY);
    EXPECT_TRUE(paintMethod_->saveStates_.empty());
    paintMethod_->SaveStates();
    EXPECT_FALSE(paintMethod_->saveStates_.empty());
    paintMethod_->RestoreStates();
    EXPECT_TRUE(paintMethod_->saveStates_.empty());
}

/**
 * @tc.name: CanvasPaintMethodTestNg003
 * @tc.desc: Test all properties related to the variable strokeState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable strokeState_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    for (auto color : CANDIDATE_COLORS) {
        paintMethod_->SetStrokeColor(color);
        EXPECT_EQ(paintMethod_->strokeState_.GetColor(), color);
    }

    Ace::Pattern imagePattern;
    paintMethod_->SetStrokePattern(imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetPattern().GetImageWidth(), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetPattern().GetImageHeight(), DEFAULT_DOUBLE0);
    EXPECT_EQ(paintMethod_->strokeState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod_->strokeState_.GetPattern().GetRepetition(), NULL_STR);
    imagePattern.SetImageWidth(IDEAL_WIDTH);
    imagePattern.SetImageHeight(IDEAL_HEIGHT);
    imagePattern.SetImgSrc(IMAGE_SRC);
    imagePattern.SetRepetition(REPETITION_STR);
    paintMethod_->SetStrokePattern(imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetPattern().GetImageWidth(), IDEAL_WIDTH);
    EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetPattern().GetImageHeight(), IDEAL_HEIGHT);
    EXPECT_EQ(paintMethod_->strokeState_.GetPattern().GetImgSrc(), IMAGE_SRC);
    EXPECT_EQ(paintMethod_->strokeState_.GetPattern().GetRepetition(), REPETITION_STR);

    Ace::Gradient gradient;
    paintMethod_->SetStrokeGradient(gradient);
    EXPECT_FALSE(paintMethod_->strokeState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    paintMethod_->SetStrokeGradient(gradient);
    EXPECT_TRUE(paintMethod_->strokeState_.GetGradient().GetRepeat());

    for (auto item : CANDIDATE_LINE_CAP_STYLES) {
        paintMethod_->SetLineCap(item);
        EXPECT_EQ(paintMethod_->strokeState_.GetLineCap(), item);
    }

    for (auto item : CANDIDATE_LINE_JOIN_STYLES) {
        paintMethod_->SetLineJoin(item);
        EXPECT_EQ(paintMethod_->strokeState_.GetLineJoin(), item);
    }

    for (double item : CANDIDATE_DOUBLES) {
        paintMethod_->SetLineWidth(item);
        EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetLineWidth(), item);
        paintMethod_->SetMiterLimit(item);
        EXPECT_DOUBLE_EQ(paintMethod_->strokeState_.GetMiterLimit(), item);
    }

    paintMethod_->SetLineDash(CANDIDATE_DOUBLES);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        auto lineDash = paintMethod_->strokeState_.GetLineDash();
        EXPECT_DOUBLE_EQ(lineDash.lineDash[i], CANDIDATE_DOUBLES[i]);
    }

    for (double item : CANDIDATE_DOUBLES) {
        paintMethod_->SetLineDashOffset(item);
        auto lineDash = paintMethod_->strokeState_.GetLineDash();
        EXPECT_DOUBLE_EQ(lineDash.dashOffset, item);
    }

    for (auto textAlign : CANDIDATE_TEXT_ALIGNS) {
        paintMethod_->SetTextAlign(textAlign);
        EXPECT_EQ(paintMethod_->strokeState_.GetTextAlign(), textAlign);
    }
    for (auto textBaseline : CANDIDATE_TEXT_BASELINES) {
        paintMethod_->SetTextBaseline(textBaseline);
        EXPECT_EQ(paintMethod_->strokeState_.GetTextStyle().GetTextBaseline(), textBaseline);
    }
    for (auto fontSize : CANDIDATE_DIMENSIONS) {
        paintMethod_->SetFontSize(fontSize);
        EXPECT_EQ(paintMethod_->strokeState_.GetTextStyle().GetFontSize(), fontSize);
    }
    for (auto fontStyle : CANDIDATE_FONT_STYLES) {
        paintMethod_->SetFontStyle(fontStyle);
        EXPECT_EQ(paintMethod_->strokeState_.GetTextStyle().GetFontStyle(), fontStyle);
    }
    for (auto fontWeight : CANDIDATE_FONT_WEIGHTS) {
        paintMethod_->SetFontWeight(fontWeight);
        EXPECT_EQ(paintMethod_->strokeState_.GetTextStyle().GetFontWeight(), fontWeight);
    }
    paintMethod_->SetFontFamilies(FONT_FAMILY);
    EXPECT_EQ(paintMethod_->strokeState_.GetTextStyle().GetFontFamilies(), FONT_FAMILY);
}

/**
 * @tc.name: CanvasPaintMethodTestNg004
 * @tc.desc: Test all properties related to the variable globalState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable globalState_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    for (double item : CANDIDATE_DOUBLES) {
        paintMethod_->SetAlpha(item);
        EXPECT_DOUBLE_EQ(paintMethod_->globalState_.GetAlpha(), item);
    }
    for (auto compositeOperation : CANDIDATE_COMPOSITE_OPERATIONS) {
        paintMethod_->SetCompositeType(compositeOperation);
        EXPECT_EQ(paintMethod_->globalState_.GetType(), compositeOperation);
    }
}

/**
 * @tc.name: CanvasPaintMethodTestNg005
 * @tc.desc: Test all properties related to the variable shadow_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable shadow_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    for (auto color : CANDIDATE_COLORS) {
        paintMethod_->SetShadowColor(color);
        EXPECT_EQ(paintMethod_->shadow_.GetColor(), color);
    }
    paintMethod_->SetShadowOffsetX(CANDIDATE_DOUBLES[0]);
    paintMethod_->SetShadowOffsetY(CANDIDATE_DOUBLES[0]);
    paintMethod_->SetShadowBlur(CANDIDATE_DOUBLES[0]);
    EXPECT_FALSE(paintMethod_->HasShadow());
    EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[0]);
    EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[0]);
    EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[0]);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        paintMethod_->SetShadowOffsetX(CANDIDATE_DOUBLES[i]);
        paintMethod_->SetShadowOffsetY(CANDIDATE_DOUBLES[i]);
        paintMethod_->SetShadowBlur(CANDIDATE_DOUBLES[i]);
        EXPECT_TRUE(paintMethod_->HasShadow());
        EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[i]);
        EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[i]);
        EXPECT_DOUBLE_EQ(paintMethod_->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[i]);
    }
}

/**
 * @tc.name: CanvasPaintMethodTestNg006
 * @tc.desc: Test the function GetAlignOffset of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);
    std::unique_ptr<MockParagraph> mockParagraph = std::make_unique<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetMaxIntrinsicWidth()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetAlphabeticBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetIdeographicBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    std::unique_ptr<Rosen::Typography> paragraph(std::move(mockParagraph));

    /**
     * @tc.steps2: Test functions GetAlignOffset.
     * @tc.expected: The return value is affected by the second parameter.
     */
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::LEFT, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::RIGHT, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::CENTER, paragraph), -DEFAULT_DOUBLE10 / 2);
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::JUSTIFY, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::START, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->GetAlignOffset(TextAlign::END, paragraph), -DEFAULT_DOUBLE10);
}

/**
 * @tc.name: CanvasPaintMethodTestNg007
 * @tc.desc: Test the function GetBaselineOffset of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);
    std::unique_ptr<MockParagraph> mockParagraph = std::make_unique<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetMaxIntrinsicWidth()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetAlphabeticBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetIdeographicBaseline()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(testing::Return(DEFAULT_DOUBLE10));
    std::unique_ptr<Rosen::Typography> paragraph(std::move(mockParagraph));

    /**
     * @tc.steps2: Test functions GetBaselineOffset.
     * @tc.expected: The return value is affected by the first parameter.
     */
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::ALPHABETIC, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::IDEOGRAPHIC, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::TOP, paragraph), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::BOTTOM, paragraph), -DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::MIDDLE, paragraph), -DEFAULT_DOUBLE10 / 2);
    EXPECT_DOUBLE_EQ(paintMethod_->GetBaselineOffset(TextBaseline::HANGING, paragraph), DEFAULT_DOUBLE0);
}

/**
 * @tc.name: CanvasPaintMethodTestNg009
 * @tc.desc: Test the function UpdateLineDash of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);
    SkPaint paint;

    /**
     * @tc.steps2: Test the function UpdateLineDash with empty lineDash.
     * @tc.expected: The pathEffect of paint is null.
     */
    EXPECT_EQ(paint.getPathEffect(), nullptr);
    const std::vector<double> lineDash1 = {};
    paintMethod_->strokeState_.SetLineDash(lineDash1);
    paintMethod_->UpdateLineDash(paint);
    EXPECT_EQ(paint.getPathEffect(), nullptr);

    /**
     * @tc.steps3: Test the function UpdateLineDash with valid lineDash.
     * @tc.expected: The pathEffect of paint is non-null.
     */
    constexpr uint32_t lineDashSize = 4;
    const std::vector<double> lineDash2(lineDashSize, DEFAULT_DOUBLE1);
    paintMethod_->strokeState_.SetLineDash(lineDash2);
    paintMethod_->strokeState_.SetLineDashOffset(DEFAULT_DOUBLE1);
    EXPECT_EQ(paint.getPathEffect(), nullptr);
    paintMethod_->UpdateLineDash(paint);
    EXPECT_NE(paint.getPathEffect(), nullptr);
}

/**
 * @tc.name: CanvasPaintMethodTestNg010
 * @tc.desc: Test functions ImageObjFailed and ImageObjReady of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);
    const std::string loadingSrc("loading");

    /**
     * @tc.steps2: Test the function ImageObjFailed.
     * @tc.expected: The imageObj_ and skiaDom_ is set to null.
     */
    paintMethod_->ImageObjFailed();
    EXPECT_EQ(paintMethod_->imageObj_, nullptr);
    EXPECT_EQ(paintMethod_->skiaDom_, nullptr);

    /**
     * @tc.steps3: Call the function ImageObjReady with imageObj->isSvg_ = false.
     * @tc.expected: The srcs of currentSource_ is not equal to loadingSrc.
     */
    ImageSourceInfo source;
    Size imageSize;
    auto imageObj = AceType::MakeRefPtr<Ace::SvgSkiaImageObject>(source, imageSize, 0, nullptr);
    imageObj->isSvg_ = false;
    paintMethod_->loadingSource_.SetSrc(loadingSrc);
    paintMethod_->ImageObjReady(imageObj);
    EXPECT_NE(paintMethod_->currentSource_.GetSrc(), loadingSrc);

    /**
     * @tc.steps4: Call the function ImageObjReady with imageObj->isSvg_ = true.
     * @tc.expected: The srcs of currentSource_ is equal to loadingSrc.
     */
    imageObj->isSvg_ = true;
    paintMethod_->loadingSource_.SetSrc(loadingSrc);
    paintMethod_->ImageObjReady(imageObj);
    EXPECT_EQ(paintMethod_->currentSource_.GetSrc(), loadingSrc);

    /**
     * @tc.steps4: Call the function GetForegroundDrawFunction.
     * @tc.expected: The return value is non-null.
     */
    EXPECT_NE(paintMethod_->GetForegroundDrawFunction(nullptr), nullptr);
}

#ifndef NEW_SKIA
/**
 * @tc.name: CanvasPaintMethodTestNg011
 * @tc.desc: Test the function GetStrokePaint of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test the function GetStrokePaint.
     * @tc.expected: The Alphaf of paint1 is set to DEFAULT_DOUBLE2.
     */
    paintMethod_->globalState_.SetAlpha(DEFAULT_DOUBLE2);
    SkPaint paint1;
    paintMethod_->GetStrokePaint(paint1);
    EXPECT_DOUBLE_EQ(paint1.getAlphaf(), DEFAULT_DOUBLE2);

    /**
     * @tc.steps3: Test the function GetStrokePaint.
     * @tc.expected: The Alphaf of paint1 is set to default value, namely, DEFAULT_DOUBLE1.
     */
    paintMethod_->globalState_.SetAlpha(DEFAULT_DOUBLE1);
    SkPaint paint2;
    paintMethod_->GetStrokePaint(paint2);
    EXPECT_DOUBLE_EQ(paint2.getAlphaf(), DEFAULT_DOUBLE1);
}

/**
 * @tc.name: CanvasPaintMethodTestNg012
 * @tc.desc: Test the function InitImagePaint of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);
    const std::string qualityUndefined("undefined");
    const std::string qualityLow("low");
    const std::string qualityMedium("medium");
    const std::string qualityHigh("high");

    /**
     * @tc.steps2: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "undefined".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod_->SetSmoothingEnabled(true);
    paintMethod_->smoothingQuality_ = qualityUndefined;
    paintMethod_->InitImagePaint(paintMethod_->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod_->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);

    /**
     * @tc.steps3: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "low".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kLow_SkFilterQuality.
     */
    paintMethod_->smoothingQuality_ = qualityLow;
    paintMethod_->InitImagePaint(paintMethod_->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod_->imagePaint_.getFilterQuality(), SkFilterQuality::kLow_SkFilterQuality);

    /**
     * @tc.steps4: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "medium".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kMedium_SkFilterQuality.
     */
    paintMethod_->smoothingQuality_ = qualityMedium;
    paintMethod_->InitImagePaint(paintMethod_->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod_->imagePaint_.getFilterQuality(), SkFilterQuality::kMedium_SkFilterQuality);

    /**
     * @tc.steps5: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "high".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kHigh_SkFilterQuality.
     */
    paintMethod_->smoothingQuality_ = qualityHigh;
    paintMethod_->InitImagePaint(paintMethod_->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod_->imagePaint_.getFilterQuality(), SkFilterQuality::kHigh_SkFilterQuality);

    /**
     * @tc.steps6: Test the function InitImagePaint with smoothingEnabled_ = false.
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod_->SetSmoothingEnabled(false);
    paintMethod_->InitImagePaint(paintMethod_->imagePaint_);
    EXPECT_DOUBLE_EQ(paintMethod_->imagePaint_.getFilterQuality(), SkFilterQuality::kNone_SkFilterQuality);
}
#endif

/**
 * @tc.name: CanvasPaintMethodTestNg014
 * @tc.desc: Test the function InitImageCallbacks of CanvasPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(paintMethod_, nullptr);

    /**
     * @tc.steps2: Test the function InitImagePaint with smoothingEnabled_ = true and smoothingQuality_ = "undefined".
     * @tc.expected: The filterQuality of imagePaint_ is equal to kNone_SkFilterQuality.
     */
    paintMethod_->InitImageCallbacks();
    EXPECT_NE(paintMethod_->imageObjSuccessCallback_, nullptr);
    EXPECT_NE(paintMethod_->failedCallback_, nullptr);
    EXPECT_NE(paintMethod_->uploadSuccessCallback_, nullptr);
    EXPECT_NE(paintMethod_->onPostBackgroundTask_, nullptr);
}
} // namespace OHOS::Ace::NG
