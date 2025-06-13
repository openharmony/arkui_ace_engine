/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#define private public
#define protected public

#include "base_shape_pattern_test_ng.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const float ZERO = 0.0;
const float LEFT = -20.0f;
const float TOP = -30.0f;
const int32_t COLUMN = 2;
const int32_t ROW = 3;
std::vector<float> MESH = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const float MAIN_SIZE = 600.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    layoutConstraint.selfIdealSize.SetWidth(WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    auto size = layoutAlgorithm->MeasureContent(
        layoutProperty->CreateContentConstraint(), AccessibilityManager::RawPtr(layoutWrapper));
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
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
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
    layoutConstraint.selfIdealSize.SetWidth(WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(circleFrameNode, geometryNode, circleFrameNode->GetLayoutProperty());
    auto size = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(), &layoutWrapper);
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
    Testing::MockCanvas rsCavas(&canvas);
    auto shapePaintProperty = AceType::DynamicCast<ShapePaintProperty>(paintWrapper->GetPaintProperty()->Clone());
    if (!shapePaintProperty->HasStrokeWidth() || !NearZero(shapePaintProperty->GetStrokeWidth()->Value())) {
        EXPECT_CALL(rsCavas, AttachPen(_)).WillOnce(ReturnRef(rsCavas));
    }
    EXPECT_CALL(rsCavas, AttachBrush(_)).WillOnce(ReturnRef(rsCavas));
    EXPECT_CALL(rsCavas, DrawCircle(_, _)).WillOnce(Return());
    EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
    EXPECT_CALL(rsCavas, DetachBrush()).WillOnce(ReturnRef(rsCavas));
    contentDraw(rsCavas);
}

/**
 * @tc.name: MeasureContent001
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureContent when ShapeViewBox is invaild
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, MeasureContent001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_TRUE(paintProperty);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    /**
     * @tc.desc: HasShapeViewBox() == FALSE && selfIdealSize.IsNull() == TRUE;
     */
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    LayoutConstraintF constrain;
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto newSize = layoutAlgorithm->MeasureContent(constrain, AccessibilityManager::RawPtr(layoutWrapper));
    LayoutConstraintF constrain2;
    constrain2.selfIdealSize = OptionalSize<float>(std::nullopt, std::nullopt);
    newSize = layoutAlgorithm->MeasureContent(constrain2, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(newSize);
}

/**
 * @tc.name: MeasureContent002
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureContent when ShapeViewBox is vaild
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, MeasureContent002, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    /**
     * @tc.desc: set HasShapeViewBox() == TRUE && GetShapeViewBoxValue().IsValid() == FALSE;
     */
    shapeModel.SetViewPort(Dimension(ZERO), Dimension(ZERO), Dimension(ZERO), Dimension(ZERO));
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_TRUE(paintProperty);
    EXPECT_TRUE(paintProperty->HasShapeViewBox());
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().IsValid(), false);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    LayoutConstraintF constrain;
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    /**
     * @tc.desc: Call MeasureContent(selfIdealSize != Null && selfIdealSize.IsValid == TRUE)
     */
    auto newSize = layoutAlgorithm->MeasureContent(constrain, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(newSize);
}

