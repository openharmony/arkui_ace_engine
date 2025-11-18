/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "mock_canvas_paint.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/canvas/canvas_layout_algorithm.h"
#include "core/components_ng/pattern/canvas/canvas_model.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/custom_paint_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "core/pipeline/base/constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasCustomPaintMethodTestNg2 : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasCustomPaintMethodTestNg2::SetUpTestCase()
{
    MockContainer::SetUp();
}

void CanvasCustomPaintMethodTestNg2::TearDownTestCase()
{
    MockContainer::TearDown();
}

/**
 * @tc.name: CanvasCustomPaintMethodTest037
 * @tc.desc: Test the function 'SetHueRotateFilter' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, CanvasCustomPaintMethodTest037, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    RSColor color;
    RSBrush brush(RSColor(0xffffffff));
    RSPen pen;
    paintMethod->state_.strokeState.SetLineDash({ { 1.0, 0.0 }, 1.0 });
    paintMethod->state_.strokeState.SetLineDashOffset(1.0);
    paintMethod->UpdateLineDash(pen);

    paintMethod->SetFilterParam("none");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetFilterParam("hue-rotate(90deg)");
    paintMethod->SetHueRotateFilter("hue-rotate(90deg)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetFilterParam("hue-rotate(90turn)");
    paintMethod->SetHueRotateFilter("hue-rotate(90turn)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);
    paintMethod->SetFilterParam("hue-rotate(90rad)");
    paintMethod->SetHueRotateFilter("hue-rotate(90rad)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);
}

/**
 * @tc.name: CanvasCustomPaintMethodTest038
 * @tc.desc: Test the function 'SetPaintImage' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, CanvasCustomPaintMethodTest038, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    RSColor color;
    RSBrush brush(RSColor(0xffffffff));
    RSPen pen;
    paintMethod->state_.strokeState.SetLineDash({ { 1.0, 0.0 }, 1.0 });
    paintMethod->state_.strokeState.SetLineDashOffset(1.0);
    paintMethod->UpdateLineDash(pen);
    FilterProperty filter;
    filter.filterParam_ = "test";
    filter.filterType_ = FilterType::NONE;
    paintMethod->SetPaintImage(&pen, &brush);
    filter.filterType_ = FilterType::GRAYSCALE;
    paintMethod->SetPaintImage(&pen, &brush);
    float percentNum = 1.0f;
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
    filter.filterType_ = FilterType::SEPIA;
    paintMethod->SetPaintImage(&pen, &brush);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
    filter.filterType_ = FilterType::SATURATE;
    paintMethod->SetPaintImage(&pen, &brush);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
    filter.filterType_ = FilterType::HUE_ROTATE;
    paintMethod->SetPaintImage(&pen, &brush);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
}

/**
 * @tc.name: CanvasCustomPaintMethodTest040
 * @tc.desc: Test the function 'InitImagePaint' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, CanvasCustomPaintMethodTest040, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    RSPen pen;
    paintMethod->state_.strokeState.SetLineDash({ { 1.0, 0.0 }, 1.0 });
    paintMethod->state_.strokeState.SetLineDashOffset(1.0);
    paintMethod->UpdateLineDash(pen);
    RSBrush brush(RSColor(0xffffffff));
    paintMethod->smoothingQuality_ = SmoothingQuality::MEDIUM;
    float percentNum = 1.0f;
    FilterProperty filter;
    RSSamplingOptions options;
    paintMethod->InitImagePaint(&pen, &brush, options);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
    paintMethod->smoothingQuality_ = SmoothingQuality::HIGH;
    paintMethod->InitImagePaint(&pen, &brush, options);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
    paintMethod->smoothingEnabled_ = false;
    paintMethod->smoothingQuality_ = SmoothingQuality::HIGH;
    paintMethod->InitImagePaint(&pen, &brush, options);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(filter.filterParam_, true, percentNum));
}

/**
 * @tc.name: CanvasCustomPaintMethodTest041
 * @tc.desc: Test the function 'UpdatePaintShader' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, CanvasCustomPaintMethodTest041, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    RSPen pen;
    paintMethod->state_.strokeState.SetLineDash({ { 1.0, 0.0 }, 1.0 });
    paintMethod->state_.strokeState.SetLineDashOffset(1.0);
    paintMethod->UpdateLineDash(pen);
    RSBrush brush(RSColor(0xffffffff));
    Ace::Gradient gradient;
    paintMethod->UpdatePaintShader(&pen, &brush, gradient);
    EXPECT_EQ(gradient.GetType(), Ace::GradientType::LINEAR);
    gradient.type_ = Ace::GradientType::CONIC;
    paintMethod->UpdatePaintShader(&pen, &brush, gradient);
    EXPECT_EQ(gradient.GetType(), Ace::GradientType::CONIC);
    gradient.type_ = Ace::GradientType::SWEEP;
    paintMethod->UpdatePaintShader(&pen, &brush, gradient);
    RSPoint beginPoint = RSPoint(static_cast<RSScalar>(gradient.GetBeginOffset().GetX()),
        static_cast<RSScalar>(gradient.GetBeginOffset().GetY()));
    RSPoint endPoint = RSPoint(
        static_cast<RSScalar>(gradient.GetEndOffset().GetX()), static_cast<RSScalar>(gradient.GetEndOffset().GetY()));
    EXPECT_FALSE(gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint);
}

/**
 * @tc.name: GetSystemDirectionTest
 * @tc.desc: Test the function 'GetSystemDirection' of the class 'CanvasPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, GetSystemDirectionTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_TRUE(frameNode);
    frameNode->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(paintMethod);
    paintMethod->frameNode_ = std::move(frameNode);

    /**
     * @tc.steps2: layoutDirection_ default is TextDirection::AUTO.
     * @tc.expected: return TextDirection::LTR.
     */
    TextDirection ret = paintMethod->GetSystemDirection();
    EXPECT_EQ(ret, TextDirection::LTR);

    /**
     * @tc.steps3: layoutDirection_ is not TextDirection::AUTO.
     * @tc.expected: return TextDirection::INHERIT.
     */
    frameNode->layoutProperty_->layoutDirection_ = TextDirection::INHERIT;
    ret = paintMethod->GetSystemDirection();
    EXPECT_EQ(ret, TextDirection::INHERIT);
}

