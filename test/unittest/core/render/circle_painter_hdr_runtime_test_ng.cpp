/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define protected public
#define private public
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#undef private
#undef protected

#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/circle_painter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr float TEST_RADIUS = 8.0f;
const NG::OffsetF DRAW_OFFSET { 1.0f, 2.0f };
} // namespace

class CirclePainterHdrRuntimeTestNg : public testing::Test {
public:
    static void ExpectCanvasCalls(Testing::MockCanvas& canvas, bool expectAttachPen = true)
    {
        EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
        EXPECT_CALL(canvas, DetachBrush()).WillOnce(ReturnRef(canvas));
        if (expectAttachPen) {
            EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
        } else {
            EXPECT_CALL(canvas, AttachPen(_)).Times(0);
        }
        EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
        EXPECT_CALL(canvas, DrawCircle(_, TEST_RADIUS)).WillOnce(Return());
    }
};

/**
 * @tc.name: CirclePainterDrawCircleHDR001
 * @tc.desc: Verify DrawCircle executes HDR/BT2020 fill branches without regressing draw sequence.
 * @tc.type: FUNC
 */
HWTEST_F(CirclePainterHdrRuntimeTestNg, CirclePainterDrawCircleHDR001, TestSize.Level0)
{
    {
        Testing::MockCanvas canvas;
        NG::ShapePaintProperty paintProperty;
        paintProperty.UpdateFill(Color::FromFloat(0.8f, 0.6f, 0.4f, 1.0f, 2.0f));
        paintProperty.UpdateFillOpacity(0.5f);
        ExpectCanvasCalls(canvas);
        NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
    }

    {
        Testing::MockCanvas canvas;
        NG::ShapePaintProperty paintProperty;
        Color bt2020Color(0xFF224466);
        bt2020Color.SetColorSpace(ColorSpace::BT2020);
        paintProperty.UpdateFill(bt2020Color);
        ExpectCanvasCalls(canvas);
        NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
    }
}

/**
 * @tc.name: CirclePainterDrawCircleHDR002
 * @tc.desc: Verify DrawCircle executes stroke HDR color-space branches (HDR headroom/BT2020/DisplayP3).
 * @tc.type: FUNC
 */
HWTEST_F(CirclePainterHdrRuntimeTestNg, CirclePainterDrawCircleHDR002, TestSize.Level0)
{
    {
        Testing::MockCanvas canvas;
        NG::ShapePaintProperty paintProperty;
        paintProperty.UpdateStroke(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.2f));
        ExpectCanvasCalls(canvas);
        NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
    }

    {
        Testing::MockCanvas canvas;
        NG::ShapePaintProperty paintProperty;
        Color bt2020Color(0xFF336699);
        bt2020Color.SetColorSpace(ColorSpace::BT2020);
        paintProperty.UpdateStroke(bt2020Color);
        ExpectCanvasCalls(canvas);
        NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
    }

    {
        Testing::MockCanvas canvas;
        NG::ShapePaintProperty paintProperty;
        Color displayP3Color(0xFF556677);
        displayP3Color.SetColorSpace(ColorSpace::DISPLAY_P3);
        paintProperty.UpdateStroke(displayP3Color);
        ExpectCanvasCalls(canvas);
        NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
    }
}

/**
 * @tc.name: CirclePainterDrawCircleHDR003
 * @tc.desc: Verify zero stroke width path skips AttachPen.
 * @tc.type: FUNC
 */
HWTEST_F(CirclePainterHdrRuntimeTestNg, CirclePainterDrawCircleHDR003, TestSize.Level0)
{
    Testing::MockCanvas canvas;
    NG::ShapePaintProperty paintProperty;
    paintProperty.UpdateStrokeWidth(Dimension(0.0f, DimensionUnit::PX));
    ExpectCanvasCalls(canvas, false);
    NG::CirclePainter::DrawCircle(canvas, TEST_RADIUS, DRAW_OFFSET, paintProperty);
}
} // namespace OHOS::Ace
