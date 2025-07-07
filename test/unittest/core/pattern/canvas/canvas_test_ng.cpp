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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

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
 * @tc.name: MeasureContentTest001
 * @tc.desc: CanvasLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, MeasureContentTest001, TestSize.Level1)
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
 * @tc.name: MeasureContentTest002
 * @tc.desc: CanvasLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, MeasureContentTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    RefPtr<CanvasLayoutAlgorithm> canvasLayoutAlgorithm = AceType::MakeRefPtr<CanvasLayoutAlgorithm>();
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, frameNode->GetLayoutProperty());
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_TRUE(layoutProperty);

    /**
     * @tc.steps1: Width is matchParent
     * @tc.expected: the return value of MeasureContent is (300, 1000)
     */
    layoutConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutConstraint.parentIdealSize = OptionalSizeF(300.0f, 400.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 300);
    EXPECT_EQ(pattern->canvasSize_->height_, 1000);

    /**
     * @tc.steps2: Height is matchParent
     * @tc.expected: the return value of MeasureContent is (1000, 400)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 1000);
    EXPECT_EQ(pattern->canvasSize_->height_, 400);

    /**
     * @tc.steps3: Width and Height is not matchParent
     * @tc.expected: the return value of MeasureContent is (1000, 1000)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 1000);
    EXPECT_EQ(pattern->canvasSize_->height_, 1000);

    /**
     * @tc.steps4: layoutPolicy has no value
     * @tc.expected: the return value of MeasureContent is (1000, 1000)
     */
    layoutProperty->layoutPolicy_ = std::nullopt;
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 1000);
    EXPECT_EQ(pattern->canvasSize_->height_, 1000);

    /**
     * @tc.steps5: layoutProperty is nullptr
     * @tc.expected: the return value of MeasureContent is (1000, 1000)
     */
    layoutProperty.Reset();
    canvasLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(pattern->canvasSize_->width_, 1000);
    EXPECT_EQ(pattern->canvasSize_->height_, 1000);
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

/**
* @tc.name: OnAttachToMainTreeTest
* @tc.desc: CanvasPattern::OnAttachToMainTree
* @tc.type: FUNC
*/
HWTEST_F(CanvasTestNg, OnAttachToMainTreeTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: instantiation paintMethod_.
     */
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "test");
    customNode->SetJSViewName("testName");
    frameNode->SetParent(customNode);
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    pattern->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(pattern->paintMethod_);
    pattern->OnAttachToMainTree();
    EXPECT_EQ(pattern->paintMethod_->customNodeName_, "testName");
}

/**
* @tc.name: FireOnContext2DAttachTest
* @tc.desc: CanvasPattern::FireOnContext2DAttach
* @tc.type: FUNC
*/
HWTEST_F(CanvasTestNg, FireOnContext2DAttachTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: instantiation onContext2DAttach_.
     * @tc.expected: onContext2DAttach equal 1.
     */
    int32_t onContext2DAttach = 0;
    pattern->SetOnContext2DAttach([&onContext2DAttach]() {
        ++onContext2DAttach;
    });
    pattern->FireOnContext2DAttach();
    EXPECT_EQ(onContext2DAttach, 1);
}

/**
* @tc.name: FireOnContext2DDetachTest
* @tc.desc: CanvasPattern::FireOnContext2DDetach
* @tc.type: FUNC
*/
HWTEST_F(CanvasTestNg, FireOnContext2DDetachTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_TRUE(pattern);
    
    /**
     * @tc.steps2: instantiation onContext2DDetach_.
     * @tc.expected: onContext2DDetach equal 1.
     */
    int32_t onContext2DDetach = 0;
    pattern->SetOnContext2DDetach([&onContext2DDetach]() {
        ++onContext2DDetach;
    });
    pattern->FireOnContext2DDetach();
    EXPECT_EQ(onContext2DDetach, 1);
}

