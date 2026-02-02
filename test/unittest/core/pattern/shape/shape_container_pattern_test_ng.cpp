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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_static.h"
#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_static.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "test/mock/base/mock_pixel_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t NODE_ID = 1;
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
        ShapeModelNG().Create();
        return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override {}

    RefPtr<ShapePaintProperty> GetShapePaintProperty(FrameNode* frameNode)
    {
        auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
        if (!pattern) {
            return nullptr;
        }
        return pattern->GetPaintProperty<ShapePaintProperty>();
    }

    RefPtr<ShapeContainerPaintProperty> GetShapeContainerPaintProperty(FrameNode* frameNode)
    {
        auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
        if (!pattern) {
            return nullptr;
        }
        return pattern->GetPaintProperty<ShapeContainerPaintProperty>();
    }
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

/**
 * @tc.name: IsEnableMatchParentTest
 * @tc.desc: check ShapeContainerPattern IsEnableMatchParent
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, IsEnableMatchParentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto shapeModel01 = ShapeModelNG();
    shapeModel01.Create();
    shapeModel01.SetViewPort(Dimension(ZERO), Dimension(ZERO), Dimension(ZERO), Dimension(ZERO));
    shapeModel01.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: Check Function IsEnableMatchParent's return value.
     * @tc.expected: Function IsEnableMatchParent returns true.
     */
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: IsEnableChildrenMatchParentTest
 * @tc.desc: Test IsEnableChildrenMatchParent Func
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, IsEnableChildrenMatchParentTest, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto shapeModel01 = ShapeModelNG();
    shapeModel01.Create();
    shapeModel01.SetViewPort(Dimension(ZERO), Dimension(ZERO), Dimension(ZERO), Dimension(ZERO));
    shapeModel01.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps2: Check Function IsEnableChildrenMatchParent's return value.
     * @tc.expected: Function IsEnableChildrenMatchParent returns true.
     */
    EXPECT_TRUE(pattern->IsEnableChildrenMatchParent());
}

/**
 * @tc.name: MeasureLayoutPolicySize001
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureLayoutPolicySize
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, MeasureLayoutPolicySize001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    /**
     * @tc.steps1: layoutProperty is null
     * @tc.expected: the size is (300, 600)
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);
    LayoutConstraintF constrain;
    constrain.maxSize = SizeF(1000, 1000);
    constrain.minSize = SizeF(300, 600);
    auto layoutAlgorithm = AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    SizeF size = SizeF(100.0, 100.0);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(300, 600));

    /**
     * @tc.steps2: LayoutPolicyProperty does not have value
     * @tc.expected: the size is (300, 600)
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->layoutPolicy_.reset();
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    size = SizeF(100.0, 100.0);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(300, 600));
}

/**
 * @tc.name: MeasureLayoutPolicySize002
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureLayoutPolicySize
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, MeasureLayoutPolicySize002, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    /**
     * @tc.steps1: Width and Height are NO_MATCH
     * @tc.expected: the size is (400, 600)
     */
    LayoutConstraintF constrain;
    constrain.maxSize = SizeF(1000, 1000);
    constrain.minSize = SizeF(300, 600);
    constrain.parentIdealSize = OptionalSizeF(500, 500);
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    SizeF size = SizeF(400, 400);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(400, 600));
    /**
     * @tc.steps2: Width and Height are MATCH_PARENT
     * @tc.expected: the size is (500, 500)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    size = SizeF(400, 400);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(500, 500));
    /**
     * @tc.steps3: Width and Height are MATCH_PARENT and parentIdealSize is null
     * @tc.expected: the size is (400, 600)
     */
    size = SizeF(400, 400);
    constrain.parentIdealSize.Reset();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(400, 600));
    /**
     * @tc.steps4: Width and Height are default
     * @tc.expected: the size is (400, 600)
     */
    size = SizeF(400, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy(4), true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy(4), false);
    layoutAlgorithm->MeasureLayoutPolicySize(constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(400, 600));
}

/**
 * @tc.name: MeasureLayoutPolicySize003
 * @tc.desc: check ShapeContainerLayoutAlgorithm MeasureLayoutPolicySize
 * @tc.type: FUNC
 */
