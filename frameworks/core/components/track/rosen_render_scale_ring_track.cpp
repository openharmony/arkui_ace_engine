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

#include "core/components/track/rosen_render_scale_ring_track.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/effects/Sk1DPathEffect.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

void DrawScaleArc(RenderContext& context, const RenderRingInfo& trackInfo)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    SkPath path;
    path.addRRect(SkRRect::MakeRectXY(SkRect::MakeWH(trackInfo.scaleStrokeWidth, trackInfo.thickness),
        trackInfo.thickness / 2.0, trackInfo.thickness / 2.0));
    double pathDistance = 2.0 * M_PI *
                          (trackInfo.radius + (NearEqual(trackInfo.clockwise, 1.0) ? trackInfo.thickness : 0.0)) /
                          trackInfo.totalScaleNumber;
    paint.setPathEffect(
        SkPath1DPathEffect::Make(path, static_cast<SkScalar>(pathDistance), 0.0f, SkPath1DPathEffect::kRotate_Style));
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(trackInfo.thickness);
    paint.setAntiAlias(true);
    paint.setColor(trackInfo.color.GetValue());
#else
    RSPen pen;
    RSRecordingPath path;
    path.AddRoundRect(RSRect(0, 0, trackInfo.scaleStrokeWidth, trackInfo.thickness),
        trackInfo.thickness / 2.0, trackInfo.thickness / 2.0);
    double pathDistance = 2.0 * M_PI *
                          (trackInfo.radius + (NearEqual(trackInfo.clockwise, 1.0) ? trackInfo.thickness : 0.0)) /
                          trackInfo.totalScaleNumber;
    pen.SetPathEffect(RSPathEffect::CreatePathDashEffect(
        path, static_cast<RSScalar>(pathDistance), 0.0f, RSPathDashStyle::ROTATE));
    pen.SetWidth(trackInfo.thickness);
    pen.SetAntiAlias(true);
    pen.SetColor(trackInfo.color.GetValue());
#endif

    static int32_t totalDegree = 360;
    double radiusPrecision = trackInfo.thickness;
    if (trackInfo.clockwise != 1) {
        radiusPrecision = 0.0;
    }
#ifndef USE_ROSEN_DRAWING
    canvas->drawArc({ trackInfo.center.GetX() - trackInfo.radius - radiusPrecision,
                        trackInfo.center.GetY() - trackInfo.radius - radiusPrecision,
                        trackInfo.center.GetX() + trackInfo.radius + radiusPrecision,
                        trackInfo.center.GetY() + trackInfo.radius + radiusPrecision },
        180 * (trackInfo.clockwise * (trackInfo.startDegree / (totalDegree / 2.0)) - 0.5),
        360 * (trackInfo.clockwise * trackInfo.sweepDegree / totalDegree), false, paint);
#else
    canvas->AttachPen(pen);
    canvas->DrawArc(
        RSRect(trackInfo.center.GetX() - trackInfo.radius - radiusPrecision,
            trackInfo.center.GetY() - trackInfo.radius - radiusPrecision,
            trackInfo.center.GetX() + trackInfo.radius + radiusPrecision,
            trackInfo.center.GetY() + trackInfo.radius + radiusPrecision),
        180 * (trackInfo.clockwise * (trackInfo.startDegree / (totalDegree / 2.0)) - 0.5),
        360 * (trackInfo.clockwise * trackInfo.sweepDegree / totalDegree));
    canvas->DetachPen();
#endif
}
} // namespace

void RosenRenderScaleRingTrack::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    RenderRingInfo data = paintData_;
    data.center = offset + Offset(GetLayoutSize().Width() / 2.0, GetLayoutSize().Height() / 2.0);
    data.radius = (GetLayoutSize().Width() / 2.0) - data.thickness;

    if (data.totalScaleNumber == 0) {
        LOGE("Scale number error. Use default number(120)");
        data.totalScaleNumber = 120;
    }
    data.color = GetBackgroundColor();
    DrawScaleArc(context, data);

    data.color = GetCachedColor();
    data.sweepDegree = paintData_.sweepDegree * GetCachedRatio();
    DrawScaleArc(context, data);

    data.color = GetSelectColor();
    data.sweepDegree = paintData_.sweepDegree * GetTotalRatio();
    DrawScaleArc(context, data);
}

} // namespace OHOS::Ace