/**
* @tc.name: GetImageDataTest
* @tc.desc: CanvasPattern::GetImageData
* @tc.type: FUNC
*/
HWTEST_F(CanvasTestNg, GetImageDataTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: obtains input parameters.
     * @tc.expected: set dirtyWidth and dirtyHeight equal input value.
     */
    EXPECT_FALSE(pattern->paintMethod_);
    auto imageData = pattern->GetImageData(10, 20, 30, 40);
    EXPECT_EQ(imageData->dirtyWidth, 30);
    EXPECT_EQ(imageData->dirtyHeight, 40);

    /**
     * @tc.steps3: obtains default parameters.
     * @tc.expected: return nullptr.
     */
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    pattern->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(pattern->paintMethod_);
    auto imageData2 = pattern->GetImageData(10, 20, 30, 40);
    EXPECT_FALSE(imageData2);
}

/**
 * @tc.name: CanvasPaintMethodTest001
 * @tc.desc: CanvasPaintMethod::CalculatePixelMapRect
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPaintMethodTest001, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Ace::CanvasImage canvasImage;
    Testing::TestingRect srcRect(0, 0, 0, 0);
    Testing::TestingRect dstRect(0, 0, 0, 0);
    canvasImage.sx = 10.0;
    canvasImage.sy = 20.0;
    canvasImage.sWidth = 30.0;
    canvasImage.sHeight = 40.0;
    canvasImage.dx = 50.0;
    canvasImage.dy = 60.0;
    canvasImage.dWidth = 70.0;
    canvasImage.dHeight = 80.0;

    /**
     * @tc.steps: step1. Default
     * srcRect = {0, 0, 0, 0}
     * dstRect = {0, 0, 0, 0}
     */
    canvasImage.flag = static_cast<CustomPaintPaintMethod::DrawImageType>(-1);
    paintMethod->CalculatePixelMapRect(canvasImage, 100, 200, srcRect, dstRect);
    EXPECT_FLOAT_EQ(srcRect.GetLeft(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetTop(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetRight(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetBottom(), 0);
    EXPECT_FLOAT_EQ(dstRect.GetLeft(), 0);
    EXPECT_FLOAT_EQ(dstRect.GetTop(), 0);
    EXPECT_FLOAT_EQ(dstRect.GetRight(), 0);
    EXPECT_FLOAT_EQ(dstRect.GetBottom(), 0);

    /**
     * @tc.steps: step2. THREE_PARAMS
     * srcRect = {0, 0, 100, 200}
     * dstRect = {50, 60, 150, 260}
     */
    srcRect = Testing::TestingRect(0, 0, 0, 0);
    dstRect = Testing::TestingRect(0, 0, 0, 0);
    canvasImage.flag = static_cast<CustomPaintPaintMethod::DrawImageType>(0);
    paintMethod->CalculatePixelMapRect(canvasImage, 100, 200, srcRect, dstRect);
    EXPECT_FLOAT_EQ(srcRect.GetLeft(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetTop(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetRight(), 100);
    EXPECT_FLOAT_EQ(srcRect.GetBottom(), 200);
    EXPECT_FLOAT_EQ(dstRect.GetLeft(), 50);
    EXPECT_FLOAT_EQ(dstRect.GetTop(), 60);
    EXPECT_FLOAT_EQ(dstRect.GetRight(), 150);
    EXPECT_FLOAT_EQ(dstRect.GetBottom(), 260);
}

/**
 * @tc.name: CanvasPaintMethodTest002
 * @tc.desc: CanvasPaintMethod::CalculatePixelMapRect
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPaintMethodTest002, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Ace::CanvasImage canvasImage;
    Testing::TestingRect srcRect(0, 0, 0, 0);
    Testing::TestingRect dstRect(0, 0, 0, 0);
    canvasImage.sx = 10.0;
    canvasImage.sy = 20.0;
    canvasImage.sWidth = 30.0;
    canvasImage.sHeight = 40.0;
    canvasImage.dx = 50.0;
    canvasImage.dy = 60.0;
    canvasImage.dWidth = 70.0;
    canvasImage.dHeight = 80.0;

    /**
     * @tc.steps: step1. FIVE_PARAMS
     * srcRect = {0, 0, 100, 200}
     * dstRect = {50, 60, 120, 140}
     */
    canvasImage.flag = static_cast<CustomPaintPaintMethod::DrawImageType>(1);
    paintMethod->CalculatePixelMapRect(canvasImage, 100, 200, srcRect, dstRect);
    EXPECT_FLOAT_EQ(srcRect.GetLeft(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetTop(), 0);
    EXPECT_FLOAT_EQ(srcRect.GetRight(), 100);
    EXPECT_FLOAT_EQ(srcRect.GetBottom(), 200);
    EXPECT_FLOAT_EQ(dstRect.GetLeft(), 50);
    EXPECT_FLOAT_EQ(dstRect.GetTop(), 60);
    EXPECT_FLOAT_EQ(dstRect.GetRight(), 120);
    EXPECT_FLOAT_EQ(dstRect.GetBottom(), 140);

    /**
     * @tc.steps: step2. NINE_PARAMS
     * srcRect = {10, 20, 40, 60}
     * dstRect = {50, 60, 120, 140}
     */
    srcRect = Testing::TestingRect(0, 0, 0, 0);
    dstRect = Testing::TestingRect(0, 0, 0, 0);
    canvasImage.flag = static_cast<CustomPaintPaintMethod::DrawImageType>(2);
    paintMethod->CalculatePixelMapRect(canvasImage, 100, 200, srcRect, dstRect);
    EXPECT_FLOAT_EQ(srcRect.GetLeft(), 10);
    EXPECT_FLOAT_EQ(srcRect.GetTop(), 20);
    EXPECT_FLOAT_EQ(srcRect.GetRight(), 40);
    EXPECT_FLOAT_EQ(srcRect.GetBottom(), 60);
    EXPECT_FLOAT_EQ(dstRect.GetLeft(), 50);
    EXPECT_FLOAT_EQ(dstRect.GetTop(), 60);
    EXPECT_FLOAT_EQ(dstRect.GetRight(), 120);
    EXPECT_FLOAT_EQ(dstRect.GetBottom(), 140);
}

/**
 * @tc.name: CanvasPaintMethodTest003
 * @tc.desc: CanvasPaintMethod::SetCustomTextType
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, CanvasPaintMethodTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_TRUE(frameNode);
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(paintMethod);
    paintMethod->rsCanvas_ = std::make_shared<Testing::TestingRecordingCanvas>(100, 100);
    auto recordingCanvas = std::static_pointer_cast<Testing::TestingRecordingCanvas>(paintMethod->rsCanvas_);
    ASSERT_TRUE(recordingCanvas);
    MockPipelineContext::SetUp();
    auto pipeContext = MockPipelineContext::GetCurrent();
    ASSERT_TRUE(pipeContext);
    paintMethod->context_ = AceType::WeakClaim(AceType::RawPtr(pipeContext));
    pipeContext->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    /**
     * @tc.steps: step1. FontManager isDefaultFontChanged_ is false
     * @tc.expected: RSRecordingCanvas isCustomTextType_ is false
     */
    pipeContext->fontManager_->isDefaultFontChanged_ = false;
    paintMethod->SetCustomTextType();
    EXPECT_FALSE(recordingCanvas->isCustomTextType_);

    /**
     * @tc.steps: step2. FontManager isDefaultFontChanged_ is true
     * @tc.expected: RSRecordingCanvas isCustomTextType_ is true
     */
    pipeContext->fontManager_->isDefaultFontChanged_ = true;
    paintMethod->SetCustomTextType();
    EXPECT_TRUE(recordingCanvas->isCustomTextType_);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: IsEnableMatchParentTest
 * @tc.desc: CanvasPattern::IsEnableMatchParent
 * @tc.type: FUNC
 */
HWTEST_F(CanvasTestNg, IsEnableMatchParentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: Check Function IsEnableMatchParent's return value.
     * @tc.expected: Function IsEnableMatchParent returns true.
     */
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}
} // namespace OHOS::Ace::NG
