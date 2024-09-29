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

#include "core/components/common/painter/rosen_scroll_bar_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace {
namespace {

constexpr double FULL_ALPHA = 255.0;
#ifdef USE_ROSEN_DRAWING
constexpr float FLOAT_HALF = 0.5f;
#endif

} // namespace

#ifndef USE_ROSEN_DRAWING
void RosenScrollBarPainter::PaintBar(SkCanvas* canvas, const Offset& offset, const Rect& paintRect,
    const RefPtr<ScrollBar>& scrollBar, const Offset& globalOffset, int32_t alpha)
#else
void RosenScrollBarPainter::PaintBar(RSCanvas* canvas, const Offset& offset,
    const Rect& paintRect, const RefPtr<ScrollBar>& scrollBar, const Offset& globalOffset, int32_t alpha)
#endif
{
    if ((canvas != nullptr) && scrollBar && scrollBar->NeedScrollBar()) {
        if (scrollBar->GetShapeMode() == ShapeMode::RECT) {
            PaintRectBar(canvas, offset, scrollBar, alpha);
        } else {
            PaintCircleBar(canvas, globalOffset, paintRect, scrollBar);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenScrollBarPainter::PaintCircleBar(
    SkCanvas* canvas, const Offset& offset, const Rect& paintRect, const RefPtr<ScrollBar>& scrollBar)
{
    if (canvas && scrollBar->GetTrickSweepAngle() > 0.0) {
        SkPaint paint;
        paint.setBlendMode(SkBlendMode::kSrcOver);
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::Style::kStroke_Style);
        paint.setStrokeWidth(scrollBar->GetNormalWidthToPx());
        paint.setStrokeCap(SkPaint::kRound_Cap);

        auto rootSize = scrollBar->GetRootSize();
        // do not draw scrollbar when central is out of scroll viewport
        if (rootSize.Height() * SK_ScalarHalf < offset.GetY() ||
            rootSize.Height() * SK_ScalarHalf > offset.GetY() + paintRect.Height()) {
            return;
        }
        double scrollBarWidth = scrollBar->GetNormalWidthToPx();
        double diameter = rootSize.Width() - scrollBarWidth;
        SkRect arcRect =
            SkRect::MakeXYWH(scrollBarWidth * SK_ScalarHalf, scrollBarWidth * SK_ScalarHalf, diameter, diameter);
        // paint background
        double deltaAngle = scrollBar->GetBottomAngle() - scrollBar->GetTopAngle();
        paint.setColor(scrollBar->GetBackgroundColor().GetValue());
        if (scrollBar->GetPositionMode() == PositionMode::LEFT) {
            canvas->drawArc(arcRect, deltaAngle * SK_ScalarHalf - STRAIGHT_ANGLE, -deltaAngle, false, paint);
        } else {
            canvas->drawArc(arcRect, -deltaAngle * SK_ScalarHalf, deltaAngle, false, paint);
        }

        // paint foreground
        paint.setColor(scrollBar->GetForegroundColor().GetValue());
        canvas->drawArc(arcRect, scrollBar->GetTrickStartAngle(), scrollBar->GetTrickSweepAngle(), false, paint);
    }
}
#else
void RosenScrollBarPainter::PaintCircleBar(RSCanvas* canvas, const Offset& offset,
    const Rect& paintRect, const RefPtr<ScrollBar>& scrollBar)
{
    if (canvas && scrollBar->GetTrickSweepAngle() > 0.0) {
        RSPen pen;
        pen.SetBlendMode(RSBlendMode::SRC_OVER);
        pen.SetAntiAlias(true);
        pen.SetWidth(scrollBar->GetNormalWidthToPx());
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

        auto rootSize = scrollBar->GetRootSize();
        // do not draw scrollbar when central is out of scroll viewport
        if (rootSize.Height() * FLOAT_HALF < offset.GetY() ||
            rootSize.Height() * FLOAT_HALF > offset.GetY() + paintRect.Height()) {
            return;
        }
        double scrollBarWidth = scrollBar->GetNormalWidthToPx();
        double diameter = rootSize.Width() - scrollBarWidth;
        RSRect arcRect = RSRect(
            scrollBarWidth * FLOAT_HALF,
            scrollBarWidth * FLOAT_HALF,
            diameter + scrollBarWidth * FLOAT_HALF,
            diameter + scrollBarWidth * FLOAT_HALF);
        // paint background
        double deltaAngle = scrollBar->GetBottomAngle() - scrollBar->GetTopAngle();
        pen.SetColor(scrollBar->GetBackgroundColor().GetValue());
        canvas->AttachPen(pen);
        if (scrollBar->GetPositionMode() == PositionMode::LEFT) {
            canvas->DrawArc(arcRect, deltaAngle * FLOAT_HALF - STRAIGHT_ANGLE, -deltaAngle);
        } else {
            canvas->DrawArc(arcRect, -deltaAngle * FLOAT_HALF, deltaAngle);
        }
        canvas->DetachPen();

        // paint foreground
        pen.SetColor(scrollBar->GetForegroundColor().GetValue());
        canvas->AttachPen(pen);
        canvas->DrawArc(arcRect, scrollBar->GetTrickStartAngle(), scrollBar->GetTrickSweepAngle());
        canvas->DetachPen();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenScrollBarPainter::PaintRectBar(
    SkCanvas* canvas, const Offset& offset, const RefPtr<ScrollBar>& scrollBar, int32_t alpha)
{
    Rect activeRect = scrollBar->GetActiveRect();
    Rect barRect = scrollBar->GetBarRect();
    if (canvas && !NearZero(activeRect.Height()) && !NearZero(barRect.Height())) {
        SkPaint paint;
        paint.setBlendMode(SkBlendMode::kSrcOver);
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::Style::kStrokeAndFill_Style);
        paint.setStrokeCap(SkPaint::kRound_Cap);

        // paint background
        SkRect backgroundRect = SkRect::MakeLTRB(barRect.Left(), barRect.Top(), barRect.Right(), barRect.Bottom());
        paint.setColor(scrollBar->GetBackgroundColor().GetValue());
        double filletRadius = backgroundRect.width() * SK_ScalarHalf;
        canvas->drawRoundRect(backgroundRect, filletRadius, filletRadius, paint);

        // paint foreground
        paint.setColor(scrollBar->GetForegroundColor().BlendOpacity(alpha / FULL_ALPHA).GetValue());
        SkRect foregroundRect =
            SkRect::MakeLTRB(activeRect.Left(), activeRect.Top(), activeRect.Right(), activeRect.Bottom());
        canvas->drawRoundRect(foregroundRect, filletRadius, filletRadius, paint);
        RenderScrollBarBoundary(canvas, activeRect.GetOffset(), activeRect.Width(), activeRect.Height());
    }
}
#else
void RosenScrollBarPainter::PaintRectBar(
    RSCanvas* canvas, const Offset& offset, const RefPtr<ScrollBar>& scrollBar, int32_t alpha)
{
    Rect activeRect = scrollBar->GetActiveRect();
    Rect barRect = scrollBar->GetBarRect();
    if (canvas && !NearZero(activeRect.Height()) && !NearZero(barRect.Height())) {
        RSPen pen;
        pen.SetBlendMode(RSBlendMode::SRC_OVER);
        pen.SetAntiAlias(true);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        RSBrush brush;
        brush.SetBlendMode(RSBlendMode::SRC_OVER);
        brush.SetAntiAlias(true);

        // paint background
        RSRect backgroundRect = RSRect(
            barRect.Left(), barRect.Top(), barRect.Right(), barRect.Bottom());
        pen.SetColor(scrollBar->GetBackgroundColor().GetValue());
        brush.SetColor(scrollBar->GetBackgroundColor().GetValue());
        double filletRadius = backgroundRect.GetWidth() * FLOAT_HALF;
        canvas->AttachPen(pen);
        canvas->AttachBrush(brush);
        RSRoundRect backRoundRect(backgroundRect, filletRadius, filletRadius);
        canvas->DrawRoundRect(backRoundRect);
        canvas->DetachPen();
        canvas->DetachBrush();

        // paint foreground
        pen.SetColor(scrollBar->GetForegroundColor().BlendOpacity(alpha / FULL_ALPHA).GetValue());
        brush.SetColor(scrollBar->GetForegroundColor().BlendOpacity(alpha / FULL_ALPHA).GetValue());
        RSRect foregroundRect = RSRect(
            activeRect.Left(), activeRect.Top(), activeRect.Right(), activeRect.Bottom());
        RSRoundRect foreRoundRect(foregroundRect, filletRadius, filletRadius);
        canvas->AttachPen(pen);
        canvas->AttachBrush(brush);
        canvas->DrawRoundRect(foreRoundRect);
        canvas->DetachPen();
        canvas->DetachBrush();
        RenderScrollBarBoundary(canvas, activeRect.GetOffset(), activeRect.Width(), activeRect.Height());
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenScrollBarPainter::RenderScrollBarBoundary(SkCanvas* canvas, const Offset& offset, double width, double height)
#else
void RosenScrollBarPainter::RenderScrollBarBoundary(RSCanvas* canvas, const Offset& offset,
    double width, double height)
#endif
{
    if (SystemProperties::GetDebugBoundaryEnabled()) {
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }
        Size layoutSize;
        layoutSize.SetWidth(width);
        layoutSize.SetHeight(height);
        DebugBoundaryPainter::PaintDebugBoundary(canvas, offset, layoutSize);
        DebugBoundaryPainter::PaintDebugCorner(canvas, offset, layoutSize);
    }
}

} // namespace OHOS::Ace