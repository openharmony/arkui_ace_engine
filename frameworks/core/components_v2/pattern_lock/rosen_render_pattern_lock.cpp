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
#include "core/components_v2/pattern_lock/rosen_render_pattern_lock.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/effects/SkGradientShader.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace::V2 {
void RosenRenderPatternLock::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    PaintLockLine(canvas, offset);
    for (int i = 0; i < COL_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            PaintLockCircle(canvas, offset, i + 1, j + 1);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderPatternLock::PaintLockCircle(SkCanvas* canvas, const Offset& offset, int16_t x, int16_t y)
{
    SkPaint skPaintFill;
    skPaintFill.setAntiAlias(true);
    skPaintFill.setStyle(SkPaint::Style::kFill_Style);
    skPaintFill.setColor(regularColor_.GetValue());
    Offset cellcenter = GetCircleCenterByXY(offset, x, y);
    double offsetX = cellcenter.GetX();
    double offsetY = cellcenter.GetY();
    if (CheckChoosePoint(x, y)) {
        const int16_t lastIndexFir = 1;
        int16_t lastIndexDecrease = 2 + passPointCount_;
        if (CheckChoosePointIsLastIndex(x, y, lastIndexFir)) {
            if (isMoveEventValid_) {
                skPaintFill.setColor(activeColor_.GetValue());
                canvas->drawCircle(offsetX, offsetY, NormalizeToPx(circleRadiusAnimatorToIncrease_), skPaintFill);
            } else {
                skPaintFill.setColor(selectedColor_.GetValue());
                canvas->drawCircle(offsetX, offsetY, NormalizeToPx(circleRadiusAnimatorToDecrease_), skPaintFill);
            }
        } else if (CheckChoosePointIsLastIndex(x, y, lastIndexDecrease)) {
            if (isMoveEventValid_) {
                skPaintFill.setColor(selectedColor_.GetValue());
                canvas->drawCircle(offsetX, offsetY, NormalizeToPx(circleRadiusAnimatorToDecrease_), skPaintFill);
            } else {
                skPaintFill.setColor(selectedColor_.GetValue());
                canvas->drawCircle(
                    offsetX, offsetY, NormalizeToPx(circleRadius_ * SCALE_ACTIVE_CIRCLE_RADIUS), skPaintFill);
            }
        } else {
            skPaintFill.setColor(selectedColor_.GetValue());
            canvas->drawCircle(
                offsetX, offsetY, NormalizeToPx(circleRadius_ * SCALE_ACTIVE_CIRCLE_RADIUS), skPaintFill);
        }
    } else {
        canvas->drawCircle(offsetX, offsetY, NormalizeToPx(circleRadius_), skPaintFill);
    }
}
#else
void RosenRenderPatternLock::PaintLockCircle(RSCanvas* canvas, const Offset& offset, int16_t x, int16_t y)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(regularColor_.GetValue());
    Offset cellcenter = GetCircleCenterByXY(offset, x, y);
    double offsetX = cellcenter.GetX();
    double offsetY = cellcenter.GetY();
    if (CheckChoosePoint(x, y)) {
        const int16_t lastIndexFir = 1;
        int16_t lastIndexDecrease = 2 + passPointCount_;
        if (CheckChoosePointIsLastIndex(x, y, lastIndexFir)) {
            if (isMoveEventValid_) {
                brush.SetColor(activeColor_.GetValue());
                canvas->AttachBrush(brush);
                canvas->DrawCircle(
                    RSPoint(offsetX, offsetY), NormalizeToPx(circleRadiusAnimatorToIncrease_));
            } else {
                brush.SetColor(selectedColor_.GetValue());
                canvas->AttachBrush(brush);
                canvas->DrawCircle(
                    RSPoint(offsetX, offsetY), NormalizeToPx(circleRadiusAnimatorToDecrease_));
            }
            canvas->DetachBrush();
        } else if (CheckChoosePointIsLastIndex(x, y, lastIndexDecrease)) {
            if (isMoveEventValid_) {
                brush.SetColor(selectedColor_.GetValue());
                canvas->AttachBrush(brush);
                canvas->DrawCircle(
                    RSPoint(offsetX, offsetY), NormalizeToPx(circleRadiusAnimatorToDecrease_));
            } else {
                brush.SetColor(selectedColor_.GetValue());
                canvas->AttachBrush(brush);
                canvas->DrawCircle(
                    RSPoint(offsetX, offsetY), NormalizeToPx(circleRadius_ * SCALE_ACTIVE_CIRCLE_RADIUS));
            }
            canvas->DetachBrush();
        } else {
            brush.SetColor(selectedColor_.GetValue());
            canvas->AttachBrush(brush);
            canvas->DrawCircle(
                RSPoint(offsetX, offsetY), NormalizeToPx(circleRadius_ * SCALE_ACTIVE_CIRCLE_RADIUS));
            canvas->DetachBrush();
        }
    } else {
        canvas->AttachBrush(brush);
        canvas->DrawCircle(RSPoint(offsetX, offsetY), NormalizeToPx(circleRadius_));
        canvas->DetachBrush();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderPatternLock::PaintLockLine(SkCanvas* canvas, const Offset& offset)
{
    size_t count = choosePoint_.size();
    if (count == 0) {
        return;
    }
    if (LessOrEqual(strokeWidth_.Value(), 0.0)) {
        return;
    }
    double half = 0.5;
    int realSizeInt = static_cast<int>(NormalizeToPx(sideLength_) + half);
    int offsetIntX = static_cast<int>(offset.GetX() - half);
    int offsetIntY = static_cast<int>(offset.GetY() - half);
    std::unique_ptr<SkRect> rect =
        std::make_unique<SkRect>(SkRect::MakeXYWH(offsetIntX, offsetIntY, realSizeInt, realSizeInt));
    canvas->saveLayerAlpha(rect.get(), pathColor_.GetAlpha());
    SkPaint skPaintStroke;
    skPaintStroke.setAntiAlias(true);
    skPaintStroke.setStyle(SkPaint::Style::kStroke_Style);
    skPaintStroke.setStrokeCap(SkPaint::kRound_Cap);
    skPaintStroke.setStrokeWidth(NormalizeToPx(strokeWidth_));
    Color pathColorAlpha255 = pathColor_.ChangeAlpha(MAX_ALPHA);
    skPaintStroke.setColor(pathColorAlpha255.GetValue());
    for (size_t i = 0; i < count - 1; i++) {
        Offset pointBegin = GetCircleCenterByXY(offset, choosePoint_[i].GetColumn(), choosePoint_[i].GetRow());
        Offset pointEnd = GetCircleCenterByXY(offset, choosePoint_[i + 1].GetColumn(), choosePoint_[i + 1].GetRow());
        canvas->drawLine(pointBegin.GetX(), pointBegin.GetY(), pointEnd.GetX(), pointEnd.GetY(), skPaintStroke);
    }
    if (count > 0 && isMoveEventValid_) {
        Offset pointBegin =
            GetCircleCenterByXY(offset, choosePoint_[count - 1].GetColumn(), choosePoint_[count - 1].GetRow());
        double x1 = pointBegin.GetX();
        double y1 = pointBegin.GetY();
        double x2 = offset.GetX() + cellCenter_.GetX();
        double y2 = offset.GetY() + cellCenter_.GetY();
        x2 = x2 > offset.GetX() + NormalizeToPx(sideLength_) ? offset.GetX() + NormalizeToPx(sideLength_) : x2;
        x2 = x2 < offset.GetX() ? offset.GetX() : x2;
        y2 = y2 > offset.GetY() + NormalizeToPx(sideLength_) ? offset.GetY() + NormalizeToPx(sideLength_) : y2;
        y2 = y2 < offset.GetY() ? offset.GetY() : y2;
        SkPoint points[2] = { SkPoint::Make(x1, y1), SkPoint::Make(x2, y2) };
        SkColor colors[3] = { pathColorAlpha255.GetValue(), pathColorAlpha255.GetValue(),
            pathColorAlpha255.ChangeOpacity(0.0).GetValue() };
        SkScalar pos[3] = { 0.0, GRADUAL_CHANGE_POINT, 1.0 };
        skPaintStroke.setShader(
            SkGradientShader::MakeLinear(points, colors, pos, std::size(colors), SkTileMode::kClamp));
        canvas->drawLine(x1, y1, x2, y2, skPaintStroke);
    }
    canvas->restore();
}
#else
void RosenRenderPatternLock::PaintLockLine(RSCanvas* canvas, const Offset& offset)
{
    size_t count = choosePoint_.size();
    if (count == 0) {
        return;
    }
    if (LessOrEqual(strokeWidth_.Value(), 0.0)) {
        return;
    }
    double half = 0.5;
    int realSizeInt = static_cast<int>(NormalizeToPx(sideLength_) + half);
    int offsetIntX = static_cast<int>(offset.GetX() - half);
    int offsetIntY = static_cast<int>(offset.GetY() - half);
    std::unique_ptr<RSRect> rect = std::make_unique<RSRect>(
        RSRect(offsetIntX, offsetIntY, offsetIntX + realSizeInt, offsetIntY + realSizeInt));
    RSBrush tempBrush;
    tempBrush.SetAlpha(pathColor_.GetAlpha());
    RSSaveLayerOps slo(rect.get(), &tempBrush);
    canvas->SaveLayer(slo);
    RSPen penStroke;
    penStroke.SetAntiAlias(true);
    penStroke.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    penStroke.SetWidth(NormalizeToPx(strokeWidth_));
    Color pathColorAlpha255 = pathColor_.ChangeAlpha(MAX_ALPHA);
    penStroke.SetColor(pathColorAlpha255.GetValue());
    canvas->AttachPen(penStroke);
    for (size_t i = 0; i < count - 1; i++) {
        Offset pointBegin = GetCircleCenterByXY(offset, choosePoint_[i].GetColumn(), choosePoint_[i].GetRow());
        Offset pointEnd = GetCircleCenterByXY(offset, choosePoint_[i + 1].GetColumn(), choosePoint_[i + 1].GetRow());
        canvas->DrawLine(RSPoint(pointBegin.GetX(), pointBegin.GetY()),
            RSPoint(pointEnd.GetX(), pointEnd.GetY()));
    }
    canvas->DetachPen();
    if (count > 0 && isMoveEventValid_) {
        Offset pointBegin =
            GetCircleCenterByXY(offset, choosePoint_[count - 1].GetColumn(), choosePoint_[count - 1].GetRow());
        double x1 = pointBegin.GetX();
        double y1 = pointBegin.GetY();
        double x2 = offset.GetX() + cellCenter_.GetX();
        double y2 = offset.GetY() + cellCenter_.GetY();
        x2 = x2 > offset.GetX() + NormalizeToPx(sideLength_) ? offset.GetX() + NormalizeToPx(sideLength_) : x2;
        x2 = x2 < offset.GetX() ? offset.GetX() : x2;
        y2 = y2 > offset.GetY() + NormalizeToPx(sideLength_) ? offset.GetY() + NormalizeToPx(sideLength_) : y2;
        y2 = y2 < offset.GetY() ? offset.GetY() : y2;
        std::vector<RSPoint> points = { RSPoint(x1, y1), RSPoint(x2, y2) };
        std::vector<RSColorQuad> colors = { pathColorAlpha255.GetValue(), pathColorAlpha255.GetValue(),
            pathColorAlpha255.ChangeOpacity(0.0).GetValue() };
        std::vector<RSScalar> pos = { 0.0, GRADUAL_CHANGE_POINT, 1.0 };

        penStroke.SetShaderEffect(RSShaderEffect::CreateLinearGradient(
            points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));

        canvas->AttachPen(penStroke);
        canvas->DrawLine(RSPoint(x1, y1), RSPoint(x2, y2));
        canvas->DetachPen();
    }
    canvas->Restore();
}
#endif
} // namespace OHOS::Ace::V2
