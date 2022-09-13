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

namespace OHOS::Ace::NG {
void CirclePainter::DrawCircle(RSCanvas& canvas, float radius)
{
    RSPen pen;
    // TODO: add suppourt in shape
    pen.SetAntiAlias(true);
    pen.SetWidth(5.0);
    pen.SetColor(ToRSColor(Color::BLACK));
    canvas.AttachPen(pen);

    PointF centerPoint = PointF(radius, radius);
    canvas.DrawCircle(ToRSPonit(centerPoint), radius);
}
} // namespace OHOS::Ace::NG