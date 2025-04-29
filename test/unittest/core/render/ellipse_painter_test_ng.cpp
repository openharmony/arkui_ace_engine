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

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/ellipse_painter.h"
#include "core/components_ng/render/shape_painter.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const Dimension STROKE_WIDTH { 0.0, DimensionUnit::PX };
const NG::RectF TEST_RECT { 10.0f, 20.0f, 15.0f, 15.0f };

} // namespace

class EllipsePainterTestNg : public testing::Test {
public:
    void CallBack(Testing::MockCanvas& rSCanvas);
};

void EllipsePainterTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillOnce(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillOnce(ReturnRef(rSCanvas));
}

/**
 * @tc.name: EllipsePainterTestNg001
 * @tc.desc: Test cast to EllipsePainterTestNg
 * @tc.type: FUNC
 */
HWTEST_F(EllipsePainterTestNg, EllipsePainterTestNg001, TestSize.Level1)
{
    Testing::MockCanvas* canvasPtr = new Testing::MockCanvas();
    Testing::MockCanvas& canvas = *canvasPtr;
    /**
     * @tc.steps1: create canvas and shapePaintProperty object.
     */
    CallBack(canvas);
    NG::ShapePaintProperty shapePaintProperty;

    /**
     * @tc.steps2: call DrawEllipse.
     * @tc.expected: .
     */
    NG::EllipsePainter::DrawEllipse(canvas, TEST_RECT, shapePaintProperty);
    EXPECT_FALSE(shapePaintProperty.HasStrokeWidth());

    /**
     * @tc.steps3: call DrawEllipse and UpdateStrokeWidth with STROKE_WIDTH.
     * @tc.expected: .
     */
    shapePaintProperty.UpdateStrokeWidth(STROKE_WIDTH);
    CallBack(canvas);
    NG::EllipsePainter::DrawEllipse(canvas, TEST_RECT, shapePaintProperty);
    EXPECT_TRUE(shapePaintProperty.HasStrokeWidth());
    testing::Mock::AllowLeak(canvasPtr);
}
} // namespace OHOS::Ace
