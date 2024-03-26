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

#include "base_shape_pattern_test_ng.h"
#include "gtest/gtest.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/ellipse_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class EllipsePatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        EllipseModelNG().Create();
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<EllipsePattern>();
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
        auto shapePaintProperty = AceType::DynamicCast<ShapePaintProperty>(paintWrapper->GetPaintProperty()->Clone());
        if (!shapePaintProperty->HasStrokeWidth() || !NearZero(shapePaintProperty->GetStrokeWidth()->Value())) {
            EXPECT_CALL(rsCavas, AttachPen(_)).WillOnce(ReturnRef(rsCavas));
        }
        EXPECT_CALL(rsCavas, AttachBrush(_)).WillOnce(ReturnRef(rsCavas));
        EXPECT_CALL(rsCavas, DrawOval(_)).WillOnce(Return());
#ifdef USE_ROSEN_DRAWING
        EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
        EXPECT_CALL(rsCavas, DetachBrush()).WillOnce(ReturnRef(rsCavas));
#endif
        contentDraw(rsCavas);
    }
};

/**
 * @tc.name: Paint001
 * @tc.desc: set stroke and draw
 * @tc.type: FUNC
 */

HWTEST_F(EllipsePatternTestNg, LAYOUTALGORITHOM001, TestSize.Level1)
{
    CheckStroke(true);
}

} // namespace OHOS::Ace::NG
