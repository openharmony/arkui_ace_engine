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

#include "core/components_ng/render/circle_painter.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/shape_painter.h"
namespace OHOS::Ace::NG {
void CirclePainter::DrawCircle(
    RSCanvas& canvas, float radius, const OffsetF& offset, const ShapePaintProperty& shapePaintProperty)
{
    RSPen pen;
    RSBrush brush;
    if (ShapePainter::SetPen(pen, shapePaintProperty)) {
        canvas.AttachPen(pen);
    }
    ShapePainter::SetBrush(brush, shapePaintProperty);
    canvas.AttachBrush(brush);
    PointF centerPoint = PointF(radius + offset.GetX(), radius + offset.GetY());
    canvas.DrawCircle(ToRSPoint(centerPoint), radius);
    canvas.DetachBrush();
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG