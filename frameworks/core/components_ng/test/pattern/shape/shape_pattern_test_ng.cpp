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

#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const float LEFT = -20.0f;
const float TOP = -30.0f;
const int32_t COLUMN = 2;
const int32_t ROW = 3;
std::vector<double> MESH = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };
} // namespace

class ShapePatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        return nullptr;
    }

    void Draw(RefPtr<FrameNode> frameNode) override {}
};

/**
 * @tc.name: LayoutAlgorithm001
 * @tc.desc: create shape with  width And height
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, LayoutAlgorithm001, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto width = Dimension(WIDTH);
    auto height = Dimension(HEIGHT);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    shapeAbstactModel.SetWidth(width);
    shapeAbstactModel.SetHeight(height);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_EQ(frameNode == nullptr, false);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    EXPECT_EQ(pattern == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    auto layoutAlgorithm = AceType::DynamicCast<BoxLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm == nullptr, false);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    auto size = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(),
                                            AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(size.has_value(), true);
    EXPECT_FLOAT_EQ(size.value().Width(), WIDTH);
    EXPECT_FLOAT_EQ(size.value().Height(), HEIGHT);
}

/**
 * @tc.name: ContainerPaintProperty001
 * @tc.desc: create shape with viewport
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetViewPort(Dimension(LEFT), Dimension(TOP), Dimension(WIDTH), Dimension(HEIGHT));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(frameNode == nullptr, false);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasShapeViewBox(), true);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Left().ConvertToPx(), LEFT);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Top().ConvertToPx(), TOP);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Width().ConvertToPx(), WIDTH);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Height().ConvertToPx(), HEIGHT);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    EXPECT_EQ(paintProperty == nullptr, false);
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    EXPECT_EQ(layoutWrapper == nullptr, false);
    frameNode->SetActive(true);
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
}

/**
 * @tc.name: ContainerPaintProperty002
 * @tc.desc: create shape with mesh
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty002, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasImageMesh(), true);
    EXPECT_EQ(paintProperty->GetImageMeshValue().GetColumn(), COLUMN);
    EXPECT_EQ(paintProperty->GetImageMeshValue().GetRow(), ROW);
    auto mesh = paintProperty->GetImageMeshValue().GetMesh();
    auto size = static_cast<int32_t>(mesh.size());
    EXPECT_EQ(size, (COLUMN + 1) * (ROW + 1) * 2);
    EXPECT_EQ(size, MESH.size());
    for (int32_t i = 0; i < size; i++) {
        EXPECT_EQ(mesh.at(i), MESH.at(i));
    }
}

/**
 * @tc.name: InheritedProperty001
 * @tc.desc: check property inherit
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, InheritedProperty001, TestSize.Level1)
{
    auto shapeModel1 = ShapeModelNG();
    shapeModel1.Create();
    shapeModel1.SetFill(Color::RED);
    shapeModel1.SetFillOpacity(OPACITY);
    auto shapeModel2 = ShapeModelNG();
    shapeModel2.Create();
    shapeModel2.SetStroke(Color::BLUE);
    shapeModel2.SetStrokeWidth(Dimension(STROKE_WIDTH));
    auto len = static_cast<int32_t>(STROKE_DASH_ARRAY.size());
    std::vector<Dimension> strokeDashArray(len);
    for (int32_t i = 0; i < len; i++) {
        strokeDashArray[i] = Dimension(STROKE_DASH_ARRAY.at(i));
    }
    shapeModel2.SetStrokeDashArray(strokeDashArray);
    shapeModel2.SetStrokeDashOffset(Dimension(DASHOFFSET));
    shapeModel2.SetStrokeLineCap(LINE_CAP);
    shapeModel2.SetStrokeLineJoin(LINE_JOIN);
    shapeModel2.SetStrokeMiterLimit(STROKE_LIMIT);
    shapeModel2.SetAntiAlias(ANTIALIAS);
    shapeModel2.SetStrokeOpacity(OPACITY);
    auto circleModel = CircleModelNG();
    circleModel.Create();
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    auto circleFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();
    auto pattern = circleFrameNode->GetPattern<CirclePattern>();
    EXPECT_EQ(pattern == nullptr, false);
    auto layoutProperty = circleFrameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm == nullptr, false);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    auto size = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(), nullptr);
    EXPECT_EQ(size.has_value(), true);
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_EQ(paintMethod == nullptr, false);
    circleFrameNode->GetGeometryNode()->SetContentSize(size.value());
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(circleFrameNode->GetRenderContext(),
        circleFrameNode->GetGeometryNode()->Clone(), circleFrameNode->GetPaintProperty<ShapePaintProperty>());
    EXPECT_EQ(paintWrapper == nullptr, false);
    auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(contentDraw == nullptr, false);
    std::shared_ptr<SkCanvas> canvas = std::make_shared<SkCanvas>();
    RSCanvas rsCavas(&canvas);
    contentDraw(rsCavas);
}

} // namespace OHOS::Ace::NG