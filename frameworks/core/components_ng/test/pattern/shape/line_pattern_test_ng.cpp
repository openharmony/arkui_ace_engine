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

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/pattern/shape/line_paint_property.h"
#include "core/components_ng/pattern/shape/line_pattern.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float START_X = 2.0f;
constexpr float START_Y = 1.0f;
constexpr float END_X = 15.0f;
constexpr float END_Y = 30.0f;
} // namespace

class LinePatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        LineModelNG().Create();
        return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<LinePattern>();
        EXPECT_EQ(pattern == nullptr, false);
        auto layoutProperty = frameNode->GetLayoutProperty();
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
        frameNode->GetGeometryNode()->SetContentSize(size.value());
        auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(),
            frameNode->GetGeometryNode()->Clone(), frameNode->GetPaintProperty<ShapePaintProperty>());
        EXPECT_EQ(paintWrapper == nullptr, false);
        auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_EQ(contentDraw == nullptr, false);
        std::shared_ptr<SkCanvas> canvas = std::make_shared<SkCanvas>();
        RSCanvas rsCavas(&canvas);
        contentDraw(rsCavas);
    }

    void CheckPoints(ShapePoint* startPoint, ShapePoint* endPoint)
    {
        auto lineModelNg = LineModelNG();
        lineModelNg.Create();
        auto hasStart = (startPoint != nullptr);
        auto hasEnd = (endPoint != nullptr);
        if (hasStart) {
            lineModelNg.StartPoint(*startPoint);
        }
        if (hasEnd) {
            lineModelNg.EndPoint(*endPoint);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        EXPECT_EQ(frameNode == nullptr, false);
        auto shapeAbstactModel = ShapeAbstractModelNG();
        SetSize(shapeAbstactModel);
        ViewStackProcessor::GetInstance()->Pop();
        auto lineProperty = frameNode->GetPaintProperty<LinePaintProperty>();
        EXPECT_EQ(lineProperty == nullptr, false);
        if (hasStart) {
            EXPECT_EQ(lineProperty->HasStartPoint(), true);
            EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().first.ConvertToPx(), START_X);
            EXPECT_FLOAT_EQ(lineProperty->GetStartPointValue().second.ConvertToPx(), START_Y);
        } else {
            EXPECT_EQ(lineProperty->HasStartPoint(), false);
        }
        if (hasEnd) {
            EXPECT_EQ(lineProperty->HasEndPoint(), true);
            EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().first.ConvertToPx(), END_X);
            EXPECT_FLOAT_EQ(lineProperty->GetEndPointValue().second.ConvertToPx(), END_Y);
        } else {
            EXPECT_EQ(lineProperty->HasEndPoint(), false);
        }
        if (hasStart && hasEnd) {
            Draw(frameNode);
        }
    }
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
    CheckPoints(&startPoint, &endPoint);
}

/**
 * @tc.name: PointTest002
 * @tc.desc: set startPoint but no endPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest002, TestSize.Level1)
{
    auto startPoint = ShapePoint(Dimension(START_X), Dimension(START_Y));
    CheckPoints(&startPoint, nullptr);
}

/**
 * @tc.name: PointTest003
 * @tc.desc: set endPoint but no startPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest003, TestSize.Level1)
{
    auto endPoint = ShapePoint(Dimension(END_X), Dimension(END_Y));
    CheckPoints(nullptr, &endPoint);
}

/**
 * @tc.name: PointTest004
 * @tc.desc: set no startPoint or endPoint
 * @tc.type: FUNC
 */

HWTEST_F(LinePatternTestNg, PointTest004, TestSize.Level1)
{
    CheckPoints(nullptr, nullptr);
}
} // namespace OHOS::Ace::NG
