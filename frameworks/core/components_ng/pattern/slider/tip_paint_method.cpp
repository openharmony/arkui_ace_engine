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

#include "core/components_ng/pattern/slider/tip_paint_method.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/slider/tip_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr float HALF = 0.5;
} // namespace

CanvasDrawFunction TipPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto tip = weak.Upgrade();
        if (tip) {
            tip->PaintBobble(canvas, paintWrapper);
        }
    };
}

void PaintBezier(bool isLeft, Axis axis, RSPath& path, const OffsetF& arrowCenter, const OffsetF& arrowEdge)
{
    if (isLeft) {
        path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
        } else {
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
        }
        path.LineTo(arrowEdge.GetX(), arrowEdge.GetY());
    } else {
        path.MoveTo(arrowEdge.GetX(), arrowEdge.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.LineTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        } else {
            path.LineTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        }
    }
}

void TipPaintMethod::PaintBobble(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto tipPaintProperty = DynamicCast<TipPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(tipPaintProperty);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto offset = paintWrapper->GetContentOffset();
    auto arrowHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    RSPath path;
    OffsetF arrowCenter;
    OffsetF clockwiseFirstPoint;
    OffsetF clockwiseSecondPoint;
    float circularRadius = 0.0f;
    OffsetF clockwiseThirdPoint;
    OffsetF clockwiseFourthPoint;
    if (tipPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        arrowCenter = { offset.GetX() + frameSize.Width() * HALF, offset.GetY() + frameSize.Height() };
        float bottomLineLength = frameSize.Width() - (frameSize.Height() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - bottomLineLength * HALF, arrowCenter.GetY() - arrowHeight };
        clockwiseSecondPoint = { clockwiseFirstPoint.GetX(), offset.GetY() };
        circularRadius = (clockwiseFirstPoint.GetY() - clockwiseSecondPoint.GetY()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX() + bottomLineLength, clockwiseSecondPoint.GetY() };
        clockwiseFourthPoint = { clockwiseThirdPoint.GetX(), offset.GetY() + circularRadius * 2 };
    } else {
        arrowCenter = { offset.GetX() + frameSize.Width(), offset.GetY() + frameSize.Height() * HALF };
        float bottomLineLength = frameSize.Height() - (frameSize.Width() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - arrowHeight, arrowCenter.GetY() + bottomLineLength * HALF };
        clockwiseSecondPoint = { offset.GetX(), clockwiseFirstPoint.GetY() };
        circularRadius = (clockwiseFirstPoint.GetX() - clockwiseSecondPoint.GetX()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX(), clockwiseSecondPoint.GetY() - bottomLineLength };
        clockwiseFourthPoint = { offset.GetX() + circularRadius * 2, clockwiseThirdPoint.GetY() };
    }
    path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
    PaintBezier(
        true, tipPaintProperty->GetDirection().value_or(Axis::HORIZONTAL), path, arrowCenter, clockwiseFirstPoint);
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseSecondPoint.GetX(),
        clockwiseSecondPoint.GetY());
    path.LineTo(clockwiseThirdPoint.GetX(), clockwiseThirdPoint.GetY());
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseFourthPoint.GetX(),
        clockwiseFourthPoint.GetY());
    PaintBezier(
        false, tipPaintProperty->GetDirection().value_or(Axis::HORIZONTAL), path, arrowCenter, clockwiseFourthPoint);
    RSPen pen;
    pen.SetColor(ToRSColor(tipPaintProperty->GetColor().value_or(Color::BLACK)));
    pen.SetAntiAlias(true);
    RSBrush brush;
    brush.SetColor(ToRSColor(tipPaintProperty->GetColor().value_or(Color::BLACK)));
    canvas.AttachPen(pen);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.ClipPath(path, RSClipOp::INTERSECT);
}
} // namespace OHOS::Ace::NG
