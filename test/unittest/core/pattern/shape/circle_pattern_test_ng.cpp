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

#include "base_shape_pattern_test_ng.h"
#include "gtest/gtest.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CirclePatternTestNg : public BaseShapePatternTestNg {
    RefPtr<FrameNode> CreadFrameNode() override
    {
        CircleModelNG().Create();
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<CirclePattern>();
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
        EXPECT_CALL(rsCavas, DrawCircle(_, _)).WillOnce(Return());
        EXPECT_CALL(rsCavas, DetachPen()).WillOnce(ReturnRef(rsCavas));
        EXPECT_CALL(rsCavas, DetachBrush()).WillOnce(ReturnRef(rsCavas));
        contentDraw(rsCavas);
    }
};

/**
 * @tc.name: Creator001
 * @tc.desc: create circle with width and height
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, Creator001, TestSize.Level1)
{
    CheckSize(true);
}

/**
 * @tc.name: PaintFill001
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintFill001, TestSize.Level1)
{
    CheckFill(true);
}

/**
 * @tc.name: PaintFill002
 * @tc.desc: set no fill and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintFill002, TestSize.Level1)
{
    CheckFill(false);
}

/**
 * @tc.name: PaintFillOpacity001
 * @tc.desc: set no fill opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintFillOpacity001, TestSize.Level1)
{
    CheckFillOpacity(true);
}

/**
 * @tc.name: PaintFillOpacity002
 * @tc.desc: set no fill opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintFillOpacity002, TestSize.Level1)
{
    CheckFillOpacity(false);
}

/**
 * @tc.name: PaintStroke001
 * @tc.desc: set stroke and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStroke001, TestSize.Level1)
{
    CheckStroke(true);
}

/**
 * @tc.name: PaintStroke002
 * @tc.desc: set no stroke and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStroke002, TestSize.Level1)
{
    CheckStroke(false);
}

/**
 * @tc.name: PaintAntiAlias001
 * @tc.desc: set antialias and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintAntiAlias001, TestSize.Level1)
{
    CheckAntiAlias(true);
}

/**
 * @tc.name: PaintAntiAlias001
 * @tc.desc: set no antialias and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintAntiAlias002, TestSize.Level1)
{
    CheckAntiAlias(false);
}

/**
 * @tc.name: PaintStrokeWidth001
 * @tc.desc: set stroke width and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeWidth001, TestSize.Level1)
{
    CheckStrokeWidth(true);
}

/**
 * @tc.name: PaintStrokeWidth002
 * @tc.desc: set no stroke width and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeWidth002, TestSize.Level1)
{
    CheckStrokeWidth(false);
}

/**
 * @tc.name: PaintStrokeOpacity001
 * @tc.desc: set stroke opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeOpacity001, TestSize.Level1)
{
    CheckStrokeOpacity(true);
}

/**
 * @tc.name: PaintStrokeOpacity002
 * @tc.desc: set no stroke opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeOpacity002, TestSize.Level1)
{
    CheckStrokeOpacity(false);
}

/**
 * @tc.name: PaintStrokeDashArray001
 * @tc.desc: set dash Array and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeDashArray001, TestSize.Level1)
{
    CheckStrokeDashArray(true);
}

/**
 * @tc.name: PaintStrokeDashArray002
 * @tc.desc: set no dash Array and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeDashArray002, TestSize.Level1)
{
    CheckStrokeDashArray(false);
}

/**
 * @tc.name: PaintStrokeDashOffset001
 * @tc.desc: set stroke dash offset and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeDashOffset001, TestSize.Level1)
{
    CheckStrokeDashOffset(true);
}

/**
 * @tc.name: PaintStrokeDashOffset002
 * @tc.desc: set no stroke dash offset and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeDashOffset002, TestSize.Level1)
{
    CheckStrokeDashOffset(false);
}

/**
 * @tc.name: PaintStrokeLineCap001
 * @tc.desc: set stroke line cap and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeLineCap001, TestSize.Level1)
{
    CheckStrokeLineCap(true);
}

/**
 * @tc.name: PaintStrokeLineCap002
 * @tc.desc: set no stroke line cap and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeLineCap002, TestSize.Level1)
{
    CheckStrokeLineCap(false);
}

/**
 * @tc.name: PaintStrokeLineJoin001
 * @tc.desc: set stroke line join and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeLineJoin001, TestSize.Level1)
{
    CheckStrokeLineJoin(true);
}

/**
 * @tc.name: PaintStrokeLineJoin002
 * @tc.desc: set stroke line join and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeLineJoin002, TestSize.Level1)
{
    CheckStrokeLineJoin(false);
}

/**
 * @tc.name: PaintStrokeMiterLimit001
 * @tc.desc: set stroke miter limit and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeMiterLimit001, TestSize.Level1)
{
    CheckStrokeMiterLimit(true);
}

/**
 * @tc.name: PaintStrokeMiterLimit002
 * @tc.desc: set stroke miter limit and check
 * @tc.type: FUNC
 */

HWTEST_F(CirclePatternTestNg, PaintStrokeMiterLimit002, TestSize.Level1)
{
    CheckStrokeMiterLimit(false);
}

} // namespace OHOS::Ace::NG