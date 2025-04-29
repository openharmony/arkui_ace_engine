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

#include "base/utils/utils.h"
#define protected public
#define private public
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/polygon_painter.h"
#include "core/components_ng/render/shape_painter.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const Dimension TEST { 0.0, DimensionUnit::PX };
const std::pair<Dimension, Dimension> START_POINT = { 10.0_vp, 10.0_vp };
const std::pair<Dimension, Dimension> END_POINT = { 30.0_vp, 30.0_vp };

std::vector<ShapePoint> shape_Point;

} // namespace

class PolygonPainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void PolygonPainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillOnce(ReturnRef(rSCanvas));
}

/**
 * @tc.name: PolygonPainterTestNg001
 * @tc.desc: Test cast to PolygonPainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPainterTestNg, PolygonPainterTestNg001, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;
    /**
     * @tc.steps1: create canvas and polygonPaintProperty object.
     */
    CallBack(canvas);
    NG::PolygonPaintProperty polygonPaintProperty;

    /**
     * @tc.steps2: call DrawPolygon.
     * @tc.expected: expect HasPoints return false.
     */
    NG::PolygonPainter::DrawPolygon(canvas, polygonPaintProperty, true);
    EXPECT_FALSE(polygonPaintProperty.HasPoints());

    /**
     * @tc.steps3: call DrawPolygon and UpdatePoints with shape_Point.
     * @tc.expected: expect HasPoints return true.
     */
    polygonPaintProperty.UpdatePoints(shape_Point);
    CallBack(canvas);
    NG::PolygonPainter::DrawPolygon(canvas, polygonPaintProperty, true);
    EXPECT_TRUE(polygonPaintProperty.HasPoints());
    EXPECT_TRUE(polygonPaintProperty.GetPointsValue().empty());
    testing::Mock::AllowLeak(canvasPtr);
}

/**
 * @tc.name: PolygonPainterTestNg002
 * @tc.desc: Test cast to PolygonPainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPainterTestNg, PolygonPainterTestNg002, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;
    /**
     * @tc.steps1: create canvas and polygonPaintProperty object.
     */
    CallBack(canvas);
    NG::PolygonPaintProperty polygonPaintProperty;

    /**
     * @tc.steps2: Add START_POINT and END_POINT element to the shape_Point.
     * @tc.steps2: UpdatePoints with shape_Point and UpdateStrokeWidth with TEST.
     */
    shape_Point.push_back(START_POINT);
    shape_Point.push_back(END_POINT);
    polygonPaintProperty.UpdatePoints(shape_Point);
    polygonPaintProperty.UpdateStrokeWidth(TEST);

    /**
     * @tc.steps3: call DrawPolygon.
     * @tc.expected: expect HasStrokeWidth return true.
     */
    NG::PolygonPainter::DrawPolygon(canvas, polygonPaintProperty, true);
    EXPECT_TRUE(polygonPaintProperty.HasStrokeWidth());
    EXPECT_FALSE(polygonPaintProperty.GetPointsValue().empty());
    testing::Mock::AllowLeak(canvasPtr);
}
} // namespace OHOS::Ace
