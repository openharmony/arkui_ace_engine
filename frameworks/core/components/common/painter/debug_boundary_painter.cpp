/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/debug_boundary_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkColorFilter.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace {
namespace {
constexpr double BOUNDARY_STROKE_WIDTH = 1.0;
// offset to show right and bottom boundary for some components when paint exceed layout and cliped
constexpr double HALF_STROKE_WIDTH_OFFSET = 0.5;
constexpr double BOUNDARY_CORNER_LENGTH = 8.0;
constexpr uint32_t BOUNDARY_COLOR = 0xFFFA2A2D;
constexpr uint32_t BOUNDARY_CORNER_COLOR = 0xFF007DFF;
constexpr uint32_t BOUNDARY_MARGIN_COLOR = 0x3FFF00AA;
}

#ifndef USE_ROSEN_DRAWING
void DebugBoundaryPainter::PaintDebugBoundary(SkCanvas* canvas, const Offset& offset, const Size& layoutSize)
{
    SkPaint skpaint;
    auto layoutRect = SkRect::MakeXYWH(offset.GetX(), offset.GetY(),
        layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET, layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET);
    skpaint.setColor(BOUNDARY_COLOR);
    skpaint.setStyle(SkPaint::Style::kStroke_Style);
    skpaint.setStrokeWidth(BOUNDARY_STROKE_WIDTH);
    canvas->drawRect(layoutRect, skpaint);
}
#else
void DebugBoundaryPainter::PaintDebugBoundary(RSCanvas* canvas, const Offset& offset,
    const Size& layoutSize)
{
    RSPen pen;
    auto layoutRect = RSRect(offset.GetX(), offset.GetY(),
        layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET + offset.GetX(),
        layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET + offset.GetY());
    pen.SetColor(BOUNDARY_COLOR);
    pen.SetWidth(BOUNDARY_STROKE_WIDTH);
    canvas->AttachPen(pen);
    canvas->DrawRect(layoutRect);
    canvas->DetachPen();
}
#endif

#ifndef USE_ROSEN_DRAWING
void DebugBoundaryPainter::PaintDebugMargin(SkCanvas* canvas, const Offset& offset,
    const Size& layoutSize, const EdgePx& margin)
{
    SkPaint skpaint;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto verticalRectHeight = layoutSize.Height() - margin.TopPx() - margin.BottomPx();
    skpaint.setColor(BOUNDARY_MARGIN_COLOR);
    skpaint.setStyle(SkPaint::Style::kFill_Style);

    auto layoutRect = SkRect::MakeXYWH(startPointX, startPointY,
        layoutSize.Width(), margin.TopPx());
    canvas->drawRect(layoutRect, skpaint);

    layoutRect = SkRect::MakeXYWH(startPointX, startPointY + layoutSize.Height() - margin.BottomPx(),
        layoutSize.Width(), margin.BottomPx());
    canvas->drawRect(layoutRect, skpaint);

    layoutRect = SkRect::MakeXYWH(startPointX, startPointY + margin.TopPx(),
        margin.LeftPx(), verticalRectHeight);
    canvas->drawRect(layoutRect, skpaint);

    layoutRect = SkRect::MakeXYWH(startPointX + layoutSize.Width() - margin.RightPx(), startPointY + margin.TopPx(),
        margin.RightPx(), verticalRectHeight);
    canvas->drawRect(layoutRect, skpaint);
}
#else
void DebugBoundaryPainter::PaintDebugMargin(RSCanvas* canvas, const Offset& offset,
    const Size& layoutSize, const EdgePx& margin)
{
    RSBrush brush;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto verticalRectHeight = layoutSize.Height() - margin.TopPx() - margin.BottomPx();
    brush.SetColor(BOUNDARY_MARGIN_COLOR);

    auto layoutRect = RSRect(startPointX, startPointY,
        layoutSize.Width() + startPointX, margin.TopPx() + startPointY);
    canvas->AttachBrush(brush);
    canvas->DrawRect(layoutRect);

    layoutRect = RSRect(startPointX, startPointY + layoutSize.Height() - margin.BottomPx(),
        layoutSize.Width() + startPointX, startPointY + layoutSize.Height());
    canvas->DrawRect(layoutRect);

    layoutRect = RSRect(startPointX, startPointY + margin.TopPx(),
        margin.LeftPx() + startPointX, verticalRectHeight + startPointY + margin.TopPx());
    canvas->DrawRect(layoutRect);

    layoutRect = RSRect(startPointX + layoutSize.Width() - margin.RightPx(),
        startPointY + margin.TopPx(), startPointX + layoutSize.Width(),
        verticalRectHeight + startPointY + margin.TopPx());
    canvas->DrawRect(layoutRect);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void DebugBoundaryPainter::PaintDebugCorner(SkCanvas* canvas, const Offset& offset, const Size& layoutSize)
{
    SkPaint skpaint;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    skpaint.setColor(BOUNDARY_CORNER_COLOR);
    skpaint.setStyle(SkPaint::Style::kStroke_Style);
    skpaint.setStrokeWidth(BOUNDARY_STROKE_WIDTH);
    canvas->drawLine(startPointX, startPointY,
        startPointX + BOUNDARY_CORNER_LENGTH, startPointY, skpaint);
    canvas->drawLine(startPointX, startPointY,
        startPointX, startPointY + BOUNDARY_CORNER_LENGTH, skpaint);
    canvas->drawLine(startPointX + layoutSize.Width() - BOUNDARY_CORNER_LENGTH, startPointY,
        startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY, skpaint);
    canvas->drawLine(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY,
        startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
        startPointY + BOUNDARY_CORNER_LENGTH, skpaint);
    canvas->drawLine(startPointX, startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET,
        startPointX + BOUNDARY_CORNER_LENGTH,
        startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET, skpaint);
    canvas->drawLine(startPointX,
        startPointY + layoutSize.Height() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET,
        startPointX, startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET, skpaint);
    canvas->drawLine(startPointX + layoutSize.Width() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET,
        startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET,
        startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
        startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET, skpaint);
    canvas->drawLine(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
        startPointY + layoutSize.Height() - BOUNDARY_CORNER_LENGTH,
        startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
        startPointY + layoutSize.Height(), skpaint);
}
#else
void DebugBoundaryPainter::PaintDebugCorner(RSCanvas* canvas, const Offset& offset,
    const Size& layoutSize)
{
    RSPen pen;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    pen.SetColor(BOUNDARY_CORNER_COLOR);
    pen.SetWidth(BOUNDARY_STROKE_WIDTH);
    canvas->AttachPen(pen);
    canvas->DrawLine(RSPoint(startPointX, startPointY),
        RSPoint(startPointX + BOUNDARY_CORNER_LENGTH, startPointY));
    canvas->DrawLine(
        RSPoint(startPointX, startPointY),
        RSPoint(startPointX, startPointY + BOUNDARY_CORNER_LENGTH));
    canvas->DrawLine(
        RSPoint(startPointX + layoutSize.Width() - BOUNDARY_CORNER_LENGTH, startPointY),
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY));
    canvas->DrawLine(
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY),
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + BOUNDARY_CORNER_LENGTH));
    canvas->DrawLine(
        RSPoint(startPointX, startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(startPointX + BOUNDARY_CORNER_LENGTH,
            startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas->DrawLine(
        RSPoint(startPointX,
            startPointY + layoutSize.Height() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(startPointX,
            startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas->DrawLine(
        RSPoint(startPointX + layoutSize.Width() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET,
            startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + layoutSize.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas->DrawLine(
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + layoutSize.Height() - BOUNDARY_CORNER_LENGTH),
        RSPoint(startPointX + layoutSize.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + layoutSize.Height()));
    canvas->DetachPen();
}
#endif
}
