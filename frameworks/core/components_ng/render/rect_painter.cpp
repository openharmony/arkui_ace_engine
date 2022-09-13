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

#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

void RectPainter::DrawRect(RSCanvas& canvas, const RectF& rect, const Radius& topLeftRadius,
    const Radius& topRightRadius, const Radius& bottomLeftRadius, const Radius& bottomRightRadius)
{
    RSPen pen;
    // TODO: add suppourt in shape
    pen.SetAntiAlias(true);
    pen.SetWidth(5);
    pen.SetColor(ToRSColor(Color::BLACK));
    canvas.AttachPen(pen);

    std::vector<RSRPoint> radiusXY(4);
    radiusXY[0].SetX(static_cast<float>(topLeftRadius.GetX().ConvertToPx()));
    radiusXY[0].SetY(static_cast<float>(topLeftRadius.GetY().ConvertToPx()));
    radiusXY[1].SetX(static_cast<float>(topRightRadius.GetX().ConvertToPx()));
    radiusXY[1].SetY(static_cast<float>(topRightRadius.GetY().ConvertToPx()));
    radiusXY[2].SetX(static_cast<float>(bottomRightRadius.GetX().ConvertToPx()));
    radiusXY[2].SetY(static_cast<float>(bottomRightRadius.GetY().ConvertToPx()));
    radiusXY[3].SetX(static_cast<float>(bottomLeftRadius.GetX().ConvertToPx()));
    radiusXY[3].SetY(static_cast<float>(bottomLeftRadius.GetY().ConvertToPx()));

    RSRoundRect rSRoundRect(
        RSRRect(rect.GetX(), rect.GetY(), rect.Width() + rect.GetX(), rect.Height() + rect.GetY()), radiusXY);
    canvas.DrawRoundRect(rSRoundRect);
}

} // namespace OHOS::Ace::NG