HWTEST_F(ShapeContainerPatternTestNg, MeasureLayoutPolicySize003, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    /**
     * @tc.steps1: Width and Height are WRAP_CONTENT
     * @tc.expected: the size is (400, 600)
     */
    LayoutConstraintF constrain;
    constrain.maxSize = SizeF(1000, 1000);
    constrain.minSize = SizeF(300, 600);
    constrain.parentIdealSize = OptionalSizeF(500, 500);
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<ShapeContainerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    SizeF size = SizeF(400, 400);
    layoutAlgorithm->MeasureLayoutPolicySize(
        constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(400, 600));
    /**
     * @tc.steps2: Width and Height are FIX_AT_IDEAL_SIZE and paintProperty is null
     * @tc.expected: the size is (400, 400)
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    size = SizeF(400, 400);
    layoutAlgorithm->MeasureLayoutPolicySize(
        constrain, AceType::RawPtr(layoutWrapper), nullptr, size);
    EXPECT_EQ(size, SizeF(400, 400));
    /**
     * @tc.steps3: Width and Height are FIX_AT_IDEAL_SIZE and pixelmap is null
     * @tc.expected: the size is (400, 400)
     */
    auto pixelMapInfo = ImageSourceInfo();
    paintProperty->UpdatePixelMapInfo(pixelMapInfo);
    pixelMapInfo.pixmap_ = nullptr;
    layoutAlgorithm->MeasureLayoutPolicySize(
        constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(400, 400));

    /**
     * @tc.steps4: Width and Height are FIX_AT_IDEAL_SIZE and pixelmap size is (600, 600)
     * @tc.expected: the size is (600, 600)
     */
    RefPtr<MockPixelMap> pixMap = AceType::MakeRefPtr<MockPixelMap>();
    pixelMapInfo = ImageSourceInfo(pixMap);
    paintProperty->UpdatePixelMapInfo(pixelMapInfo);
    EXPECT_CALL(*pixMap.GetRawPtr(), GetWidth()).Times(1).WillOnce(Return(600));
    EXPECT_CALL(*pixMap.GetRawPtr(), GetHeight()).Times(1).WillOnce(Return(600));
    layoutAlgorithm->MeasureLayoutPolicySize(
        constrain, AceType::RawPtr(layoutWrapper), paintProperty, size);
    EXPECT_EQ(size, SizeF(600, 600));
}

