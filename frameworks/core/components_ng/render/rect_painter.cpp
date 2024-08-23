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

#include "core/components_ng/render/rect_painter.h"

#include "core/components_ng/render/shape_painter.h"

namespace OHOS::Ace::NG {

void RectPainter::DrawRect(RSCanvas& canvas, const RectF& rect, RectPaintProperty& rectPaintProperty)
{
    RSPen pen;
    RSBrush brush;
    if (ShapePainter::SetPen(pen, rectPaintProperty)) {
        canvas.AttachPen(pen);
    }
    ShapePainter::SetBrush(brush, rectPaintProperty);
    std::vector<RSPoint> radiusXY(4);
    if (rectPaintProperty.GetTopLeftRadius()) {
        radiusXY[0].SetX(static_cast<float>(rectPaintProperty.GetTopLeftRadiusValue().GetX().ConvertToPx()));
        radiusXY[0].SetY(static_cast<float>(rectPaintProperty.GetTopLeftRadiusValue().GetY().ConvertToPx()));
    }
    if (rectPaintProperty.GetTopRightRadius()) {
        radiusXY[1].SetX(static_cast<float>(rectPaintProperty.GetTopRightRadiusValue().GetX().ConvertToPx()));
        radiusXY[1].SetY(static_cast<float>(rectPaintProperty.GetTopRightRadiusValue().GetY().ConvertToPx()));
    }
    if (rectPaintProperty.GetBottomRightRadius()) {
        radiusXY[2].SetX(static_cast<float>(rectPaintProperty.GetBottomRightRadiusValue().GetX().ConvertToPx()));
        radiusXY[2].SetY(static_cast<float>(rectPaintProperty.GetBottomRightRadiusValue().GetY().ConvertToPx()));
    }
    if (rectPaintProperty.GetBottomLeftRadius()) {
        radiusXY[3].SetX(static_cast<float>(rectPaintProperty.GetBottomLeftRadiusValue().GetX().ConvertToPx()));
        radiusXY[3].SetY(static_cast<float>(rectPaintProperty.GetBottomLeftRadiusValue().GetY().ConvertToPx()));
    }
    // The radiusWidth and radiusHeight is the same when there is only one of them is specified.
    for (auto& radius : radiusXY) {
        if (Negative(radius.GetX()) && NonNegative(radius.GetY())) {
            radius.SetX(radius.GetY());
            continue;
        }
        if (Negative(radius.GetY()) && NonNegative(radius.GetX())) {
            radius.SetY(radius.GetX());
            continue;
        }
    }
    canvas.AttachBrush(brush);
    RSRoundRect rSRoundRect(
        RSRect(rect.GetX(), rect.GetY(), rect.Width() + rect.GetX(), rect.Height() + rect.GetY()), radiusXY);
    canvas.DrawRoundRect(rSRoundRect);
    canvas.DetachBrush();
    canvas.DetachPen();
}

} // namespace OHOS::Ace::NG