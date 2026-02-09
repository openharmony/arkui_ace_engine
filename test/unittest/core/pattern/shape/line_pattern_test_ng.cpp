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

#include "gtest/gtest.h"
#include "include/core/SkCanvas.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/pattern/shape/line_paint_property.h"
#include "core/components_ng/pattern/shape/line_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/render/paint_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float WIDTH = 200.0f;
constexpr float HEIGHT = 300.0f;
constexpr float OPACITY = 0.5f;
constexpr float STROKE_WIDTH = 3.0f;
constexpr bool ANTIALIAS = false;
constexpr float STROKE_LIMIT = 5.0f;
constexpr float DASHOFFSET = 3.0f;
constexpr int32_t LINE_JOIN = 1;
constexpr int32_t LINE_CAP = 1;
constexpr std::array<float, 2> STROKE_DASH_ARRAY = { 3, 5 };
constexpr float START_ZERO = 0.0f;
constexpr float END_ZERO = 0.0f;
constexpr float START_X = 2.0f;
constexpr float START_Y = 1.0f;
constexpr float END_X = 15.0f;
constexpr float END_Y = 30.0f;
} // namespace

class LinePatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        frameNode_ = CreateFrameNode();
    }

    RefPtr<FrameNode> CreateFrameNode()
    {
        LineModelNG().Create();
        auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        EXPECT_NE(frameNode, nullptr);
        return frameNode;
    }

    void SetSize(RefPtr<FrameNode> frameNode)
    {
        auto width = Dimension(WIDTH);
        auto height = Dimension(HEIGHT);
        ShapeAbstractModelNG::SetWidth(AceType::RawPtr(frameNode), width);
        ShapeAbstractModelNG::SetHeight(AceType::RawPtr(frameNode), height);
    }

    void Draw(RefPtr<FrameNode> frameNode)
    {
        EXPECT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<LinePattern>();
        EXPECT_NE(pattern, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty();
        EXPECT_NE(layoutProperty, nullptr);
        auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
        EXPECT_NE(layoutAlgorithm, nullptr);
        LayoutConstraintF layoutConstraint;
        layoutConstraint.percentReference.SetWidth(WIDTH);
        layoutConstraint.percentReference.SetHeight(HEIGHT);
        layoutConstraint.selfIdealSize.SetWidth(WIDTH);
        layoutConstraint.selfIdealSize.SetHeight(HEIGHT);
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);
        layoutProperty->UpdateContentConstraint();
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
        LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
        auto size = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(), &layoutWrapper);
        EXPECT_TRUE(size.has_value());
        auto paintMethod = pattern->CreateNodePaintMethod();
        EXPECT_NE(paintMethod, nullptr);
        frameNode->GetGeometryNode()->SetContentSize(size.value());
        auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(),
            frameNode->GetGeometryNode()->Clone(), frameNode->GetPaintProperty<ShapePaintProperty>());
        EXPECT_NE(paintWrapper, nullptr);
        auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(contentDraw, nullptr);
        std::shared_ptr<SkCanvas> canvas = std::make_shared<SkCanvas>();
        Testing::MockCanvas rsCavas(&canvas);
        auto shapePaintProperty = AceType::DynamicCast<ShapePaintProperty>(paintWrapper->GetPaintProperty()->Clone());
        if (!shapePaintProperty->HasStrokeWidth() || !NearZero(shapePaintProperty->GetStrokeWidth()->Value())) {
            EXPECT_CALL(rsCavas, AttachPen(_)).WillOnce(ReturnRef(rsCavas));
        }
        EXPECT_CALL(rsCavas, DrawLine(_, _)).WillOnce(Return());
        EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
        contentDraw(rsCavas);
    }

    void SetPoints(LineModelNG& lineModelNg, ShapePoint* startPoint, ShapePoint* endPoint)
    {
        auto hasStart = (startPoint != nullptr);
        auto hasEnd = (endPoint != nullptr);
        if (hasStart) {
            lineModelNg.StartPoint(*startPoint);
        }
        if (hasEnd) {
            lineModelNg.EndPoint(*endPoint);
        }
    }

    void SetStrokeWidth(LineModelNG& lineModelNg, bool bSetValue)
    {
        auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        EXPECT_NE(frameNode, nullptr);
        auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
        EXPECT_NE(lineProperty, nullptr);
        if (bSetValue) {
            lineProperty->UpdateStrokeWidth(Dimension(STROKE_WIDTH));
        }
        if (bSetValue) {
            EXPECT_TRUE(lineProperty->HasStrokeWidth());
            EXPECT_FLOAT_EQ(lineProperty->GetStrokeWidthValue().ConvertToPx(), STROKE_WIDTH);
        } else {
            EXPECT_FALSE(lineProperty->HasStrokeWidth());
        }
    }

    void MeasureContentTest(
        ShapePoint* startPoint, ShapePoint* endPoint, bool bVaild = true, bool bSetStrokeWidth = true)
    {
        auto lineModelNg = LineModelNG();
        lineModelNg.Create();
        auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        EXPECT_NE(frameNode, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(geometryNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty();
        EXPECT_NE(layoutProperty, nullptr);
        RefPtr<LayoutWrapperNode> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
        auto pattern = frameNode->GetPattern<LinePattern>();
        EXPECT_NE(pattern, nullptr);
        auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
        EXPECT_NE(layoutAlgorithm, nullptr);
        LayoutConstraintF layoutConstraint;
        if (bVaild) {
            layoutConstraint.percentReference.SetWidth(WIDTH);
            layoutConstraint.percentReference.SetHeight(HEIGHT);
            layoutConstraint.selfIdealSize.SetWidth(WIDTH);
            layoutConstraint.selfIdealSize.SetHeight(HEIGHT);
        } else {
            layoutConstraint.selfIdealSize = OptionalSize<float>(std::nullopt, std::nullopt);
        }
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);
        layoutProperty->UpdateContentConstraint();

        SetStrokeWidth(lineModelNg, bSetStrokeWidth);
        SetPoints(lineModelNg, startPoint, endPoint);

        auto size = layoutAlgorithm->MeasureContent(
            layoutProperty->CreateContentConstraint(), AccessibilityManager::RawPtr(layoutWrapper));
        EXPECT_TRUE(size.has_value());
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: PointTest001
 * @tc.desc: set startPoint and endPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest001, TestSize.Level1)
{
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_Y));
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_Y));
    auto lineModelNg = LineModelNG();
    lineModelNg.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    bool hasStart = true;
    bool hasEnd = true;
    if (hasStart) {
        lineModelNg.StartPoint(startPoint);
    }
    if (hasEnd) {
        lineModelNg.EndPoint(endPoint);
    }
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_NE(lineProperty, nullptr);
    if (hasStart) {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), START_X);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), START_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasEnd) {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), END_X);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), END_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasStart && hasEnd) {
        Draw(frameNode);
    }
}

