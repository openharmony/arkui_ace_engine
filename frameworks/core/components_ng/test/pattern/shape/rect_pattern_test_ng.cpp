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

#include <array>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/rect_pattern.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr std::array<std::array<float, 2>, 4> RADIUS = { { { 21, 4 }, { 3, 33 }, { 22, 44 }, { 0, 44 } } };
constexpr Dimension RADIUS_WIDTH = Dimension(20);
constexpr Dimension RADIUS_HEIGHT = Dimension(2);
constexpr int32_t INDEX_ZERO = 0;
constexpr int32_t INDEX_ONE = 1;
constexpr int32_t INDEX_TWO = 2;
constexpr int32_t INDEX_THREE = 3;
} // namespace
class RectPatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        RectModelNG().Create();
        return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    }

    void Draw(RefPtr<FrameNode> frameNode) override
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<RectPattern>();
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

    void CheckRadius(const RefPtr<FrameNode>& frameNode, bool hasValue)
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
        EXPECT_EQ(paintProperty == nullptr, false);
        if (hasValue) {
            EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
            EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
            EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
            EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
            EXPECT_FLOAT_EQ(
                paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), RADIUS.at(INDEX_ZERO).at(INDEX_ZERO));
            EXPECT_FLOAT_EQ(
                paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), RADIUS.at(INDEX_ZERO).at(INDEX_ONE));
            EXPECT_FLOAT_EQ(
                paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), RADIUS.at(INDEX_ONE).at(INDEX_ZERO));
            EXPECT_FLOAT_EQ(
                paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), RADIUS.at(INDEX_ONE).at(INDEX_ONE));
            EXPECT_FLOAT_EQ(
                paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), RADIUS.at(INDEX_TWO).at(INDEX_ZERO));
            EXPECT_FLOAT_EQ(
                paintProperty->GetBottomRightRadiusValue().GetY().ConvertToPx(), RADIUS.at(INDEX_TWO).at(INDEX_ONE));
            EXPECT_FLOAT_EQ(
                paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), RADIUS.at(INDEX_THREE).at(INDEX_ZERO));
            EXPECT_FLOAT_EQ(
                paintProperty->GetBottomLeftRadiusValue().GetY().ConvertToPx(), RADIUS.at(INDEX_THREE).at(INDEX_ONE));
        } else {
            EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
            EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
            EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
            EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
        }
        Draw(frameNode);
    }
};

/**
 * @tc.name: RectPaintProperty001
 * @tc.desc: create rect with radius
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, RectPaintProperty001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    for (int i = 0; i < RADIUS.size(); i++) {
        rectModelNG.SetRadiusValue(Dimension(RADIUS.at(i).at(0)), Dimension(RADIUS.at(i).at(1)), i);
    }
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    CheckRadius(frameNode, true);
}

/**
 * @tc.name: RectPaintProperty002
 * @tc.desc: create rect with invalid radius
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, RectPaintProperty002, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    rectModelNG.SetRadiusValue(Dimension(), Dimension(), RADIUS.size());
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    CheckRadius(frameNode, false);
}

/**
 * @tc.name: RectPaintProperty003
 * @tc.desc: create rect with radius width and radius height
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, RectPaintProperty003, TestSize.Level1)
{
    RectModelNG().Create();
    RectModelNG().SetRadiusWidth(RADIUS_WIDTH);
    RectModelNG().SetRadiusHeight(RADIUS_HEIGHT);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    Draw(frameNode);
}

} // namespace OHOS::Ace::NG