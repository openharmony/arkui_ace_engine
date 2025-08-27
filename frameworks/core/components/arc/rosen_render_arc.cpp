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

#include "core/components/arc/rosen_render_arc.h"
#include "frameworks/core/pipeline/base/constants.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPaint.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace {
void RosenRenderArc::Paint(RenderContext& context, const Offset& offset)
{
    if (!IsAcrValid()) {
        LOGE("IsAcrValid is false.");
        return;
    }

    if (!IsArcShow()) {
        LOGE("IsAcrShow is false.");
        return;
    }

    auto contextPointer = AceType::DynamicCast<RosenRenderContext>(&context);
    if (contextPointer == nullptr) {
        LOGE("ContextPointer is null");
        return;
    }
    auto canvas = contextPointer->GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }

    double widthHalf = width_ / ARC_RADIUS_TO_DIAMETER;
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(color_.GetValue());
    paint.setStrokeWidth(width_);
    paint.setStrokeCap(SkPaint::kRound_Cap);

    if (!NearZero(width_)) {
        paint.setStyle(SkPaint::Style::kStroke_Style);
        if (!NearZero(shadowWidth_)) {
            paint.setMaskFilter(
                SkMaskFilter::MakeBlur(SkBlurStyle::kSolid_SkBlurStyle, static_cast<float>(shadowWidth_)));
        }
        canvas->drawArc(
            SkRect::MakeLTRB(
                offset.GetX() + widthHalf,
                offset.GetY() + widthHalf,
                offset.GetX() + arcRadiusX_ * ARC_RADIUS_TO_DIAMETER - widthHalf,
                offset.GetY() + arcRadiusY_ * ARC_RADIUS_TO_DIAMETER - widthHalf),
            startAngle_ * 180.0 / ACE_PI, sweepAngle_ * 180.0 / ACE_PI, false, paint);
    } else {
        paint.setStyle(SkPaint::Style::kFill_Style);
        canvas->drawArc(
            SkRect::MakeLTRB(
                offset.GetX(), offset.GetY(),
                offset.GetX() + arcRadiusX_ * ARC_RADIUS_TO_DIAMETER,
                offset.GetY() + arcRadiusY_ * ARC_RADIUS_TO_DIAMETER),
            startAngle_ * 180.0 / ACE_PI, sweepAngle_ * 180.0 / ACE_PI, true, paint);
    }
#else
    if (!NearZero(width_)) {
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetColor(color_.GetValue());
        pen.SetWidth(width_);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

        if (!NearZero(shadowWidth_)) {
            RSFilter filter;
            filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
                RSBlurType::SOLID, static_cast<float>(shadowWidth_)));
            pen.SetFilter(filter);
        }
        canvas->AttachPen(pen);
        canvas->DrawArc(
            RSRect(
                offset.GetX() + widthHalf, offset.GetY() + widthHalf,
                offset.GetX() + arcRadiusX_ * ARC_RADIUS_TO_DIAMETER - widthHalf,
                offset.GetY() + arcRadiusY_ * ARC_RADIUS_TO_DIAMETER - widthHalf),
            startAngle_ * 180.0 / ACE_PI, sweepAngle_ * 180.0 / ACE_PI);
        canvas->DetachPen();
    } else {
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(color_.GetValue());

        canvas->AttachBrush(brush);
        canvas->DrawPie(
            RSRect(offset.GetX(), offset.GetY(),
                offset.GetX() + arcRadiusX_ * ARC_RADIUS_TO_DIAMETER,
                offset.GetY() + arcRadiusY_ * ARC_RADIUS_TO_DIAMETER),
            startAngle_ * 180.0 / ACE_PI, sweepAngle_ * 180.0 / ACE_PI);
        canvas->DetachBrush();
    }
#endif
}
} // namespace OHOS::Ace
