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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/tip_layout_algorithm.h"
#include "core/components_ng/pattern/slider/tip_layout_property.h"
#include "core/components_ng/pattern/slider/tip_paint_method.h"
#include "core/components_ng/pattern/slider/tip_paint_property.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr float FRAMESIZE_WIDTH = 100.0f;
constexpr float FRAMESIZE_HEIGHT = 80.0f;
constexpr float CHILD_FRAMESIZE_WIDTH = 40.0f;
constexpr float CHILD_FRAMESIZE_HEIGHT = 30.0f;
constexpr float PADDING = 16.0f;
} // namespace
class SliderTipTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SliderTipTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SliderTipTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SliderTipTestNg001
 * @tc.desc: Test TipLayoutAlgorithm Measure Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderTipTestNg, SliderTipTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutWrapper and TipLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto tipLayoutProperty = AceType::MakeRefPtr<TipLayoutProperty>();
    EXPECT_NE(tipLayoutProperty, nullptr);
    tipLayoutProperty->UpdatePadding(Dimension(PADDING));
    LayoutWrapper tipLayoutWrapper = LayoutWrapper(nullptr, geometryNode, tipLayoutProperty);
    auto tipLayoutAlgorithm = AceType::MakeRefPtr<TipLayoutAlgorithm>();
    /**
     * @tc.cases: case1. tipLayoutWrapper has not child LayoutWrapper.
     */
    tipLayoutAlgorithm->Measure(&tipLayoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(),
        SizeF(ARROW_WIDTH.ConvertToPx() + PADDING * 2, PADDING * 2 + ARROW_HEIGHT.ConvertToPx()));
    tipLayoutProperty->UpdateDirection(Axis::VERTICAL);
    tipLayoutAlgorithm->Measure(&tipLayoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(ARROW_HEIGHT.ConvertToPx(), PADDING * 2));
    /**
     * @tc.cases: case2. tipLayoutWrapper has child LayoutWrapper and childSize is not same to { 0, 0 }.
     */
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SizeF(FRAMESIZE_WIDTH, FRAMESIZE_HEIGHT));
    RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(nullptr, childGeometryNode, nullptr);
    EXPECT_NE(childLayoutWrapper, nullptr);
    tipLayoutWrapper.AppendChild(childLayoutWrapper);
    tipLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    tipLayoutAlgorithm->Measure(&tipLayoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(FRAMESIZE_WIDTH + PADDING * 2 + FRAMESIZE_HEIGHT,
                                                FRAMESIZE_HEIGHT + PADDING * 2 + ARROW_HEIGHT.ConvertToPx()));
    tipLayoutProperty->UpdateDirection(Axis::VERTICAL);
    tipLayoutAlgorithm->Measure(&tipLayoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(),
        SizeF(FRAMESIZE_WIDTH + ARROW_HEIGHT.ConvertToPx(), FRAMESIZE_WIDTH + PADDING * 2 + FRAMESIZE_HEIGHT));
}

/**
 * @tc.name: SliderTipTestNg002
 * @tc.desc: Test TipLayoutAlgorithm Layout Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderTipTestNg, SliderTipTestNg002, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(FRAMESIZE_WIDTH, FRAMESIZE_HEIGHT));
    auto tipLayoutProperty = AceType::MakeRefPtr<TipLayoutProperty>();
    EXPECT_NE(tipLayoutProperty, nullptr);
    tipLayoutProperty->UpdatePadding(Dimension(PADDING));
    LayoutWrapper tipLayoutWrapper = LayoutWrapper(nullptr, geometryNode, tipLayoutProperty);
    // create child layoutWrapper
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SizeF(CHILD_FRAMESIZE_WIDTH, CHILD_FRAMESIZE_HEIGHT));
    RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(nullptr, childGeometryNode, nullptr);
    EXPECT_NE(childLayoutWrapper, nullptr);
    tipLayoutWrapper.AppendChild(childLayoutWrapper);
    auto tipLayoutAlgorithm = AceType::MakeRefPtr<TipLayoutAlgorithm>();
    EXPECT_NE(tipLayoutAlgorithm, nullptr);
    /**
     * @tc.cases: case1. Direction is not Axis::VERTICAL.
     */
    tipLayoutProperty->UpdateDirection(Axis::VERTICAL);
    tipLayoutAlgorithm->Layout(&tipLayoutWrapper);
    EXPECT_EQ(
        childGeometryNode->GetMarginFrameOffset(), OffsetF(.0f, (FRAMESIZE_HEIGHT - CHILD_FRAMESIZE_HEIGHT) * HALF));
    /**
     * @tc.cases: case2. Direction is Axis::HORIZONTAL.
     */
    tipLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    tipLayoutAlgorithm->Layout(&tipLayoutWrapper);
    EXPECT_EQ(
        childGeometryNode->GetMarginFrameOffset(), OffsetF((FRAMESIZE_WIDTH - CHILD_FRAMESIZE_WIDTH) * HALF, PADDING));
}

/**
 * @tc.name: SliderTipTestNg003
 * @tc.desc: Test TipPaintMethod Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderTipTestNg, SliderTipTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TipPaintMethod and PaintWrapper.
     */
    auto tipPaintProperty = AceType::MakeRefPtr<TipPaintProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, tipPaintProperty);
    /**
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL
     */
    auto paintMethod = AceType::MakeRefPtr<TipPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _)).Times(1);
    auto drawfunc1 = paintMethod->GetContentDrawFunction(&paintWrapper);
    drawfunc1(canvas);
    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is not HORIZONTAL
     */
    tipPaintProperty->UpdateDirection(Axis::VERTICAL);
    PaintWrapper paintWrapper2(nullptr, geometryNode, tipPaintProperty);
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _)).Times(1);
    auto drawfunc2 = paintMethod->GetContentDrawFunction(&paintWrapper2);
    drawfunc2(canvas);
}
} // namespace OHOS::Ace::NG
