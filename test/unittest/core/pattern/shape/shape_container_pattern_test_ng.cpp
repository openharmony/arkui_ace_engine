/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "foundation/arkui/ace_engine/test/mock/core/rosen/mock_canvas.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#define private public
#define protected public

#include "base_shape_pattern_test_ng.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
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
const float LEFT = -20.0f;
const float TOP = -30.0f;
const float ZERO = 0.0;
const int32_t COLUMN = 2;
const int32_t ROW = 3;
static constexpr double STROKE_MITERLIMIT_FIRST = -0.1f;
static constexpr double STROKE_MITERLIMIT_SECONG = 0.0f;
static constexpr double STROKE_MITERLIMIT_THIRD = 4.0f;
SizeF sizeF(80.0f, 20.0f);
std::vector<float> MESH = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };
} // namespace

class ShapeContainerPatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        return nullptr;
    }

    void Draw(RefPtr<FrameNode> frameNode) override {}
};

/**
 * @tc.name: OnDirtyLayoutWrapperSwap
 * @tc.desc: check ShapeContainerPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = true; dirty->SkipMeasureContent() = false;
     *           isShapeContainerInit_ = false)
     */
    auto flag01 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(flag01);
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = false; dirty->SkipMeasureContent() = false;
     *           isShapeContainerInit_ = false)
     */
    auto flag02 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_TRUE(flag02);
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = false; dirty->SkipMeasureContent() = true;
     *           isShapeContainerInit_ = true)
     */
    layoutWrapper->skipMeasureContent_ = std::make_optional<bool>(true);
    EXPECT_TRUE(layoutWrapper);
    auto flag03 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_FALSE(flag03);
    /**
     * @tc.desc: Call ViewPortTransform(false)
     */
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_TRUE(paintProperty);
    pattern->ViewPortTransform();
    paintProperty->propShapeViewBox_ = std::nullopt;
    pattern->ViewPortTransform();
    EXPECT_EQ(pattern->isShapeContainerInit_, true);
    /**
     * @tc.desc: Call OnModifyDone(false)
     */
    pattern->OnModifyDone();
}

