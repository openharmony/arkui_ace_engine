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
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/utils/utils.h"
#define protected public
#define private public
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/line_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/line_painter.h"
#include "core/components_ng/render/shape_painter.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double START_VALUE = 10.0;
const double END_VALUE = 30.0;
const Dimension TEST { 0.0, DimensionUnit::PX };
const NG::OffsetF OFFSET_TEST { 1, 1 };
static constexpr NG::ShapePoint START_POINT = ShapePoint(10.0, 10.0);
static constexpr NG::ShapePoint END_POINT = ShapePoint(30.0, 30.0);

} // namespace

class LinePainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void LinePainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillOnce(ReturnRef(rSCanvas));
}

/**
 * @tc.name: LinePainterTestNg001
 * @tc.desc: Test cast to LinePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(LinePainterTestNg, LinePainterTestNg001, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;
    /**
     * @tc.steps1: create canvas pen and linePaintProperty object.
     */
    RSPen pen;
    NG::LinePaintProperty linePaintProperty;

    /**
     * @tc.steps2: call DrawLine and UpdateStartPoint with START_POINT.
     * @tc.steps2: UpdateEndPoint with END_POINT.
     * @tc.expected: expect SetPen return true.
     */
    linePaintProperty.UpdateStartPoint(START_POINT);
    linePaintProperty.UpdateEndPoint(END_POINT);
    CallBack(canvas);
    NG::LinePainter::DrawLine(canvas, linePaintProperty, OFFSET_TEST);
    bool result = NG::ShapePainter::SetPen(pen, linePaintProperty);
    EXPECT_TRUE(result);
    EXPECT_EQ(linePaintProperty.GetStartPointValue().first.ConvertToPx(), START_VALUE);
    EXPECT_EQ(linePaintProperty.GetEndPointValue().first.ConvertToPx(), END_VALUE);

    /**
     * @tc.steps3: call DrawLine and UpdateStrokeWidth with TEST.
     * @tc.expected: expect SetPen return false, HasStrokeWidth return true.
     */
    linePaintProperty.UpdateStrokeWidth(TEST);
    CallBack(canvas);
    NG::LinePainter::DrawLine(canvas, linePaintProperty, OFFSET_TEST);
    bool result_test = NG::ShapePainter::SetPen(pen, linePaintProperty);
    EXPECT_FALSE(result_test);
    EXPECT_TRUE(linePaintProperty.HasStrokeWidth());
    testing::Mock::AllowLeak(canvasPtr);
}
} // namespace OHOS::Ace