/**
 * @tc.name: PointTest002
 * @tc.desc: set startPoint but no endPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest002, TestSize.Level1)
{
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_Y));
    ShapePoint* endPoint = nullptr;
    auto lineModelNg = LineModelNG();
    lineModelNg.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    bool hasStart = true;
    bool hasEnd = false;
    if (hasStart) {
        lineModelNg.StartPoint(startPoint);
    }
    if (hasEnd) {
        lineModelNg.EndPoint(*endPoint);
    }
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_NE(lineProperty, nullptr);
    if (hasStart) {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), START_X);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), START_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasEnd) {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), END_X);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), END_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasStart && hasEnd) {
        Draw(frameNode);
    }
}

/**
 * @tc.name: PointTest003
 * @tc.desc: set endPoint but no startPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest003, TestSize.Level1)
{
    ShapePoint* startPoint = nullptr;
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_Y));
    auto lineModelNg = LineModelNG();
    lineModelNg.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    bool hasStart = false;
    bool hasEnd = true;
    if (hasStart) {
        lineModelNg.StartPoint(*startPoint);
    }
    if (hasEnd) {
        lineModelNg.EndPoint(endPoint);
    }
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_NE(lineProperty, nullptr);
    if (hasStart) {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), START_X);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), START_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasEnd) {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), END_X);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), END_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasStart && hasEnd) {
        Draw(frameNode);
    }
}

/**
 * @tc.name: PointTest004
 * @tc.desc: set no startPoint or endPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest004, TestSize.Level1)
{
    ShapePoint* startPoint = nullptr;
    ShapePoint* endPoint = nullptr;
    auto lineModelNg = LineModelNG();
    lineModelNg.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto hasStart = (startPoint != nullptr);
    auto hasEnd = (endPoint != nullptr);
    if (hasStart) {
        lineModelNg.StartPoint(*startPoint);
    }
    if (hasEnd) {
        lineModelNg.EndPoint(*endPoint);
    }
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_NE(lineProperty, nullptr);
    if (hasStart) {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), START_X);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), START_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasStartPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasEnd) {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), END_X);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), END_Y);
    } else {
        EXPECT_TRUE(lineProperty->HasEndPoint());
        constexpr float DEFAULT_POINT_VALUE = 0.0f;
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), DEFAULT_POINT_VALUE);
        EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), DEFAULT_POINT_VALUE);
    }
    if (hasStart && hasEnd) {
        Draw(frameNode);
    }
}

/**
 * @tc.name: MeasureContent001
 * @tc.desc: set no selfIdealSize and has StrokeWidth
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent001, TestSize.Level1)
{
    /**
     * @tc.desc: Call MeasureContent(IsValid == FALSE; HasStrokeWidth() == TRUE)
     */
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_Y));
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_Y));
    MeasureContentTest(&startPoint, &endPoint, false, true);
}