/**
 * @tc.name: Paint001
 * @tc.desc: set stroke and draw
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStrokeTest, TestSize.Level1)
{
    CheckStroke(true);
}

/**
 * @tc.name: SetStroke001
 * @tc.desc: test SetStroke
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStroke001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetStroke(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStroke());
    EXPECT_EQ(paintProperty->GetStrokeValue(), Color::TRANSPARENT);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_COLOR, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_COLOR, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetStroke(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStroke());
    EXPECT_EQ(paintProperty->GetStrokeValue(), Color::BLUE);

    shapeModelNG.SetStroke(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetFill001
 * @tc.desc: test SetFill
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetFill001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetFill(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFill());
    EXPECT_EQ(paintProperty->GetFillValue(), Color::BLACK);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_COLOR, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_COLOR, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetFill(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFill());
    EXPECT_EQ(paintProperty->GetFillValue(), Color::BLUE);

    shapeModelNG.SetFill(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetForegroundColor001
 * @tc.desc: test SetForegroundColor
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetForegroundColor001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetForegroundColor(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFill());
    EXPECT_EQ(paintProperty->GetFillValue(), Color::BLACK);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_COLOR, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_COLOR, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetForegroundColor(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFill());
    EXPECT_EQ(paintProperty->GetFillValue(), Color::BLUE);

    shapeModelNG.SetForegroundColor(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeDashOffset001
 * @tc.desc: test SetStrokeDashOffset
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStrokeDashOffset001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetStrokeDashOffset(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeDashOffset());
    EXPECT_EQ(paintProperty->GetStrokeDashOffset()->ConvertToPx(), 0.0f);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_DASH_OFFSET, Dimension(DASHOFFSET));
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_DASH_OFFSET, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetStrokeDashOffset(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeDashOffset());
    EXPECT_EQ(paintProperty->GetStrokeDashOffset()->ConvertToPx(), DASHOFFSET);

    shapeModelNG.SetStrokeDashOffset(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeMiterLimit001
 * @tc.desc: test SetStrokeMiterLimit
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStrokeMiterLimit001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetStrokeMiterLimit(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeMiterLimitValue()), DEFAULT_STROKE_LIMIT);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_STROKE_LIMIT, STROKE_LIMIT);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_STROKE_LIMIT, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetStrokeMiterLimit(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeMiterLimit());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeMiterLimitValue()), STROKE_LIMIT);

    shapeModelNG.SetStrokeMiterLimit(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeOpacity001
 * @tc.desc: test SetStrokeOpacity
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStrokeOpacity001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetStrokeOpacity(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeOpacity());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeOpacityValue()), 1.0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_OPACITY, OPACITY);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_OPACITY, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetStrokeOpacity(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeOpacity());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeOpacityValue()), OPACITY);

    shapeModelNG.SetStrokeOpacity(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetFillOpacity001
 * @tc.desc: test SetFillOpacity
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetFillOpacity001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetFillOpacity(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFillOpacity());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetFillOpacityValue()), 1.0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_OPACITY, OPACITY);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_OPACITY, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetFillOpacity(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasFillOpacity());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetFillOpacityValue()), OPACITY);

    shapeModelNG.SetFillOpacity(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeWidth001
 * @tc.desc: test SetStrokeWidth
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, SetStrokeWidth001, TestSize.Level1)
{
    auto shapeModelNG = ShapeModelNG();
    shapeModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    shapeModelNG.SetStrokeWidth(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeWidth());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeWidthValue().ConvertToVp()), 1.0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_STROKE_WIDTH, Dimension(STROKE_WIDTH));
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_STROKE_WIDTH, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    shapeModelNG.SetStrokeWidth(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(paintProperty->HasStrokeWidth());
    EXPECT_FLOAT_EQ(static_cast<float>(paintProperty->GetStrokeWidthValue().ConvertToPx()), STROKE_WIDTH);

    shapeModelNG.SetStrokeWidth(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStroke_Test
 * @tc.desc: Test SetStroke function with and without color.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStroke_Test, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Color> color = Color::RED;
    ShapeModelStatic::SetStroke(frameNode, color);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStroke().has_value());
    EXPECT_EQ(paintProp->GetStroke().value(), Color::RED);

    std::optional<Color> noColor;
    ShapeModelStatic::SetStroke(frameNode, noColor);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStroke().has_value());
}

/**
 * @tc.name: SetFill_Test
 * @tc.desc: Test SetFill function with and without color.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetFill_Test, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Color> color = Color::BLUE;
    ShapeModelStatic::SetFill(frameNode, color);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetFill().has_value());
    EXPECT_EQ(paintProp->GetFill().value(), Color::BLUE);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetForegroundColor().has_value());
    EXPECT_EQ(renderContext->GetForegroundColor().value(), Color::BLUE);
    EXPECT_TRUE(renderContext->GetForegroundColorFlag().has_value());
    EXPECT_EQ(renderContext->GetForegroundColorFlag().value(), true);

    std::optional<Color> noColor;
    ShapeModelStatic::SetFill(frameNode, noColor);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetFill().has_value());
    EXPECT_EQ(paintProp->GetFill().value(), Color::BLACK);
    
    renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->GetForegroundColor().has_value());
    EXPECT_TRUE(renderContext->GetForegroundColorFlag().has_value());
    EXPECT_EQ(renderContext->GetForegroundColorFlag().value(), false);
}

/**
 * @tc.name: SetStrokeDashOffset_Test001
 * @tc.desc: Test SetStrokeDashOffset function with and without dashOffset.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeDashOffset_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> dashOffset = Dimension(10.0);
    ShapeModelStatic::SetStrokeDashOffset(frameNode, dashOffset);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeDashOffset().has_value());
    EXPECT_EQ(paintProp->GetStrokeDashOffset().value(), Dimension(10.0));

    std::optional<Dimension> noDashOffset;
    ShapeModelStatic::SetStrokeDashOffset(frameNode, noDashOffset);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeDashOffset().has_value());
    EXPECT_EQ(paintProp->GetStrokeDashOffset().value(), 0.0_vp);
}

/**
 * @tc.name: SetStrokeLineCap_Test001
 * @tc.desc: Test SetStrokeLineCap function with and without lineCapStyle.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeLineCap_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<int> lineCapStyle = 1;
    ShapeModelStatic::SetStrokeLineCap(frameNode, lineCapStyle);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeLineCap().has_value());
    EXPECT_EQ(paintProp->GetStrokeLineCap().value(), 1);

    std::optional<int> noLineCapStyle;
    ShapeModelStatic::SetStrokeLineCap(frameNode, noLineCapStyle);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStrokeLineCap().has_value());
}

/**
 * @tc.name: SetStrokeLineJoin_Test001
 * @tc.desc: Test SetStrokeLineJoin function with and without lineJoinStyle.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeLineJoin_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<int> lineJoinStyle = 2;
    ShapeModelStatic::SetStrokeLineJoin(frameNode, lineJoinStyle);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeLineJoin().has_value());
    EXPECT_EQ(paintProp->GetStrokeLineJoin().value(), 2);

    std::optional<int> noLineJoinStyle;
    ShapeModelStatic::SetStrokeLineJoin(frameNode, noLineJoinStyle);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStrokeLineJoin().has_value());
}

/**
 * @tc.name: SetStrokeMiterLimit_Test001
 * @tc.desc: Test SetStrokeMiterLimit function with and without miterLimit.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeMiterLimit_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<double> miterLimit = 5.0;
    ShapeModelStatic::SetStrokeMiterLimit(frameNode, miterLimit);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeMiterLimit().has_value());
    EXPECT_EQ(paintProp->GetStrokeMiterLimit().value(), 5.0);

    std::optional<double> noMiterLimit;
    ShapeModelStatic::SetStrokeMiterLimit(frameNode, noMiterLimit);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStrokeMiterLimit().has_value());
}

/**
 * @tc.name: SetFillOpacity_Test001
 * @tc.desc: Test SetFillOpacity function with and without fillOpacity, including clamp.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetFillOpacity_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<double> fillOpacity = 0.5;
    ShapeModelStatic::SetFillOpacity(frameNode, fillOpacity);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetFillOpacity().has_value());
    EXPECT_DOUBLE_EQ(paintProp->GetFillOpacity().value(), 0.5);

    std::optional<double> fillOpacityLow = -0.1;
    ShapeModelStatic::SetFillOpacity(frameNode, fillOpacityLow);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetFillOpacity().has_value());
    EXPECT_DOUBLE_EQ(paintProp->GetFillOpacity().value(), 0.0);

    std::optional<double> fillOpacityHigh = 1.5;
    ShapeModelStatic::SetFillOpacity(frameNode, fillOpacityHigh);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetFillOpacity().has_value());
    EXPECT_DOUBLE_EQ(paintProp->GetFillOpacity().value(), 1.0);

    std::optional<double> noFillOpacity;
    ShapeModelStatic::SetFillOpacity(frameNode, noFillOpacity);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetFillOpacity().has_value());
}

/**
 * @tc.name: SetStrokeOpacity_Test001
 * @tc.desc: Test SetStrokeOpacity function with and without strokeOpacity.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeOpacity_Test001, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<double> strokeOpacity = 0.8;
    ShapeModelStatic::SetStrokeOpacity(frameNode, strokeOpacity);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeOpacity().has_value());
    EXPECT_DOUBLE_EQ(paintProp->GetStrokeOpacity().value(), 0.8);

    std::optional<double> noStrokeOpacity;
    ShapeModelStatic::SetStrokeOpacity(frameNode, noStrokeOpacity);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStrokeOpacity().has_value());
}

/**
 * @tc.name: SetStrokeWidth_Test
 * @tc.desc: Test SetStrokeWidth function with and without strokeWidth.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeWidth_Test, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);

    std::optional<Dimension> strokeWidth = Dimension(2.0);
    ShapeModelStatic::SetStrokeWidth(frameNode, strokeWidth);
    
    auto paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_TRUE(paintProp->GetStrokeWidth().has_value());
    EXPECT_EQ(paintProp->GetStrokeWidth().value(), Dimension(2.0));

    std::optional<Dimension> noStrokeWidth;
    ShapeModelStatic::SetStrokeWidth(frameNode, noStrokeWidth);
    
    paintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(paintProp, nullptr);
    EXPECT_FALSE(paintProp->GetStrokeWidth().has_value());
}

/**
 * @tc.name: SetStrokeDashOffset_Test002
 * @tc.desc: Test SetStrokeDashOffset function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeDashOffset_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    Dimension dashOffset = Dimension(15.0);
    ShapeAbstractModelStatic::SetStrokeDashOffset(frameNode, dashOffset);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetStrokeDashOffset().has_value());
    EXPECT_EQ(shapePaintProp->GetStrokeDashOffset().value(), Dimension(15.0));
}

/**
 * @tc.name: SetStrokeLineCap_Test002
 * @tc.desc: Test SetStrokeLineCap function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeLineCap_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    int lineCapStyle = 2;
    ShapeAbstractModelStatic::SetStrokeLineCap(frameNode, lineCapStyle);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetStrokeLineCap().has_value());
    EXPECT_EQ(shapePaintProp->GetStrokeLineCap().value(), 2);
}

/**
 * @tc.name: SetStrokeLineJoin_Test002
 * @tc.desc: Test SetStrokeLineJoin function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeLineJoin_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    int lineJoinStyle = 3;
    ShapeAbstractModelStatic::SetStrokeLineJoin(frameNode, lineJoinStyle);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetStrokeLineJoin().has_value());
    EXPECT_EQ(shapePaintProp->GetStrokeLineJoin().value(), 3);
}

/**
 * @tc.name: SetStrokeMiterLimit_Test002
 * @tc.desc: Test SetStrokeMiterLimit function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeMiterLimit_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    double miterLimit = 4.5;
    ShapeAbstractModelStatic::SetStrokeMiterLimit(frameNode, miterLimit);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetStrokeMiterLimit().has_value());
    EXPECT_DOUBLE_EQ(shapePaintProp->GetStrokeMiterLimit().value(), 4.5);
}

/**
 * @tc.name: SetStrokeOpacity_Test002
 * @tc.desc: Test SetStrokeOpacity function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetStrokeOpacity_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    double opacity = 0.75;
    ShapeAbstractModelStatic::SetStrokeOpacity(frameNode, opacity);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetStrokeOpacity().has_value());
    EXPECT_DOUBLE_EQ(shapePaintProp->GetStrokeOpacity().value(), 0.75);
}

/**
 * @tc.name: SetFillOpacity_Test002
 * @tc.desc: Test SetFillOpacity function.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetFillOpacity_Test002, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    double opacity = 0.6;
    ShapeAbstractModelStatic::SetFillOpacity(frameNode, opacity);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetFillOpacity().has_value());
    EXPECT_DOUBLE_EQ(shapePaintProp->GetFillOpacity().value(), 0.6);
}

/**
 * @tc.name: SetAntiAlias_Test
 * @tc.desc: Test SetAntiAlias function with true and false.
 */
HWTEST_F(ShapeContainerPatternTestNg, SetAntiAlias_Test, TestSize.Level1)
{
    auto frameNodeRef = ShapeModelStatic::CreateFrameNode(NODE_ID);
    auto frameNode = AceType::RawPtr(frameNodeRef);
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = AceType::MakeRefPtr<ShapePaintProperty>();

    bool antiAlias = true;
    ShapeAbstractModelStatic::SetAntiAlias(frameNode, antiAlias);
    
    auto shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetAntiAlias().has_value());
    EXPECT_EQ(shapePaintProp->GetAntiAlias().value(), true);

    antiAlias = false;
    ShapeAbstractModelStatic::SetAntiAlias(frameNode, antiAlias);
    
    shapePaintProp = GetShapePaintProperty(frameNode);
    ASSERT_NE(shapePaintProp, nullptr);
    EXPECT_TRUE(shapePaintProp->GetAntiAlias().has_value());
    EXPECT_EQ(shapePaintProp->GetAntiAlias().value(), false);
}
} // namespace OHOS::Ace::NG
