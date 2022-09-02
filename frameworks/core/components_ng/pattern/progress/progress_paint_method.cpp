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

#include "core/components_ng/pattern/progress/progress_paint_method.h"

#include <algorithm>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/log/log_wrapper.h"
#include "core/components/image/image_animator_component.h"
#include "core/components/progress/progress_theme.h"

namespace OHOS::Ace::NG {
void ProgressPaintMethod::PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    PointF start = PointF(offset.GetX() + strokeWidth_ / 2, offset.GetY() + strokeWidth_ / 2);
    PointF end = PointF(offset.GetX() + frameSize.Width() - strokeWidth_ / 2, offset.GetY() + strokeWidth_ / 2);
    PointF end2 = PointF(offset.GetX() + strokeWidth_ / 2 + (frameSize.Width() - strokeWidth_) * value_ / maxValue_,
        offset.GetY() + strokeWidth_ / 2);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth_);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(ToRSColor((Color::GRAY)));
    canvas.AttachPen(pen);
    if (end2 != end) {
        canvas.DrawLine(ToRSPonit(end2), ToRSPonit(end));
    }
    pen.SetColor(ToRSColor((color_)));
    canvas.AttachPen(pen);
    if (start != end2) {
        canvas.DrawLine(ToRSPonit(start), ToRSPonit(end2));
    }
}

void ProgressPaintMethod::PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 360;
    PointF centerPt = PointF(frameSize.Width() / 2, frameSize.Height() / 2) + offset;
    rosen::scalar radius = std::min(frameSize.Width() / 2, frameSize.Height() / 2) - strokeWidth_ / 2;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth_);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(ToRSColor((Color::GRAY)));
    canvas.AttachPen(pen);
    canvas.DrawCircle(ToRSPonit(centerPt), radius);
    pen.SetColor(ToRSColor((color_)));
    canvas.AttachPen(pen);
    double angle = (value_ / maxValue_) * totalDegree;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius }, 270,
        angle);
}

void ProgressPaintMethod::PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 360;
    PointF centerPt = PointF(frameSize.Width() / 2, frameSize.Height() / 2) + offset;
    rosen::scalar radius = std::min(frameSize.Width() / 2, frameSize.Height() / 2) - strokeWidth_ / 2;
    double pathDistance = 2.0 * M_PI * radius / scaleCount_;
    LOGI("PaintScaleRing: radius:%{public}lf pathDistanc:%{public}lf scaleCount_:%d, strokeWidth_:%{public}lf  "
         "scaleWidth_:%{public}lf",
        radius, pathDistance, scaleCount_, strokeWidth_, scaleWidth_);
    RSPen pen;
    Rosen::Drawing::Path path;
    double widthOfLine = std::min(scaleWidth_, pathDistance);
    path.AddRoundRect({ 0, 0, widthOfLine ,strokeWidth_}, 90, 90, rosen::PathDirection::CW_DIRECTION);
    pen.SetAntiAlias(true);
    pen.SetWidth(scaleWidth_);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetPathEffect(rosen::PathEffect::CreatePathDashEffect(path, pathDistance, 0.0f, rosen::PathDashStyle::ROTATE));
    pen.SetColor(ToRSColor((Color::GRAY)));
    canvas.AttachPen(pen);
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius }, 270,
        totalDegree);
    pen.SetColor(ToRSColor((color_)));
    canvas.AttachPen(pen);
    double angle = (value_ / maxValue_) * totalDegree;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius }, 270,
        angle);
}

} // namespace OHOS::Ace::NG