/**
 * @tc.name: MeasureContent003
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureContent when selfIdealSize is vaild/invaild
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, MeasureContent003, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    /**
     * @tc.desc: set HasShapeViewBox() == TRUE && GetShapeViewBoxValue().IsValid() == TRUE;
     */
    shapeModel.SetViewPort(Dimension(LEFT), Dimension(TOP), Dimension(WIDTH), Dimension(HEIGHT));
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_TRUE(paintProperty);
    EXPECT_TRUE(paintProperty->HasShapeViewBox());
    EXPECT_TRUE(paintProperty->GetShapeViewBoxValue().IsValid());
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.desc: Call MeasureContent(selfIdealSize == Null && GreatNotEqual == TRUE)
     */
    LayoutConstraintF constrain;
    constrain.selfIdealSize = OptionalSize<float>(std::nullopt, std::nullopt);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto newSize = layoutAlgorithm->MeasureContent(constrain, AccessibilityManager::RawPtr(layoutWrapper));
    /**
     * @tc.desc: Call MeasureContent(selfIdealSize != Null && selfIdealSize.IsValid != TRUE)
     */
    LayoutConstraintF constrain2;
    constrain2.selfIdealSize = OptionalSize<float>(0, 0);
    newSize = layoutAlgorithm->MeasureContent(constrain2, AccessibilityManager::RawPtr(layoutWrapper));
    /**
     * @tc.desc: Call MeasureContent(selfIdealSize != Null && selfIdealSize.IsValid == TRUE &&
     * (hasDefineWidth && !hasDefineHeight && GreatNotEqual(portWidth, 0.0)))
     */
    LayoutConstraintF constrain3;
    constrain3.selfIdealSize = OptionalSize<float>(-1, std::nullopt);
    newSize = layoutAlgorithm->MeasureContent(constrain3, AccessibilityManager::RawPtr(layoutWrapper));
    /**
     * @tc.desc: Call MeasureContent(selfIdealSize != Null && selfIdealSize.IsValid != TRUE &&
     * (!hasDefineWidth && hasDefineHeight && GreatNotEqual(portHeight, 0.0)))
     */
    LayoutConstraintF constrain4;
    constrain4.selfIdealSize = OptionalSize<float>(std::nullopt, -1);
    newSize = layoutAlgorithm->MeasureContent(constrain4, AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: MeasureContent005
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureContent when layoutPolicy is vaild/invaild
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTestNg, MeasureContent005, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    ASSERT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_TRUE(paintProperty);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_TRUE(layoutAlgorithm);
    /**
     * @tc.steps1: Width is matchParent
     * @tc.expected: the return value of MeasureContent is (300, 0)
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutConstraint.parentIdealSize = OptionalSizeF(300.0f, 400.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    auto contentSize = layoutAlgorithm->MeasureContent(layoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_TRUE(contentSize.has_value());
    EXPECT_EQ(contentSize.value(), SizeF(300, 0));

    /**
     * @tc.steps2: Height is matchParent
     * @tc.expected: the return value of MeasureContent is (0, 400)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    contentSize = layoutAlgorithm->MeasureContent(layoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_TRUE(contentSize.has_value());
    EXPECT_EQ(contentSize.value(), SizeF(0, 400));

    /**
     * @tc.steps3: Width and Height is not matchParent
     * @tc.expected: the return value of MeasureContent is (0, 0)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    contentSize = layoutAlgorithm->MeasureContent(layoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_TRUE(contentSize.has_value());
    EXPECT_EQ(contentSize.value(), SizeF(0, 0));

    /**
     * @tc.steps4: layoutPolicy has no value
     * @tc.expected: the return value of MeasureContent is (0, 0)
     */
    layoutProperty->layoutPolicy_ = std::nullopt;
    contentSize = layoutAlgorithm->MeasureContent(layoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_TRUE(contentSize.has_value());
    EXPECT_EQ(contentSize.value(), SizeF(0, 0));
}

/**
 * @tc.name: GetChildrenSize
 * @tc.desc: check ShapeContainerLayoutAlgorithm GetChildrenSize
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTestNg, GetChildrenSize002, TestSize.Level1)
{
    ShapeModelNG().Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_FALSE(frameNode == nullptr);
    CircleModelNG().Create();
    auto firstItem = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_FALSE(firstItem == nullptr);
    /**
     * @tc.desc: create parent and child framenode
     */
    frameNode->AddChild(firstItem);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto framePattern = frameNode->GetPattern<ShapeContainerPattern>();
    EXPECT_FALSE(framePattern == nullptr);
    auto layoutAlgorithm = framePattern->CreateLayoutAlgorithm();
    auto shapeContainerLayoutAlgorithm = AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(layoutAlgorithm);
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(shapeContainerLayoutAlgorithm));
    /**
     * @tc.desc: Set Parent LayoutConstraint
     */
    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    parentLayoutConstrain.percentReference = SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    firstItem->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);
    EXPECT_TRUE(firstItem->GetGeometryNode()->GetParentLayoutConstraint());

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.desc: set child GeometryNode MarginFrameSize
     * Call GetChildrenSize(childSize.Width() > 0 && childSize.Height() > 0)
     */
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    firstGeometryNode->GetMarginFrameSize().SetMainSize(MAIN_SIZE, Axis::HORIZONTAL);

    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstItem, firstGeometryNode, firstItem->GetLayoutProperty());
    EXPECT_FALSE(firstLayoutWrapper == nullptr);
    auto firstItemPattern = firstItem->GetPattern<CirclePattern>();
    EXPECT_FALSE(firstItemPattern == nullptr);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * @tc.desc: set child2 GeometryNode MarginFrameSize == NULL
     * Call GetChildrenSize(childSize.Width() == 0 && childSize.Height() == 0)
     */
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstItem, secondGeometryNode, firstItem->GetLayoutProperty());
    EXPECT_FALSE(secondLayoutWrapper == nullptr);
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(secondLayoutWrapper);
    auto childFrame = shapeContainerLayoutAlgorithm->GetChildrenSize(&layoutWrapper, SizeF(0, 0));
    EXPECT_TRUE(childFrame.IsNonNegative());
}

/**
 * @tc.name: IsEnableMatchParentTest
 * @tc.desc: check ShapePattern IsEnableMatchParent
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTestNg, IsEnableMatchParentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: Check Function IsEnableMatchParent's return value.
     * @tc.expected: Function IsEnableMatchParent returns true.
     */
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: MeasureContent
 * @tc.desc: check ShapeLayoutAlgorithm MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(ShapePatternTestNg, MeasureContent004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    ASSERT_TRUE(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_TRUE(geometryNode);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto pattern = AceType::MakeRefPtr<ShapePattern>();
    ASSERT_TRUE(pattern);
    frameNode->pattern_ = pattern;
    auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);

    /**
     * @tc.steps2: selfIdealSize is valid
     * @tc.expected: the return value of MeasureContent is (300, 400)
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(50, 50);
    contentConstraint.selfIdealSize = OptionalSizeF(300, 400);
    contentConstraint.percentReference = SizeF(500, 600);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(300, 400));
    contentConstraint.selfIdealSize.Reset();

    /**
     * @tc.steps3: measureType is MATCH_PARENT
     * @tc.expected: the return value of MeasureContent is (500, 600)
     */
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(500, 600));

    /**
     * @tc.steps4: Width is matchParent
     * @tc.expected: the return value of MeasureContent is (100, 50)
     */
    layoutProperty->measureType_ = MeasureType::MATCH_CONTENT;
    contentConstraint.parentIdealSize = OptionalSizeF(100, 200);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 50));

    /**
     * @tc.steps5: Height is matchParent
     * @tc.expected: the return value of MeasureContent is (50, 200)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(50, 200));

    /**
     * @tc.steps6: Width and Height is not matchParent
     * @tc.expected: the return value of MeasureContent is (50, 50)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(50, 50));

    /**
     * @tc.steps7: layoutPolicy has no value
     * @tc.expected: the return value of MeasureContent is (50, 50)
     */
    layoutProperty->layoutPolicy_ = std::nullopt;
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(50, 50));
}
} // namespace OHOS::Ace::NG
