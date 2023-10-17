/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public

#include "core/components_ng/render/shape_painter.h"

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr double STROKE_OPACITY = 1.0;
constexpr double STROKE_MITER_LIMIT = 1.0;
constexpr double FILL_OPACITY = 2.0;

const Color STROKE_COLOR_RED = Color::RED;
const Color FILL_COLOR_BLUE = Color::BLUE;

const Dimension STROKE_WIDTH_5 {5.0, DimensionUnit::PX};
const Dimension STROKE_WIDTH_0 {0.0, DimensionUnit::PX};
const Dimension STROKE_DASH_0 {0.0, DimensionUnit::PX};
const Dimension STROKE_DASH_1 {1.0, DimensionUnit::PX};
const Dimension STROKE_DASH_2 {2.0, DimensionUnit::PX};
const Dimension STROKE_DASH_OFFSET {1.0, DimensionUnit::PX};
}

class ShapePainterTestNg : public testing::Test {
};

/**
 * @tc.name: ShapePainterTestNg001
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: create testPen and shapePaintProperty.
     */
    RSPen testPen;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call SetPen.
     * @tc.expected: the retrun value is true.
     */
    bool retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps3: call SetPen and UpdateStrokeWidth with STROKE_WIDTH_5.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStrokeWidth(STROKE_WIDTH_5);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps4: call SetPen and UpdateStrokeWidth with STROKE_WIDTH_0.
     * @tc.expected: the retrun value is false.
     */
    shapePaintProperty.UpdateStrokeWidth(STROKE_WIDTH_0);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_FALSE(retSetPen);
}

/**
 * @tc.name: ShapePainterTestNg002
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: create testPen and shapePaintProperty.
      */
    RSPen testPen;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call SetPen and UpdateAntiAlias with true.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateAntiAlias(true);
    bool retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps3: call SetPen and UpdateStroke with STROKE_COLOR_RED.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStroke(STROKE_COLOR_RED);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps4: call SetPen and UpdateStrokeOpacity with STROKE_OPACITY.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStrokeOpacity(STROKE_OPACITY);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps5: call SetPen and UpdateStrokeMiterLimit with STROKE_MITER_LIMIT.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStrokeMiterLimit(STROKE_MITER_LIMIT);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);
}

/**
 * @tc.name: ShapePainterTestNg003
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: create testPen and shapePaintProperty.
     */
    RSPen testPen;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call SetPen and UpdateStrokeLineCap with CapStyle.
     * @tc.expected: the retrun value is true.
     */
    for (int32_t index = 0; index < 4; index++) {
        shapePaintProperty.UpdateStrokeLineCap(index);
        bool retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
        auto strokeLineCapValue = static_cast<RSPen::CapStyle>(index);
        switch (strokeLineCapValue) {
            case RSPen::CapStyle::FLAT_CAP:
            case RSPen::CapStyle::SQUARE_CAP:
            case RSPen::CapStyle::ROUND_CAP:
                EXPECT_TRUE(retSetPen);
            break;
            default:
                EXPECT_TRUE(retSetPen);
        }
    }
}

/**
 * @tc.name: ShapePainterTestNg004
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: create testPen and shapePaintProperty.
     */
    RSPen testPen;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call SetPen and UpdateStrokeLineJoin with JoinStyle.
     * @tc.expected: the retrun value is true.
     */
    for (int32_t index = 0; index < 4; index++) {
        shapePaintProperty.UpdateStrokeLineJoin(index);
        bool retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
        auto strokeLineJoinValue = static_cast<RSPen::JoinStyle>(index);
        switch (strokeLineJoinValue) {
            case RSPen::JoinStyle::BEVEL_JOIN:
            case RSPen::JoinStyle::MITER_JOIN:
            case RSPen::JoinStyle::ROUND_JOIN:
                EXPECT_TRUE(retSetPen);
            break;
            default:
                EXPECT_TRUE(retSetPen);
        }
    }
}

/**
 * @tc.name: ShapePainterTestNg005
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: create testPen and shapePaintProperty.
     */
    RSPen testPen;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: push three dash to strokeDash.
     */
    std::vector<Ace::Dimension> strokeDash;
    strokeDash.push_back(STROKE_DASH_0);
    strokeDash.push_back(STROKE_DASH_1);
    strokeDash.push_back(STROKE_DASH_2);

    /**
     * @tc.steps3: call SetPen and UpdateStrokeMiterLimit with strokeDash.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStrokeDashArray(strokeDash);
    bool retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);

    /**
     * @tc.steps4: call SetPen and UpdateStrokeDashOffset with STROKE_DASH_OFFSET.
     * @tc.expected: the retrun value is true.
     */
    shapePaintProperty.UpdateStrokeDashOffset(STROKE_DASH_OFFSET);
    retSetPen = NG::ShapePainter::SetPen(testPen, shapePaintProperty);
    EXPECT_TRUE(retSetPen);
}

/**
 * @tc.name: ShapePainterTestNg006
 * @tc.desc: Test cast to ShapePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(ShapePainterTestNg, ShapePainterTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: create brush and  shapePaintProperty.
     */
    RSBrush brush;
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call SetBrush.
     * @tc.expected: shapePaintProperty.HasFill() and shapePaintProperty.HasFillOpacity() are false.
     */
    NG::ShapePainter::SetBrush(brush, shapePaintProperty);
    EXPECT_FALSE(shapePaintProperty.HasFill());
    EXPECT_FALSE(shapePaintProperty.HasFillOpacity());

    /**
     * @tc.steps3: UpdateFill with FILL_COLOR_BLUE and UpdateFillOpacity with FILL_OPACITY.
     */
    shapePaintProperty.UpdateFill(FILL_COLOR_BLUE);
    shapePaintProperty.UpdateFillOpacity(FILL_OPACITY);

    /**
     * @tc.steps4: call SetBrush.
     * @tc.expected: shapePaintProperty.HasFill() and shapePaintProperty.HasFillOpacity() are true.
     */
    NG::ShapePainter::SetBrush(brush, shapePaintProperty);
    EXPECT_TRUE(shapePaintProperty.HasFill());
    EXPECT_TRUE(shapePaintProperty.HasFillOpacity());
}
} // namespace OHOS::Ace
