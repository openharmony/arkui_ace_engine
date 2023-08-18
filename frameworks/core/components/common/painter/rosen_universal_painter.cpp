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

#include "core/components/common/painter/rosen_universal_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPaint.h"
#include "include/core/SkRRect.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace {

#ifndef USE_ROSEN_DRAWING
void RosenUniversalPainter::DrawHoverBackground(
    SkCanvas* canvas, const Rect& paintRect, uint32_t hoverBackgroundColor, double borderRadius)
#else
void RosenUniversalPainter::DrawHoverBackground(
    RSCanvas* canvas, const Rect& paintRect, uint32_t hoverBackgroundColor, double borderRadius)
#endif
{
    RRect paintRRect = RRect::MakeRRect(paintRect, borderRadius, borderRadius);
    RosenUniversalPainter::DrawRRectBackground(canvas, paintRRect, hoverBackgroundColor, 1.0);
}

#ifndef USE_ROSEN_DRAWING
void RosenUniversalPainter::DrawRRectBackground(
    SkCanvas* canvas, const RRect& paintRRect, uint32_t backgroundColor, double dipScale)
#else
void RosenUniversalPainter::DrawRRectBackground(
    RSCanvas* canvas, const RRect& paintRRect, uint32_t backgroundColor, double dipScale)
#endif
{
    if (!canvas) {
        LOGE("canvas is null.");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint skPaint;

    skPaint.setAntiAlias(true);
    skPaint.setStyle(SkPaint::Style::kFill_Style);
    skPaint.setColor(backgroundColor);

    auto paintRect = paintRRect.GetRect();
    auto corner = paintRRect.GetCorner();
    SkRect skRect = SkRect::MakeXYWH(paintRect.Left(), paintRect.Top(), paintRect.Width(), paintRect.Height());
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    fRadii[SkRRect::kUpperLeft_Corner].set(
        SkDoubleToScalar(std::max(RosenUniversalPainter::NormalizeToPx(corner.topLeftRadius.GetX(), dipScale), 0.0)),
        SkDoubleToScalar(std::max(RosenUniversalPainter::NormalizeToPx(corner.topLeftRadius.GetY(), dipScale), 0.0)));
    fRadii[SkRRect::kUpperRight_Corner].set(
        SkDoubleToScalar(std::max(RosenUniversalPainter::NormalizeToPx(corner.topRightRadius.GetX(), dipScale), 0.0)),
        SkDoubleToScalar(std::max(RosenUniversalPainter::NormalizeToPx(corner.topRightRadius.GetY(), dipScale), 0.0)));
    fRadii[SkRRect::kLowerRight_Corner].set(
        SkDoubleToScalar(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomRightRadius.GetX(), dipScale), 0.0)),
        SkDoubleToScalar(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomRightRadius.GetY(), dipScale), 0.0)));
    fRadii[SkRRect::kLowerLeft_Corner].set(
        SkDoubleToScalar(std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomLeftRadius.GetX(), dipScale), 0.0)),
        SkDoubleToScalar(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomLeftRadius.GetY(), dipScale), 0.0)));
    SkRRect skRRect;
    skRRect.setRectRadii(skRect, fRadii);
    canvas->drawRRect(skRRect, skPaint);
#else
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(backgroundColor);

    auto paintRect = paintRRect.GetRect();
    auto corner = paintRRect.GetCorner();
    RSRect rect = RSRect(paintRect.Left(), paintRect.Top(),
        paintRect.Width() + paintRect.Left(), paintRect.Height() + paintRect.Top());
    std::vector<RSPoint> fRadii;
    fRadii.push_back(RSPoint(
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.topLeftRadius.GetX(), dipScale), 0.0)),
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.topLeftRadius.GetY(), dipScale), 0.0))));
    fRadii.push_back(RSPoint(
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.topRightRadius.GetX(), dipScale), 0.0)),
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.topRightRadius.GetY(), dipScale), 0.0))));
    fRadii.push_back(RSPoint(
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomRightRadius.GetX(), dipScale), 0.0)),
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomRightRadius.GetY(), dipScale), 0.0))));
    fRadii.push_back(RSPoint(
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomLeftRadius.GetX(), dipScale), 0.0)),
        static_cast<RSScalar>(
            std::max(RosenUniversalPainter::NormalizeToPx(corner.bottomLeftRadius.GetY(), dipScale), 0.0))));
    RSRoundRect roundRect = RSRoundRect(rect, fRadii);
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(roundRect);
    canvas->DetachBrush();
#endif
}

double RosenUniversalPainter::NormalizeToPx(const Dimension& dimension, double scale)
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * scale);
    }
    return dimension.Value();
}

} // namespace OHOS::Ace
