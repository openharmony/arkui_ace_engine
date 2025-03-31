/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components_ng/pattern/canvas/canvas_event_hub.h"
#include "core/components_ng/pattern/canvas/canvas_layout_algorithm.h"
#include "core/components_ng/pattern/canvas/canvas_model.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/custom_paint_paint_method.h"
#include "core/components_ng/pattern/canvas/custom_paint_util.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#undef private
#undef protected

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasTestNg::SetUpTestCase() {}

void CanvasTestNg::TearDownTestCase() {}

/**
 * @tc.name: CanvasPatternTest001
 * @tc.desc: Test the function 'IsPercentStr' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function IsPercentStr with percent string.
     * @tc.expected: The return value is true and the '%' of percent string is droped.
     */
    const std::string exceptedresult("50");

    std::string percentStr("50%");
    EXPECT_TRUE(paintMethod->IsPercentStr(percentStr));
    EXPECT_STREQ(percentStr.c_str(), exceptedresult.c_str());

    /**
     * @tc.steps3: Call the function IsPercentStr with non-percent string.
     * @tc.expected: The return value is false and the non-percent string is not changed.
     */
    std::string nonPercentStr("50");
    EXPECT_FALSE(paintMethod->IsPercentStr(nonPercentStr));
    EXPECT_STREQ(nonPercentStr.c_str(), exceptedresult.c_str());
}

/**
 * @tc.name: CanvasPatternTest002
 * @tc.desc: CanvasPattern::OnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig config;
    bool needReset;

    /**
     * @tc.steps: step1. needReset = false; dirtyPixelGridRoundSize_ = { 0, 0 }
     */
    needReset = false;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { -1, -1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier1 = pattern->contentModifier_;
    EXPECT_FALSE(contentModifier1->needResetSurface_);

    /**
     * @tc.steps: step2. needReset = false; dirtyPixelGridRoundSize_ = { 1, 1 };
     */
    needReset = false;
    config.frameSizeChange = false;
    config.contentSizeChange = false;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { 1, 1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier2 = pattern->contentModifier_;
    EXPECT_FALSE(contentModifier2->needResetSurface_);

    /**
     * @tc.steps: step3. needReset = true; dirtyPixelGridRoundSize_ = { 1, 1 };
     */
    needReset = false;
    config.frameSizeChange = true;
    config.contentSizeChange = true;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { 1, 1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier3 = pattern->contentModifier_;
    EXPECT_FALSE(contentModifier3->needResetSurface_);

    /**
     * @tc.steps: step4. needReset = true; config.frameSizeChange = false; config.contentSizeChange = false;
     */
    needReset = true;
    config.frameSizeChange = false;
    config.contentSizeChange = false;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { -1, -1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier4 = pattern->contentModifier_;
    EXPECT_FALSE(contentModifier4->needResetSurface_);

    /**
     * @tc.steps: step5. needReset = true; config.frameSizeChange = true; config.contentSizeChange = false;
     */
    needReset = true;
    config.frameSizeChange = true;
    config.contentSizeChange = false;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { -1, -1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier5 = pattern->contentModifier_;
    EXPECT_TRUE(contentModifier5->needResetSurface_);

    /**
     * @tc.steps: step6. needReset = true; config.frameSizeChange = false; config.contentSizeChange = true;
     */
    needReset = true;
    config.frameSizeChange = false;
    config.contentSizeChange = true;
    pattern->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern->dirtyPixelGridRoundSize_ = { -1, -1 };
    pattern->OnSizeChanged(config, needReset);
    ASSERT_NE(pattern->contentModifier_, nullptr);
    auto contentModifier6 = pattern->contentModifier_;
    EXPECT_TRUE(contentModifier6->needResetSurface_);
}

/**
 * @tc.name: CanvasPatternTest003
 * @tc.desc: CanvasPattern::EnableAnalyzer
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();

    /**
     * @tc.steps: step1. enable = false;
     */
    pattern->EnableAnalyzer(false);
    EXPECT_FALSE(pattern->imageAnalyzerManager_);

    /**
     * @tc.steps: step1. enable = true;
     */
    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->imageAnalyzerManager_);
}

/**
 * @tc.name: CanvasPatternTest004
 * @tc.desc: CanvasPattern::UpdateTextDefaultDirection
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();

    /**
     * @tc.steps: step1. TextDirection::AUTO;
     */
    pattern->currentSetTextDirection_ = TextDirection::AUTO;
    pattern->UpdateTextDefaultDirection();
    EXPECT_EQ(pattern->currentSetTextDirection_, TextDirection::AUTO);
}

/**
 * @tc.name: CanvasPatternTest005
 * @tc.desc: CanvasLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();

    RefPtr<CanvasLayoutAlgorithm> canvasLayoutAlgorithm = AceType::MakeRefPtr<CanvasLayoutAlgorithm>();
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step1. IsValid() == false;
     */
    layoutConstraint.maxSize.SetWidth(1000.0f);
    layoutConstraint.maxSize.SetHeight(1000.0f);
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 1000.0f);
    EXPECT_EQ(pattern->canvasSize_->height_, 1000.0f);

    /**
     * @tc.steps: step1. IsValid() == true;
     */
    layoutConstraint.selfIdealSize.SetWidth(960.0f);
    layoutConstraint.selfIdealSize.SetHeight(960.0f);
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 960.0f);
    EXPECT_EQ(pattern->canvasSize_->height_, 960.0f);
}

