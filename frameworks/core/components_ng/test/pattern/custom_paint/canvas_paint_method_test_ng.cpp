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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void CanvasPaintMethodTestNg::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "CanvasPaintMethodTestNg SetUpTestCase";
}

void CanvasPaintMethodTestNg::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "CanvasPaintMethodTestNg TearDownTestCase";
}

void CanvasPaintMethodTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "CanvasPaintMethodTestNg SetUp";
}

void CanvasPaintMethodTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "CanvasPaintMethodTestNg TearDown";
}

/**
 * Test common attributes that belong to both the class OffscreenCanvasPaintMethod and OffscreenCanvasPaintMethod, 
 * that is, the properties that belong to the class CustomPaintPaintMethod.
 */

/**
 * @tc.name: CanvasPaintMethodTestNg001
 * @tc.desc: Test all properties related to the object paintMethod itself.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg001, TestSize.Level1)
{
    // Access to private properties and methods is implemented using macro definitions during testing.
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(paintMethod == nullptr);
    EXPECT_EQ(paintMethod->GetWidth(), 0);
    EXPECT_EQ(paintMethod->GetHeight(), 0);
    paintMethod->SetSmoothingEnabled(true);
    EXPECT_TRUE(paintMethod->smoothingEnabled_);
    paintMethod->SetSmoothingEnabled(false);
    EXPECT_FALSE(paintMethod->smoothingEnabled_);
    EXPECT_FALSE(paintMethod->HasTask());
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        GTEST_LOG_(INFO) << "The first task to be push to tasks";
    };
    paintMethod->PushTask(task);
    EXPECT_TRUE(paintMethod->HasTask());

    for (uint32_t i = 0; i < CANDIDATE_CANVAS_FILL_RULES.size(); ++i) {
        paintMethod->SetFillRuleForPath(CANDIDATE_CANVAS_FILL_RULES[i]);
        paintMethod->SetFillRuleForPath2D(CANDIDATE_CANVAS_FILL_RULES[i]);
        EXPECT_EQ(paintMethod->skPath_.getFillType(), CANDIDATE_SKPATH_FILL_TYPES[i]);
        EXPECT_EQ(paintMethod->skPath2d_.getFillType(), CANDIDATE_SKPATH_FILL_TYPES[i]);
    }

    float viewScale = 1.0f;

    auto imageInfo = SkImageInfo::Make(IDEAL_SIZE.Width() * viewScale, IDEAL_SIZE.Height() * viewScale,
        SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    paintMethod->canvasCache_.reset();
    paintMethod->cacheBitmap_.reset();
    paintMethod->canvasCache_.allocPixels(imageInfo);
    paintMethod->cacheBitmap_.allocPixels(imageInfo);
    paintMethod->canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    paintMethod->cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    paintMethod->skCanvas_ = std::make_unique<SkCanvas>(paintMethod->canvasCache_);
    paintMethod->cacheCanvas_ = std::make_unique<SkCanvas>(paintMethod->cacheBitmap_);
    EXPECT_FALSE(paintMethod->skCanvas_ == nullptr);
    EXPECT_EQ(viewScale, 1.0f);
}

/**
 * @tc.name: CanvasPaintMethodTestNg002
 * @tc.desc: Test all properties related to the variable fillState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg002, TestSize.Level1)
{
    // Access to private properties and methods is implemented using macro definitions during testing.
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(paintMethod == nullptr);
    for (auto color : CANDIDATE_COLORS) {
        paintMethod->SetFillColor(color);
        EXPECT_EQ(paintMethod->fillState_.GetColor(), color);
        EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetTextColor(), color);
    }

    Ace::Pattern imagePattern;
    paintMethod->SetFillPattern(imagePattern);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImageWidth(), 0);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImageHeight(), 0);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetRepetition(), NULL_STR);
    imagePattern.SetImageWidth(IDEAL_WIDTH);
    imagePattern.SetImageHeight(IDEAL_HEIGHT);
    imagePattern.SetImgSrc(IMAGE_SRC);
    imagePattern.SetRepetition(REPETITION_STR);
    paintMethod->SetFillPattern(imagePattern);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImageWidth(), IDEAL_WIDTH);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImageHeight(), IDEAL_HEIGHT);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImgSrc(), IMAGE_SRC);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetRepetition(), REPETITION_STR);
    
    Ace::Gradient gradient;
    paintMethod->SetFillGradient(gradient);
    EXPECT_FALSE(paintMethod->fillState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    paintMethod->SetFillGradient(gradient);
    EXPECT_TRUE(paintMethod->fillState_.GetGradient().GetRepeat());

    for (auto textAlign : CANDIDATE_TEXT_ALIGNS) {
        paintMethod->SetTextAlign(textAlign);
        EXPECT_EQ(paintMethod->fillState_.GetTextAlign(), textAlign);
    }
    for (auto textBaseline : CANDIDATE_TEXT_BASELINES) {
        paintMethod->SetTextBaseline(textBaseline);
        EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetTextBaseline(), textBaseline);
    }
    for (auto fontSize : CANDIDATE_DIMENSIONS) {
        paintMethod->SetFontSize(fontSize);
        EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontSize(), fontSize);
    }
    for (auto fontStyle : CANDIDATE_FONT_STYLES) {
        paintMethod->SetFontStyle(fontStyle);
        EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontStyle(), fontStyle);
    }
    for (auto fontWeight : CANDIDATE_FONT_WEIGHTS) {
        paintMethod->SetFontWeight(fontWeight);
        EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontWeight(), fontWeight);
    }
    paintMethod->SetFontFamilies(FONT_FAMILY);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontFamilies(), FONT_FAMILY);
    EXPECT_TRUE(paintMethod->saveStates_.empty());
    paintMethod->SaveStates();
    EXPECT_FALSE(paintMethod->saveStates_.empty());
    paintMethod->RestoreStates();
    EXPECT_TRUE(paintMethod->saveStates_.empty());
}

/**
 * @tc.name: CanvasPaintMethodTestNg003
 * @tc.desc: Test all properties related to the variable strokeState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg003, TestSize.Level1)
{
    // Access to private properties and methods is implemented using macro definitions during testing.
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(paintMethod == nullptr);
    for (auto color : CANDIDATE_COLORS) {
        paintMethod->SetStrokeColor(color);
        EXPECT_EQ(paintMethod->strokeState_.GetColor(), color);
    }

    Ace::Pattern imagePattern;
    paintMethod->SetStrokePattern(imagePattern);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImageWidth(), 0);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImageHeight(), 0);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetRepetition(), NULL_STR);
    imagePattern.SetImageWidth(IDEAL_WIDTH);
    imagePattern.SetImageHeight(IDEAL_HEIGHT);
    imagePattern.SetImgSrc(IMAGE_SRC);
    imagePattern.SetRepetition(REPETITION_STR);
    paintMethod->SetStrokePattern(imagePattern);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImageWidth(), IDEAL_WIDTH);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImageHeight(), IDEAL_HEIGHT);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImgSrc(), IMAGE_SRC);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetRepetition(), REPETITION_STR);

    Ace::Gradient gradient;
    paintMethod->SetStrokeGradient(gradient);
    EXPECT_FALSE(paintMethod->strokeState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    paintMethod->SetStrokeGradient(gradient);
    EXPECT_TRUE(paintMethod->strokeState_.GetGradient().GetRepeat());

    for (auto item : CANDIDATE_LINE_CAP_STYLES) {
        paintMethod->SetLineCap(item);
        EXPECT_EQ(paintMethod->strokeState_.GetLineCap(), item);
    }

    for (auto item : CANDIDATE_LINE_JOIN_STYLES) {
        paintMethod->SetLineJoin(item);
        EXPECT_EQ(paintMethod->strokeState_.GetLineJoin(), item);
    }

    for (double item : CANDIDATE_DOUBLES) {
        paintMethod->SetLineWidth(item);
        EXPECT_EQ(paintMethod->strokeState_.GetLineWidth(), item);
        paintMethod->SetMiterLimit(item);
        EXPECT_EQ(paintMethod->strokeState_.GetMiterLimit(), item);
    }

    paintMethod->SetLineDash(CANDIDATE_DOUBLES);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        EXPECT_EQ(paintMethod->GetLineDash().lineDash[i], CANDIDATE_DOUBLES[i]);
    }
    for (double item : CANDIDATE_DOUBLES) {
        paintMethod->SetLineDashOffset(item);
        EXPECT_EQ(paintMethod->GetLineDash().dashOffset, item);
    }

    for (auto textAlign : CANDIDATE_TEXT_ALIGNS) {
        paintMethod->SetTextAlign(textAlign);
        EXPECT_EQ(paintMethod->strokeState_.GetTextAlign(), textAlign);
    }
    for (auto textBaseline : CANDIDATE_TEXT_BASELINES) {
        paintMethod->SetTextBaseline(textBaseline);
        EXPECT_EQ(paintMethod->strokeState_.GetTextStyle().GetTextBaseline(), textBaseline);
    }
    for (auto fontSize : CANDIDATE_DIMENSIONS) {
        paintMethod->SetFontSize(fontSize);
        EXPECT_EQ(paintMethod->strokeState_.GetTextStyle().GetFontSize(), fontSize);
    }
    for (auto fontStyle : CANDIDATE_FONT_STYLES) {
        paintMethod->SetFontStyle(fontStyle);
        EXPECT_EQ(paintMethod->strokeState_.GetTextStyle().GetFontStyle(), fontStyle);
    }
    for (auto fontWeight : CANDIDATE_FONT_WEIGHTS) {
        paintMethod->SetFontWeight(fontWeight);
        EXPECT_EQ(paintMethod->strokeState_.GetTextStyle().GetFontWeight(), fontWeight);
    }
    paintMethod->SetFontFamilies(FONT_FAMILY);
    EXPECT_EQ(paintMethod->strokeState_.GetTextStyle().GetFontFamilies(), FONT_FAMILY);
}

/**
 * @tc.name: CanvasPaintMethodTestNg004
 * @tc.desc: Test all properties related to the variable globalState_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg004, TestSize.Level1)
{
    // Access to private properties and methods is implemented using macro definitions during testing.
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(paintMethod == nullptr);
    for (double item : CANDIDATE_DOUBLES) {
        paintMethod->SetAlpha(item);
        EXPECT_EQ(paintMethod->globalState_.GetAlpha(), item);
    }
    for (auto compositeOperation : CANDIDATE_COMPOSITE_OPERATIONS) {
        paintMethod->SetCompositeType(compositeOperation);
        EXPECT_EQ(paintMethod->globalState_.GetType(), compositeOperation);
    }
}

/**
 * @tc.name: CanvasPaintMethodTestNg005
 * @tc.desc: Test all properties related to the variable shadow_.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPaintMethodTestNg, CanvasPaintMethodTestNg005, TestSize.Level1)
{
    // Access to private properties and methods is implemented using macro definitions during testing.
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(paintMethod == nullptr);
    for (auto color : CANDIDATE_COLORS) {
        paintMethod->SetShadowColor(color);
        EXPECT_EQ(paintMethod->shadow_.GetColor(), color);
    }
    paintMethod->SetShadowOffsetX(CANDIDATE_DOUBLES[0]);
    paintMethod->SetShadowOffsetY(CANDIDATE_DOUBLES[0]);
    paintMethod->SetShadowBlur(CANDIDATE_DOUBLES[0]);
    EXPECT_FALSE(paintMethod->HasShadow());
    EXPECT_EQ(paintMethod->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[0]);
    EXPECT_EQ(paintMethod->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[0]);
    EXPECT_EQ(paintMethod->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[0]);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        paintMethod->SetShadowOffsetX(CANDIDATE_DOUBLES[i]);
        paintMethod->SetShadowOffsetY(CANDIDATE_DOUBLES[i]);
        paintMethod->SetShadowBlur(CANDIDATE_DOUBLES[i]);
        EXPECT_TRUE(paintMethod->HasShadow());
        EXPECT_EQ(paintMethod->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[i]);
        EXPECT_EQ(paintMethod->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[i]);
        EXPECT_EQ(paintMethod->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[i]);
    }
}

} // namespace OHOS::Ace::NG