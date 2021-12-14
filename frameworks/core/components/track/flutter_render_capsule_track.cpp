/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: progress capsule paint
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

#include "core/components/track/flutter_render_capsule_track.h"

#include "core/pipeline/base/scoped_canvas_state.h"

#include "flutter/lib/ui/painting/path.h"

namespace OHOS::Ace {
void FlutterRenderCapsuleTrack::DrawShape(RenderContext& context, const Offset& offset)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    Size canvasSize = GetLayoutSize();
    double capsuleHeight = canvasSize.Height() / 2.0;
    double capsuleWidth = canvasSize.Width();
    Size progressSize = Size(capsuleWidth, capsuleHeight);
    double rrectRadius = progressSize.Height() / 2.0;
    double trackHeight = canvasSize.Height() / 2.0 - rrectRadius;

    flutter::Paint paint;
    paint.paint()->setColor(GetBackgroundColor().GetValue());
    paint.paint()->setStyle(SkPaint::Style::kFill_Style);
    paint.paint()->setAntiAlias(true);
    flutter::RRect rRect;
    flutter::PaintData paintData;

    rRect.sk_rrect.setRectXY(SkRect::MakeIWH(progressSize.Width(),
                             progressSize.Height()),
                             rrectRadius,
                             rrectRadius);

    rRect.sk_rrect.offset(offset.GetX(), offset.GetY() + trackHeight);
    canvas->drawRRect(rRect, paint, paintData);
}

void FlutterRenderCapsuleTrack::DrawCapsuleProgressAnimation(RenderContext& context,
                                                             const Offset& offset)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    double offsetX = offset.GetX();
    double offsetY = offset.GetY();
    Size canvasSize = GetLayoutSize();
    double capsuleHeight = canvasSize.Height() / 2.0;
    double capsuleWidth = canvasSize.Width();
    Size progressSize = Size(capsuleWidth, capsuleHeight);

    double radius = progressSize.Height() / 2.0;
    double trackHeight = canvasSize.Height() / 2.0 - radius;
    double progressWidth = progressSize.Width()*GetTotalRatio();

    auto path = flutter::CanvasPath::Create();
    path->addArc(offsetX, offsetY + trackHeight, progressSize.Height() + offsetX,
        progressSize.Height() + offsetY + trackHeight, M_PI * 0.5, M_PI);
    if (LessNotEqual(progressWidth, radius)) {
        path->addArc(progressWidth + offsetX, offsetY + trackHeight,
            progressSize.Height() - progressWidth + offsetX,
            progressSize.Height() + offsetY + trackHeight, M_PI * 1.5, -M_PI);
    } else if (GreatNotEqual(progressWidth, progressSize.Width() - radius)) {
        path->addRect(radius + offsetX, offsetY + trackHeight,
            progressSize.Width() - radius + offsetX,
            progressSize.Height() + offsetY + trackHeight);
        path->addArc((progressSize.Width() - radius) * 2.0 - progressWidth + offsetX,
            offsetY + trackHeight,
            progressWidth + offsetX,
            progressSize.Height() + offsetY + trackHeight,
            M_PI * 1.5, M_PI);
    } else {
        path->addRect(radius + offsetX,
                      offsetY + trackHeight,
                      progressWidth + offsetX,
                      progressSize.Height() + offsetY + trackHeight);
    }

    flutter::Paint paint;
    paint.paint()->setColor(GetSelectColor().GetValue());
    paint.paint()->setStyle(SkPaint::Style::kFill_Style);
    paint.paint()->setAntiAlias(true);
    flutter::PaintData paintData;
    canvas->drawPath(path.get(), paint, paintData);
}

void FlutterRenderCapsuleTrack::Paint(RenderContext& context, const Offset& offset)
{
    DrawShape(context, offset);
    DrawCapsuleProgressAnimation(context, offset);
}
} // namespace OHOS::Ace