/**
 * @tc.name: MeasureContent002
 * @tc.desc: set no selfIdealSize and no StrokeWidth
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent002, TestSize.Level1)
{
    /**
     * @tc.desc: Call MeasureContent(IsValid == FALSE; HasStrokeWidth() == FALSE)
     */
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_Y));
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_Y));
    MeasureContentTest(&startPoint, &endPoint, false, false);
}

/**
 * @tc.name: MeasureContent003
 * @tc.desc: set no width but has height
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent003, TestSize.Level1)
{
    /**
     * @tc.desc: Call MeasureContent(IsValid == FALSE; HasStrokeWidth() == TRUE; width == 0 && height != 0)
     */
    auto startPoint = ShapePoint(Dimension(START_ZERO), Dimension(START_Y));
    auto endPoint = ShapePoint(Dimension(START_ZERO), Dimension(END_Y));
    MeasureContentTest(&startPoint, &endPoint, false, true);
}

/**
 * @tc.name: MeasureContent004
 * @tc.desc: set no height but has width
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent004, TestSize.Level1)
{
    /**
     * @tc.desc: Call MeasureContent(IsValid == FALSE; HasStrokeWidth() == TRUE; width != 0 && height == 0)
     */
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_ZERO));
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_ZERO));
    MeasureContentTest(&startPoint, &endPoint, false, true);
}

/**
 * @tc.name: MeasureContent005
 * @tc.desc: set no width and no height
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent005, TestSize.Level1)
{
    /**
     * @tc.desc: Call MeasureContent(IsValid == FALSE; HasStrokeWidth() == TRUE; width == 0 && height == 0)
     */
    auto startPoint = ShapePoint(Dimension(START_ZERO), Dimension(START_ZERO));
    auto endPoint = ShapePoint(Dimension(END_ZERO), Dimension(END_ZERO));
    MeasureContentTest(&startPoint, &endPoint, false, true);
}

/**
 * @tc.name: MeasureContent006
 * @tc.desc: LineLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<LineLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps2: contentConstraint.selfIdealSize is (100, 200)
     * @tc.expected: the return value of MeasureContent is (100, 200)
     */
    contentConstraint.selfIdealSize = OptionalSizeF(100, 200);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 200));

    /**
     * @tc.steps3: Width is Zero and StrokeWidth is 5
     * @tc.expected: the return value of MeasureContent is (5, 100)
     */
    contentConstraint.selfIdealSize.Reset();
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateStrokeWidth(Dimension(5));
    paintProperty->UpdateStartPoint(ShapePoint(0, 0));
    paintProperty->UpdateEndPoint(ShapePoint(0, 100));
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(5, 100));

    /**
     * @tc.steps4: Height is Zero and StrokeWidth is 5
     * @tc.expected: the return value of MeasureContent is (100, 5)
     */
    contentConstraint.selfIdealSize.Reset();
    paintProperty->UpdateStrokeWidth(Dimension(5));
    paintProperty->UpdateStartPoint(ShapePoint(0, 0));
    paintProperty->UpdateEndPoint(ShapePoint(100, 0));
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 5));
}

/**
 * @tc.name: MeasureContent007
 * @tc.desc: LineLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, MeasureContent007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<LineLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_TRUE(paintProperty);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps2: Width is matchParent
     * @tc.expected: the return value of MeasureContent is (300, 100)
     */
    contentConstraint.selfIdealSize.Reset();
    paintProperty->UpdateStartPoint(ShapePoint(0, 0));
    paintProperty->UpdateEndPoint(ShapePoint(100, 100));
    contentConstraint.parentIdealSize = OptionalSizeF(300, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(300, 100));

    /**
     * @tc.steps3: Height is matchParent
     * @tc.expected: the return value of MeasureContent is (100, 400)
     */
    contentConstraint.selfIdealSize.Reset();
    paintProperty->UpdateStartPoint(ShapePoint(0, 0));
    paintProperty->UpdateEndPoint(ShapePoint(100, 100));
    contentConstraint.parentIdealSize = OptionalSizeF(300, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 400));

    /**
     * @tc.steps4: Width and Height is not matchParent
     * @tc.expected: the return value of MeasureContent is (100, 100)
     */
    contentConstraint.selfIdealSize.Reset();
    paintProperty->UpdateStartPoint(ShapePoint(0, 0));
    paintProperty->UpdateEndPoint(ShapePoint(100, 100));
    contentConstraint.parentIdealSize = OptionalSizeF(300, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 100));
}

