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
#include "include/core/SkCanvas.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/shape/shape_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/paint_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

const std::array<std::array<float, 2>, 5> POINTS = { { { 50, 0 }, { 0, 50 }, { 20, 100 }, { 80, 100 }, { 100, 50 } } };

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

} // namespace

class PolylinePatternTestNg : public testing::Test {
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
        PolygonModelNG().Create(false);
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
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<PolygonPattern>();
        EXPECT_EQ(pattern == nullptr, false);
        auto layoutProperty = frameNode->GetLayoutProperty();
        EXPECT_EQ(layoutProperty == nullptr, false);
        auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
        EXPECT_EQ(layoutAlgorithm == nullptr, false);
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
        EXPECT_EQ(size.has_value(), true);
        auto paintMethod = pattern->CreateNodePaintMethod();
        EXPECT_EQ(paintMethod == nullptr, false);
        frameNode->GetGeometryNode()->SetContentSize(size.value());
        auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(),
            frameNode->GetGeometryNode()->Clone(), frameNode->GetPaintProperty<ShapePaintProperty>());
        EXPECT_EQ(paintWrapper == nullptr, false);
        auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_EQ(contentDraw == nullptr, false);
        std::shared_ptr<SkCanvas> canvas = std::make_shared<SkCanvas>();
        Testing::MockCanvas rsCavas(&canvas);
        auto shapePaintProperty = AceType::DynamicCast<PolygonPaintProperty>(paintWrapper->GetPaintProperty()->Clone());
        if (shapePaintProperty->HasPoints() && !shapePaintProperty->GetPoints()->empty()) {
            if (!shapePaintProperty->HasStrokeWidth() || !NearZero(shapePaintProperty->GetStrokeWidth()->Value())) {
                EXPECT_CALL(rsCavas, AttachPen(_)).WillOnce(ReturnRef(rsCavas));
            }
            EXPECT_CALL(rsCavas, AttachBrush(_)).WillOnce(ReturnRef(rsCavas));
            EXPECT_CALL(rsCavas, DrawPath(_)).WillOnce(Return());
            EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
            EXPECT_CALL(rsCavas, DetachBrush()).WillOnce(ReturnRef(rsCavas));
        }
        contentDraw(rsCavas);
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: PolylinePaintProperty001
 * @tc.desc: create polyline with points
 * @tc.type: FUNC
 */

HWTEST_F(PolylinePatternTestNg, PolylinePaintProperty001, TestSize.Level1)
{
    PolygonModelNG().Create(false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SetSize(frameNode);

    EXPECT_EQ(frameNode == nullptr, false);
    ShapePoints shapePoints;
    auto size = static_cast<int32_t>(POINTS.size());
    for (int32_t i = 0; i < size; i++) {
        shapePoints.emplace_back(ShapePoint(Dimension(POINTS.at(i).at(0)), Dimension(POINTS.at(i).at(1))));
    }
    PolygonModelNG().SetPoints(shapePoints);
    ViewStackProcessor::GetInstance()->Pop();
    auto polygonPaintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_EQ(polygonPaintProperty->HasPoints(), true);
    auto propLen = static_cast<int32_t>(polygonPaintProperty->GetPointsValue().size());
    EXPECT_EQ(propLen, static_cast<int32_t>(POINTS.size()));
    auto propPoints = polygonPaintProperty->GetPointsValue();
    for (int32_t i = 0; i < propLen; i++) {
        EXPECT_FLOAT_EQ(propPoints[i].first.ConvertToPx(), POINTS[i][0]);
        EXPECT_FLOAT_EQ(propPoints[i].second.ConvertToPx(), POINTS[i][1]);
    }

    Draw(frameNode);
}

/**
 * @tc.name: PolylinePaintProperty002
 * @tc.desc: create polyline with no points
 * @tc.type: FUNC
 */

HWTEST_F(PolylinePatternTestNg, PolylinePaintProperty002, TestSize.Level1)
{
    PolygonModelNG().Create(false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SetSize(frameNode);

    EXPECT_EQ(frameNode == nullptr, false);
    ViewStackProcessor::GetInstance()->Pop();
    auto polygonPaintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_EQ(polygonPaintProperty->HasPoints(), false);

    Draw(frameNode);
}

/**
 * @tc.name: PaintFill001
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */
HWTEST_F(PolylinePatternTestNg, PaintFill001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintFill002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintFillOpacity001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintFillOpacity002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStroke001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStroke002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintAntiAlias001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintAntiAlias002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeWidth001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeWidth002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeOpacity001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeOpacity002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeDashArray001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeDashArray002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeDashOffset001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeDashOffset002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeLineCap001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeLineCap002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeLineJoin001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeLineJoin002, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeMiterLimit001, TestSize.Level1)
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
HWTEST_F(PolylinePatternTestNg, PaintStrokeMiterLimit002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeMiterLimit());
    Draw(frameNode_);
}

} // namespace OHOS::Ace::NG