/**
 * @tc.name: GetImageDataTest
 * @tc.desc: Test the function 'GetImageData' of the class 'CanvasPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestNg2, GetImageDataTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_TRUE(frameNode);
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(paintMethod);
    /**
     * @tc.steps2: invoked by default.
     * @tc.expected: DrawBitmap(renderContext, currentBitmap) return false.
     */
    auto imageData = paintMethod->GetImageData(10, 10, 10, 10);
    EXPECT_FALSE(imageData);
}

/**
* @tc.name: UpdateRecordingCanvasTest
* @tc.desc: Test the function 'UpdateRecordingCanvas' of the class 'CanvasPaintMethod'.
* @tc.type: FUNC
*/
HWTEST_F(CanvasCustomPaintMethodTestNg2, UpdateRecordingCanvasTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_TRUE(contentModifier);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_TRUE(frameNode);
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode);
    ASSERT_TRUE(paintMethod);

    /**
     * @tc.steps2: invoked by default.
     * @tc.expected: set paintMethod->needMarkDirty_ is true.
     */
    paintMethod->UpdateRecordingCanvas(10, 10);
    EXPECT_TRUE(paintMethod->needMarkDirty_);

    /**
     * @tc.steps3: set apiTargetVersion is VERSION_THIRTEEN.
     * @tc.expected: set paintMethod->needMarkDirty_ is true.
     */
    auto container = Container::Current();
    ASSERT_TRUE(container);
    auto apiVersion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    paintMethod->UpdateRecordingCanvas(10, 10);
    EXPECT_TRUE(paintMethod->needMarkDirty_);
    container->SetApiTargetVersion(apiVersion);
}

}