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
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/ellipse_pattern.h"
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
constexpr float DASHOFFSET = 3;
constexpr int32_t LINE_JOIN = 1;
constexpr int32_t LINE_CAP = 1;
constexpr std::array<float, 2> STROKE_DASH_ARRAY = { 3, 5 };
} // namespace

class EllipsePatternTestNg : public testing::Test {
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
        EllipseModelNG().Create();
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
        auto pattern = frameNode->GetPattern<EllipsePattern>();
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
        EXPECT_CALL(rsCavas, AttachBrush(_)).WillOnce(ReturnRef(rsCavas));
        EXPECT_CALL(rsCavas, DrawOval(_)).WillOnce(Return());
        EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
        EXPECT_CALL(rsCavas, DetachBrush()).WillOnce(ReturnRef(rsCavas));
        contentDraw(rsCavas);
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: Creator001
 * @tc.desc: create ellipse with width and height
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, Creator001, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto layoutProperty = frameNode_->GetLayoutProperty();
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto mesureLayout = calcLayoutConstraint->selfIdealSize;
    EXPECT_TRUE(mesureLayout.has_value());
    EXPECT_TRUE(mesureLayout->Width().has_value());
    EXPECT_TRUE(mesureLayout->Height().has_value());
}

/**
 * @tc.name: PaintFill001
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, PaintFill001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintFill002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintFillOpacity001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintFillOpacity002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStroke001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStroke002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintAntiAlias001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintAntiAlias002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeWidth001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeWidth002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeOpacity001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeOpacity002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeDashArray001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeDashArray002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeDashOffset001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeDashOffset002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeLineCap001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeLineCap002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeLineJoin001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeLineJoin002, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeMiterLimit001, TestSize.Level1)
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
HWTEST_F(EllipsePatternTestNg, PaintStrokeMiterLimit002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeMiterLimit());
    Draw(frameNode_);
}

/**
 * @tc.name: EllipsePatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod creates shapeOverlayModifier_ on first call
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePatternCreateNodePaintMethod001, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    // First call should create paintMethod successfully
    auto paintMethod1 = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod1, nullptr);
}

/**
 * @tc.name: EllipsePatternCreateNodePaintMethod002
 * @tc.desc: test CreateNodePaintMethod reuses existing shapeOverlayModifier_
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePatternCreateNodePaintMethod002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    // First call
    auto paintMethod1 = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod1, nullptr);

    // Second call should reuse shapeOverlayModifier_
    auto paintMethod2 = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod2, nullptr);
}

/**
 * @tc.name: EllipsePaintMethodDefaultConstructor001
 * @tc.desc: test EllipsePaintMethod default constructor
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePaintMethodDefaultConstructor001, TestSize.Level1)
{
    EllipsePaintMethod paintMethod;
    EXPECT_NE(&paintMethod, nullptr);
}

/**
 * @tc.name: EllipsePaintMethodGetContentDrawFunction001
 * @tc.desc: test GetContentDrawFunction with null paintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePaintMethodGetContentDrawFunction001, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    // Test with null paintWrapper
    auto contentDraw = paintMethod->GetContentDrawFunction(nullptr);
    EXPECT_EQ(contentDraw, nullptr);
}

/**
 * @tc.name: EllipsePaintMethodGetContentDrawFunction002
 * @tc.desc: test GetContentDrawFunction returns null when GetPaintProperty returns null
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePaintMethodGetContentDrawFunction002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    // Create a PaintWrapper with null paint property
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        frameNode_->GetRenderContext(), geometryNode, nullptr);
    ASSERT_NE(paintWrapper, nullptr);

    auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(contentDraw, nullptr);
}

/**
 * @tc.name: EllipsePaintMethodParameterizedConstructor001
 * @tc.desc: test EllipsePaintMethod parameterized constructor
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePaintMethodParameterizedConstructor001, TestSize.Level1)
{
    auto shapePaintProperty = AceType::MakeRefPtr<ShapePaintProperty>();
    auto shapeOverlayModifier = AceType::MakeRefPtr<ShapeOverlayModifier>();

    EllipsePaintMethod paintMethod(shapePaintProperty, shapeOverlayModifier);
    EXPECT_NE(&paintMethod, nullptr);
}

/**
 * @tc.name: EllipsePatternOnModifyDone001
 * @tc.desc: test OnModifyDone with negative miter limit (should reset to DEFAULT)
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePatternOnModifyDone001, TestSize.Level1)
{
    SetSize(frameNode_);
    // Set negative miter limit
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode_), -5.0);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    // Call OnModifyDone which should reset negative miter limit to DEFAULT
    pattern->OnModifyDone();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()),
        ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
}

/**
 * @tc.name: EllipsePatternOnModifyDone002
 * @tc.desc: test OnModifyDone with miter limit less than MIN (should reset to MIN)
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePatternOnModifyDone002, TestSize.Level1)
{
    SetSize(frameNode_);
    // Set miter limit less than MIN (1.0)
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode_), 0.5);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    // Call OnModifyDone which should reset miter limit to MIN
    pattern->OnModifyDone();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()),
        ShapePaintProperty::STROKE_MITERLIMIT_MIN);
}

/**
 * @tc.name: EllipsePatternOnModifyDone003
 * @tc.desc: test OnModifyDone with valid miter limit (should not change)
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePatternTestNg, EllipsePatternOnModifyDone003, TestSize.Level1)
{
    SetSize(frameNode_);
    // Set valid miter limit
    double validMiterLimit = 3.0;
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode_), validMiterLimit);
    ViewStackProcessor::GetInstance()->Pop();

    auto pattern = frameNode_->GetPattern<EllipsePattern>();
    ASSERT_NE(pattern, nullptr);

    // Call OnModifyDone which should not change valid miter limit
    pattern->OnModifyDone();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()), validMiterLimit);
}

} // namespace OHOS::Ace::NG
