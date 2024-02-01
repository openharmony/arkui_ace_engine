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

#include "base_polygon_pattern_test_ng.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class PolylinePatternTestNg : public BasePolygonPatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        PolygonModelNG().Create(false);
        return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override
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

    void CheckPolylinePoints(bool hasValue)
    {
        PolygonModelNG().Create(false);
        auto shapeAbstactModel = ShapeAbstractModelNG();
        SetSize(shapeAbstactModel);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        CheckPoints(frameNode, hasValue);
        Draw(frameNode);
    }
};

/**
 * @tc.name: PolylinePaintProperty001
 * @tc.desc: create polyline with points
 * @tc.type: FUNC
 */

HWTEST_F(PolylinePatternTestNg, PolylinePaintProperty001, TestSize.Level1)
{
    CheckPolylinePoints(true);
}

/**
 * @tc.name: PolylinePaintProperty002
 * @tc.desc: create polyline with no points
 * @tc.type: FUNC
 */

HWTEST_F(PolylinePatternTestNg, PolylinePaintProperty002, TestSize.Level1)
{
    CheckPolylinePoints(false);
}

} // namespace OHOS::Ace::NG