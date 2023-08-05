/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "rosen_render_moon_track.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

void RosenRenderMoonTrack::Paint(RenderContext& context, const Offset& offset)
{
    Size canvasSize = GetLayoutSize();
    Offset center = offset + Offset(canvasSize.Width() / 2, canvasSize.Height() / 2);
    double radius = std::min(canvasSize.Width(), canvasSize.Height()) / 2;
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(GetSelectColor().GetValue());
    paint.setStyle(SkPaint::kFill_Style);
#else
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(GetSelectColor().GetValue());
#endif
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPath path;

    SkPaint backgroundPaint;
    backgroundPaint.setStyle(SkPaint::kFill_Style);
    backgroundPaint.setAntiAlias(true);
    backgroundPaint.setColor(GetBackgroundColor().GetValue());
    canvas->drawCircle(center.GetX(), center.GetY(), radius, backgroundPaint);

    if (GetTotalRatio() <= 0.5) {
        path.moveTo(center.GetX(), center.GetY() - radius);
        path.addArc({ center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
            90, 180);
        double progressOffset = radius - radius * GetTotalRatio() / 0.5;
        path.addArc({ center.GetX() - progressOffset, center.GetY() - radius, center.GetX() + progressOffset,
                        center.GetY() + radius },
            270, -180);
        canvas->drawPath(path, paint);
    } else {
        double progressOffset = radius * (GetTotalRatio() - 0.5) / 0.5;
        path.moveTo(center.GetX(), center.GetY() - radius);
        path.addArc({ center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
            90, 180);

        path.addArc({ center.GetX() - progressOffset, center.GetY() - radius, center.GetX() + progressOffset,
                        center.GetY() + radius },
            270, 180);
        canvas->drawPath(path, paint);
    }
#else
    RSRecordingPath path;

    RSBrush backgroundBrush;
    backgroundBrush.SetAntiAlias(true);
    backgroundBrush.SetColor(GetBackgroundColor().GetValue());
    canvas->AttachBrush(backgroundBrush);
    canvas->DrawCircle(RSPoint(center.GetX(), center.GetY()), radius);
    canvas->DetachBrush();

    if (GetTotalRatio() <= 0.5) {
        path.MoveTo(center.GetX(), center.GetY() - radius);
        path.AddArc(RSRect(
            center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius),
            90, 180);
        double progressOffset = radius - radius * GetTotalRatio() / 0.5;
        path.AddArc(RSRect(center.GetX() - progressOffset,
            center.GetY() - radius, center.GetX() + progressOffset, center.GetY() + radius),
            270, -180);
        canvas->AttachBrush(brush);
        canvas->DrawPath(path);
        canvas->DetachBrush();
    } else {
        double progressOffset = radius * (GetTotalRatio() - 0.5) / 0.5;
        path.MoveTo(center.GetX(), center.GetY() - radius);
        path.AddArc(RSRect(
            center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius),
            90, 180);
        path.AddArc(RSRect(center.GetX() - progressOffset,
            center.GetY() - radius, center.GetX() + progressOffset, center.GetY() + radius),
            270, 180);
        canvas->AttachBrush(brush);
        canvas->DrawPath(path);
        canvas->DetachBrush();
    }
#endif
}

} // namespace OHOS::Ace