/**
 * @tc.name: CanvasPatternTest006
 * @tc.desc: GetQuality
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest006, TestSize.Level1)
{
    double dRet = 0.0;
    std::string strRet = "";

    /**
     * @tc.steps: step1. GetQuality：type != IMAGE_JPEG && type != IMAGE_WEBP, quality > 0.0 || quality < 1.0
     */
    dRet = GetQuality("", 0.8);
    EXPECT_EQ(dRet, DEFAULT_QUALITY * QUALITY_COEFFICIENT);

    /**
     * @tc.steps: step2. GetQuality：type != IMAGE_JPEG && type != IMAGE_WEBP, quality > 0.0 || quality < 1.0
     */
    dRet = GetQuality(IMAGE_PNG, 0.8);
    EXPECT_EQ(dRet, DEFAULT_QUALITY * QUALITY_COEFFICIENT);

    /**
     * @tc.steps: step4. GetQuality：mimeType == IMAGE_JPEG, quality > 0.0 || quality < 1.0
     */
    dRet = GetQuality(IMAGE_JPEG, 0.8);
    EXPECT_EQ(dRet, 0.8 * QUALITY_COEFFICIENT);

    /**
     * @tc.steps: step5. GetQuality：mimeType == IMAGE_WEBP, quality > 0.0 || quality < 1.0
     */
    dRet = GetQuality(IMAGE_WEBP, 0.8);
    EXPECT_EQ(dRet, 0.8 * QUALITY_COEFFICIENT);

    /**
     * @tc.steps: step6. mimeType == IMAGE_WEBP, GetQuality：quality > 1.0
     */
    dRet = GetQuality(IMAGE_WEBP, 1.1);
    EXPECT_EQ(dRet, DEFAULT_QUALITY * QUALITY_COEFFICIENT);

    /**
     * @tc.steps: step7. mimeType == IMAGE_WEBP, GetQuality：quality < 0.0
     */
    dRet = GetQuality(IMAGE_WEBP, -1.1);
    EXPECT_EQ(dRet, DEFAULT_QUALITY * QUALITY_COEFFICIENT);
}

/**
 * @tc.name: CanvasPatternTest007
 * @tc.desc: OffscreenCanvasPattern::SetTextDirection && UpdateTextDefaultDirection
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest007, TestSize.Level1)
{
    auto offPattern = AceType::MakeRefPtr<OffscreenCanvasPattern>(100, 100);
    ASSERT_NE(offPattern, nullptr);

    /**
     * @tc.steps: step1. SetTextDirection : TextDirection::AUTO;
     */
    offPattern->SetTextDirection(TextDirection::AUTO);
    EXPECT_EQ(offPattern->offscreenPaintMethod_->state_.fillState.textDirection_, TextDirection::AUTO);
    /**
     * @tc.steps: step2. SetTextDirection : TextDirection::INHERIT;
     */
    offPattern->SetTextDirection(TextDirection::INHERIT);
    EXPECT_EQ(offPattern->offscreenPaintMethod_->state_.fillState.textDirection_, TextDirection::LTR);
    /**
     * @tc.steps: step3. UpdateTextDefaultDirection : TextDirection::INHERIT;
     */
    offPattern->currentSetTextDirection_ = TextDirection::AUTO;
    offPattern->UpdateTextDefaultDirection();
    EXPECT_EQ(offPattern->offscreenPaintMethod_->state_.fillState.textDirection_, TextDirection::LTR);
    /**
     * @tc.steps: step4. UpdateTextDefaultDirection : TextDirection::INHERIT;
     */
    offPattern->currentSetTextDirection_ = TextDirection::INHERIT;
    offPattern->UpdateTextDefaultDirection();
    EXPECT_EQ(offPattern->offscreenPaintMethod_->state_.fillState.textDirection_, TextDirection::LTR);
}

/**
 * @tc.name: CanvasPatternTest008
 * @tc.desc: CustomPaintPaintMethod::HasShadow
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPatternTest008, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps: step1. HasShadow() == false
     */
    Shadow shadow1 = Shadow(5.0f, Offset(0.0, 0.0), Color(0x32000000), ShadowStyle::OuterDefaultXS);
    Shadow shadow2 = Shadow(5.0f, Offset(10.0, 10.0), Color(0x32000000), ShadowStyle::OuterDefaultXS);
    paintMethod->state_.shadow = shadow1;
    EXPECT_FALSE(paintMethod->HasShadow());
    /**
     * @tc.steps: step2. HasShadow() == true
     */
    paintMethod->state_.shadow = shadow2;
    EXPECT_TRUE(paintMethod->HasShadow());
}
} // namespace OHOS::Ace::NG