/**
 * @tc.name: PaintFill001
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintFill001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetFill(AceType::RawPtr(frameNode_), Color::RED);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasFill());
    EXPECT_EQ(shapeProperty->GetFillValue(), Color::RED);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFill002
 * @tc.desc: set no fill and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintFill002, TestSize.Level1)
{
    SetSize(frameNode_);
    // Default behavior - no explicit fill set
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasFill());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFillOpacity001
 * @tc.desc: set fill opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintFillOpacity001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode_), OPACITY);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasFillOpacity());
    EXPECT_FLOAT_EQ(shapeProperty->GetFillOpacityValue(), OPACITY);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFillOpacity002
 * @tc.desc: set no fill opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintFillOpacity002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasFillOpacity());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStroke001
 * @tc.desc: set stroke and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStroke001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStroke(AceType::RawPtr(frameNode_), Color::RED);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStroke());
    EXPECT_EQ(shapeProperty->GetStrokeValue(), Color::RED);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStroke002
 * @tc.desc: set no stroke and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStroke002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStroke());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintAntiAlias001
 * @tc.desc: set antialias and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintAntiAlias001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetAntiAlias(AceType::RawPtr(frameNode_), ANTIALIAS);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasAntiAlias());
    EXPECT_EQ(shapeProperty->GetAntiAliasValue(), ANTIALIAS);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintAntiAlias002
 * @tc.desc: set no antialias and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintAntiAlias002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasAntiAlias());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeWidth001
 * @tc.desc: set stroke width and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeWidth001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeWidth(AceType::RawPtr(frameNode_), Dimension(STROKE_WIDTH));
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeWidth());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeWidthValue().ConvertToPx(), STROKE_WIDTH);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeWidth002
 * @tc.desc: set no stroke width and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeWidth002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeWidth());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeOpacity001
 * @tc.desc: set stroke opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeOpacity001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode_), OPACITY);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeOpacity());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeOpacityValue(), OPACITY);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeOpacity002
 * @tc.desc: set no stroke opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeOpacity002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeOpacity());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashArray001
 * @tc.desc: set dash Array and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeDashArray001, TestSize.Level1)
{
    SetSize(frameNode_);
    auto len = static_cast<int32_t>(STROKE_DASH_ARRAY.size());
    std::vector<Dimension> strokeDashArray(len);
    for (int32_t i = 0; i < len; i++) {
        strokeDashArray[i] = Dimension(STROKE_DASH_ARRAY.at(i));
    }
    ShapeModelNG::SetStrokeDashArray(AceType::RawPtr(frameNode_), strokeDashArray);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeDashArray());
    EXPECT_EQ(shapeProperty->GetStrokeDashArrayValue().size(), STROKE_DASH_ARRAY.size());
    const std::vector<Dimension> propStrokeDashArray = shapeProperty->GetStrokeDashArrayValue();
    auto propLen = static_cast<int32_t>(propStrokeDashArray.size());
    for (int32_t i = 0; i < propLen; i++) {
        EXPECT_FLOAT_EQ(propStrokeDashArray[i].ConvertToPx(), STROKE_DASH_ARRAY.at(i));
    }
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashArray002
 * @tc.desc: set no dash Array and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeDashArray002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeDashArray());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashOffset001
 * @tc.desc: set stroke dash offset and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeDashOffset001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeDashOffset(AceType::RawPtr(frameNode_), Dimension(DASHOFFSET));
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeDashOffset());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeDashOffset()->ConvertToPx(), DASHOFFSET);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashOffset002
 * @tc.desc: set no stroke dash offset and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeDashOffset002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeDashOffset());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeLineCap001
 * @tc.desc: set stroke line cap and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeLineCap001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeLineCap(AceType::RawPtr(frameNode_), LINE_CAP);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeLineCap());
    EXPECT_EQ(shapeProperty->GetStrokeLineCap(), LINE_CAP);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeLineCap002
 * @tc.desc: set no stroke line cap and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeLineCap002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeLineCap());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeLineJoin001
 * @tc.desc: set stroke line join and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeLineJoin001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeLineJoin(AceType::RawPtr(frameNode_), LINE_JOIN);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeLineJoin());
    EXPECT_EQ(shapeProperty->GetStrokeLineJoinValue(), LINE_JOIN);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeLineJoin002
 * @tc.desc: set no stroke line join and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeLineJoin002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeLineJoin());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeMiterLimit001
 * @tc.desc: set stroke miter limit and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeMiterLimit001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode_), STROKE_LIMIT);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()), STROKE_LIMIT);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeMiterLimit002
 * @tc.desc: set no stroke miter limit and check
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTestNg, PaintStrokeMiterLimit002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeMiterLimit());
    Draw(frameNode_);
}

} // namespace OHOS::Ace::NG
