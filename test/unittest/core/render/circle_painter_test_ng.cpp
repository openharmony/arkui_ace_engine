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
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "base/utils/utils.h"
#define protected public
#define private public
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/circle_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/shape_painter.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
Dimension test { 0, DimensionUnit::PX };

float radius = 1;

Testing::TestingPen pen;

const NG::OffsetF& DRAWOFFSET { 1, 1 };

NG::ShapePaintProperty shapePaintProperty;
} // namespace

class CirclePainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void CirclePainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillOnce(ReturnRef(rSCanvas));
}

/**
 * @tc.name: CirclePainterTestNg001
 * @tc.desc: Test cast to CirclePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(CirclePainterTestNg, CirclePainterTestNg_DrawCircle001, TestSize.Level1)
{
    Testing::MockCanvas* testingCanvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& testingCanvas = *testingCanvasPtr;
    /**
     * @tc.steps1: callback DrawCircle.push shapePaintProperty is null.
     * @tc.expected: expect SetPen return true.
     */
    CallBack(testingCanvas);
    NG::CirclePainter::DrawCircle(testingCanvas, radius, DRAWOFFSET, shapePaintProperty);
    bool result = NG::ShapePainter::SetPen(pen, shapePaintProperty);
    EXPECT_TRUE(result);

    /**
     * @tc.steps2: callback DrawCircle.push shapePaintProperty is not null.
     * @tc.expected: expect SetPen return false.
     */
    shapePaintProperty.UpdateStrokeWidth(test);

    CallBack(testingCanvas);
    NG::CirclePainter::DrawCircle(testingCanvas, radius, DRAWOFFSET, shapePaintProperty);
    bool result1 = NG::ShapePainter::SetPen(pen, shapePaintProperty);
    EXPECT_FALSE(result1);
    Mock::AllowLeak(testingCanvasPtr);
}
} // namespace OHOS::Ace
