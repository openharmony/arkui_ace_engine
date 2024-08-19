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

#include "core/components_ng/render/line_painter.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/shape_painter.h"

namespace OHOS::Ace::NG {
void LinePainter::DrawLine(RSCanvas& canvas, const LinePaintProperty& linePaintProperty, OffsetF offset)
{
    RSPen pen;
    if (!ShapePainter::SetPen(pen, linePaintProperty)) {
        return;
    }
    canvas.AttachPen(pen);
    PointF startPoint_ = PointF(linePaintProperty.GetStartPointValue().first.ConvertToPx(),
        linePaintProperty.GetStartPointValue().second.ConvertToPx());
    PointF endPoint_ = PointF(linePaintProperty.GetEndPointValue().first.ConvertToPx(),
        linePaintProperty.GetEndPointValue().second.ConvertToPx());
    canvas.DrawLine(ToRSPoint(startPoint_ + offset), ToRSPoint(endPoint_ + offset));
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG
