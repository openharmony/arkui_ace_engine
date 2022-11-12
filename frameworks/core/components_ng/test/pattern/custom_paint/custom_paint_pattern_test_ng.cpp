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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_event_hub.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_layout_algorithm.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_view.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CustomPaintPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void CustomPaintPatternTestNg::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg SetUpTestCase";
}

void CustomPaintPatternTestNg::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg TearDownTestCase";
}

void CustomPaintPatternTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg SetUp";
}

void CustomPaintPatternTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg TearDown";
}

/**
 * @tc.name: CustomPaintPatternTestNg001
 * @tc.desc: Test attributes of the object customPattern.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg001, TestSize.Level1)
{
    auto customPattern = CustomPaintView::Create();
    EXPECT_FALSE(customPattern == nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::CANVAS_ETS_TAG);
    EXPECT_FALSE(customPattern->IsAtomicNode());

    customPattern->SetCanvasSize(IDEAL_SIZE);
    EXPECT_EQ(customPattern->GetWidth(), IDEAL_WIDTH);
    EXPECT_EQ(customPattern->GetHeight(), IDEAL_HEIGHT);

    customPattern->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(nullptr);
    EXPECT_FALSE(customPattern->CreateNodePaintMethod() == nullptr);
    customPattern->paintMethod_->SetLineDash(CANDIDATE_DOUBLES);
    customPattern->paintMethod_->SetLineDashOffset(DEFAULT_DOUBLE);
    EXPECT_EQ(customPattern->GetLineDash().dashOffset, DEFAULT_DOUBLE);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        EXPECT_EQ(customPattern->paintMethod_->GetLineDash().lineDash[i], CANDIDATE_DOUBLES[i]);
    }

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto layoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    config.skipMeasure = false;
    EXPECT_TRUE(customPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = true;
    EXPECT_FALSE(customPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    PaintState paintState;
    EXPECT_EQ(customPattern->MeasureText(DEFAULT_STR, paintState), 0.0);
    EXPECT_EQ(customPattern->MeasureTextHeight(DEFAULT_STR, paintState), 0.0);
    TextMetrics textMetrics = customPattern->MeasureTextMetrics(DEFAULT_STR, paintState);
    EXPECT_EQ(textMetrics.width, 0.0);
    EXPECT_EQ(textMetrics.height, 0.0);
    EXPECT_EQ(textMetrics.actualBoundingBoxLeft, 0.0);
    EXPECT_EQ(textMetrics.actualBoundingBoxRight, 0.0);
    EXPECT_EQ(textMetrics.actualBoundingBoxAscent, 0.0);
    EXPECT_EQ(textMetrics.actualBoundingBoxDescent, 0.0);
}

/**
 * @tc.name: CustomPaintPatternTestNg002
 * @tc.desc: Test onReady event.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg002, TestSize.Level1)
{
    auto customPattern = CustomPaintView::Create();
    EXPECT_FALSE(customPattern == nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<CustomPaintEventHub>();
    EXPECT_FALSE(eventHub == nullptr);

    // The flag used to determine whether the event callback function executed successfully.
    bool flagEventCbk = false;

    // Set the onReadEvent as nullptr, the value of flagEventCbk keep false always.
    CustomPaintView::SetOnReady(nullptr);
    eventHub->FireReadyEvent();
    EXPECT_FALSE(flagEventCbk);

    // Set the onReadEvent as the function which changes the value of flagEventCbk, the value will be modified when
    // the onReadyEvent is fired.
    CustomPaintView::SetOnReady([&flagEventCbk] () { flagEventCbk = true; });
    eventHub->FireReadyEvent();
    EXPECT_TRUE(flagEventCbk);
}

/**
 * @tc.name: CustomPaintPatternTestNg003
 * @tc.desc: Test the MeasureContent function with different layoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg003, TestSize.Level1)
{
    auto customPattern = CustomPaintView::Create();
    EXPECT_FALSE(customPattern == nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);

    auto layoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);

    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}

} // namespace OHOS::Ace::NG