/**
 * @tc.name: ViewPortTransform
 * @tc.desc: check ShapeContainerPattern ViewPortTransform
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, ViewPortTransform001, TestSize.Level1)
{
    /**
     * @tc.desc: Call ViewPortTransform(HasShapeViewBox = true; IsValid = false; first_if = false)
     */
    auto shapeModel01 = ShapeModelNG();
    shapeModel01.Create();
    shapeModel01.SetViewPort(Dimension(ZERO), Dimension(ZERO), Dimension(ZERO), Dimension(ZERO));
    shapeModel01.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    auto paintProperty01 = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    pattern->ViewPortTransform();
    EXPECT_TRUE(paintProperty01->HasShapeViewBox());
    ViewStackProcessor::GetInstance()->Pop();
    /**
     * @tc.desc: Call ViewPortTransform(HasShapeViewBox = true; IsValid = true; first_if = true;
     *           IsPositive = false; portWidth = true; portHeight = true; second_if = false)
     */
    auto shapeModel02 = ShapeModelNG();
    shapeModel02.Create();
    shapeModel02.SetViewPort(Dimension(LEFT), Dimension(TOP), Dimension(WIDTH), Dimension(HEIGHT));
    shapeModel02.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode01 = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode01 = AceType::DynamicCast<FrameNode>(uiNode01);
    auto pattern01 = frameNode01->GetPattern<ShapeContainerPattern>();
    auto paintProperty02 = frameNode01->GetPaintProperty<ShapeContainerPaintProperty>();
    pattern01->ViewPortTransform();
    EXPECT_TRUE(paintProperty02->GetShapeViewBoxValue().IsValid());
    ViewStackProcessor::GetInstance()->Pop();
    /**
     * @tc.desc: Call ViewPortTransform(HasShapeViewBox = true; IsValid = true; first_if = true;
     *           IsPositive = true; portWidth = true; portHeight = true; second_if = true;
     *           HasOffset = false; third_if = false)
     */
    auto shapeModel03 = ShapeModelNG();
    shapeModel03.Create();
    shapeModel03.SetViewPort(Dimension(LEFT), Dimension(TOP), Dimension(WIDTH), Dimension(HEIGHT));
    shapeModel03.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode03 = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode03 = AceType::DynamicCast<FrameNode>(uiNode03);
    auto pattern03 = frameNode03->GetPattern<ShapeContainerPattern>();
    auto paintProperty03 = frameNode03->GetPaintProperty<ShapeContainerPaintProperty>();
    auto geometryNode = frameNode03->GetGeometryNode();
    geometryNode->SetContentSize(sizeF);
    // add frameNode child
    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    rowNode->MountToParent(frameNode03);
    pattern03->ViewPortTransform();
    auto node = AceType::DynamicCast<FrameNode>(rowNode);
    auto context = node->GetRenderContext();
    EXPECT_EQ(context->HasOffset(), false);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: ViewPortTransform
 * @tc.desc: check ShapeContainerPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto shapeModel01 = ShapeModelNG();
    shapeModel01.Create();
    RefPtr<UINode> uiNode01 = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode01 = AceType::DynamicCast<FrameNode>(uiNode01);
    auto pattern01 = frameNode01->GetPattern<ShapeContainerPattern>();
    auto paintProperty01 = frameNode01->GetPaintProperty<ShapeContainerPaintProperty>();
    /**
     * @tc.desc: Call OnModifyDone(HasStrokeMiterLimit = false; first_if = false;
     *           !child = false; third = false)
     */
    WeakPtr<FrameNode> childNode = frameNode01;
    pattern01->AddChildShapeNode(childNode);
    pattern01->OnModifyDone();
    EXPECT_EQ(paintProperty01->HasStrokeMiterLimit(), false);
    /**
     * @tc.desc: Call OnModifyDone(HasStrokeMiterLimit = true; first_if = true;
     *           Negative = true; NonNegative = false; second_if = true;
     */
    paintProperty01->UpdateStrokeMiterLimit(STROKE_MITERLIMIT_FIRST);
    pattern01->OnModifyDone();
    EXPECT_EQ(paintProperty01->HasStrokeMiterLimit(), true);
    EXPECT_EQ(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
    EXPECT_NE(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_MIN);
    /**
     * @tc.desc: Call OnModifyDone(HasStrokeMiterLimit = true; first_if = true;
     *           Negative = false; NonNegative = true; second_if = true;
     */
    paintProperty01->UpdateStrokeMiterLimit(STROKE_MITERLIMIT_SECONG);
    pattern01->OnModifyDone();
    EXPECT_NE(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
    EXPECT_EQ(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_MIN);
    /**
     * @tc.desc: Call OnModifyDone(HasStrokeMiterLimit = true; first_if = true;
     *           Negative = false; NonNegative = false; second_if = false;
     */
    paintProperty01->UpdateStrokeMiterLimit(STROKE_MITERLIMIT_THIRD);
    pattern01->OnModifyDone();
    EXPECT_EQ(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
    EXPECT_NE(paintProperty01->GetStrokeMiterLimitValue(), ShapePaintProperty::STROKE_MITERLIMIT_MIN);
}

/**
 * @tc.name: ShapeContainerModifier
 * @tc.desc: check ShapeContainer ContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, ShapeContainerModifier, TestSize.Level1)
{
    /**
     * @tc.desc: Call CreateShape with mesh&pixelmap
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto shapeModel01 = ShapeModelNG();
    shapeModel01.Create();
    shapeModel01.SetBitmapMesh(MESH, COLUMN, ROW);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    shapeModel01.InitBox(pixelMap);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    EXPECT_TRUE(pattern);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeShapeMethod = pattern->CreateNodePaintMethod();
    EXPECT_TRUE(shapeShapeMethod);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), frameNode->GetGeometryNode(), paintProperty);
    shapeShapeMethod->UpdateContentModifier(&paintWrapper);
    auto contentModifier =
        AceType::DynamicCast<ShapeContainerModifier>(shapeShapeMethod->GetContentModifier(&paintWrapper));
    EXPECT_TRUE(contentModifier);
    auto row = contentModifier->row_;
    EXPECT_TRUE(row);
    auto column = contentModifier->column_;
    EXPECT_TRUE(column);
    EXPECT_EQ(row->Get(), ROW);
    EXPECT_EQ(column->Get(), COLUMN);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    DrawingContext context = { rsCanvas, 1.f, 1.f };
    contentModifier->onDraw(context);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
