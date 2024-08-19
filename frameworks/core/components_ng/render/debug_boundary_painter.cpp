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

#include "core/components_ng/render/debug_boundary_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BOUNDARY_STROKE_WIDTH = 1.0;
// offset to show right and bottom boundary for some components when paint exceed layout and cliped
constexpr float HALF_STROKE_WIDTH_OFFSET = 0.5;
constexpr float BOUNDARY_CORNER_LENGTH = 8.0;
constexpr uint32_t BOUNDARY_COLOR = 0xFFFA2A2D;
constexpr uint32_t BOUNDARY_CORNER_COLOR = 0xFF007DFF;
constexpr uint32_t BOUNDARY_MARGIN_COLOR = 0x3FFF00AA;
} // namespace

void DebugBoundaryPainter::PaintDebugBoundary(RSCanvas& canvas, const OffsetF& offset) const
{
    // offset is not used because canvas is translated.
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(BOUNDARY_STROKE_WIDTH);
    pen.SetColor(BOUNDARY_COLOR);
    auto marginOffset = contentOffset_ - offset;
    canvas.AttachPen(pen);
    RSRect paintRect = RSRect(-marginOffset.GetX(), -marginOffset.GetY(),
        frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET - marginOffset.GetX(),
        frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET - marginOffset.GetY());
    canvas.DrawRect(paintRect);
    canvas.DetachPen();
}

void DebugBoundaryPainter::PaintDebugMargin(RSCanvas& canvas, const OffsetF& offset) const
{
    RSBrush brush;
    auto marginOffset = contentOffset_ - offset;
    auto startPointX = -marginOffset.GetX();
    auto startPointY = -marginOffset.GetY();
    auto verticalRectHeight = contentSize_.Height();
    auto marginTop = contentOffset_.GetY() - offset.GetY();
    auto marginBottom = frameMarginSize_.Height() - contentSize_.Height() - marginTop;
    auto marginLeft = contentOffset_.GetX() - offset.GetX();
    auto marginRight = frameMarginSize_.Width() - contentSize_.Width() - marginLeft;
    brush.SetColor(BOUNDARY_MARGIN_COLOR);
    canvas.AttachBrush(brush);

    RSRect layoutRect =
        RSRect(startPointX, startPointY, frameMarginSize_.Width() + startPointX, startPointY + marginTop);
    canvas.DrawRect(layoutRect);
    layoutRect = RSRect(startPointX, startPointY + frameMarginSize_.Height() - marginBottom,
        frameMarginSize_.Width() + startPointX, startPointY + frameMarginSize_.Height());
    canvas.DrawRect(layoutRect);
    layoutRect = RSRect(
        startPointX, startPointY + marginTop, startPointX + marginLeft, startPointY + marginTop + verticalRectHeight);
    canvas.DrawRect(layoutRect);
    layoutRect = RSRect(startPointX + frameMarginSize_.Width() - marginRight, startPointY + marginTop,
        startPointX + frameMarginSize_.Width(), startPointY + marginTop + verticalRectHeight);
    canvas.DrawRect(layoutRect);

    canvas.DetachBrush();
}

void DebugBoundaryPainter::PaintDebugCorner(RSCanvas& canvas, const OffsetF& offset) const
{
    RSPen pen;
    auto marginOffset = contentOffset_ - offset;
    auto startPointX = -marginOffset.GetX();
    auto startPointY = -marginOffset.GetY();
    pen.SetColor(BOUNDARY_CORNER_COLOR);
    pen.SetWidth(BOUNDARY_STROKE_WIDTH);
    canvas.AttachPen(pen);
    canvas.DrawLine(RSPoint(startPointX, startPointY), RSPoint(startPointX + BOUNDARY_CORNER_LENGTH, startPointY));
    canvas.DrawLine(RSPoint(startPointX, startPointY), RSPoint(startPointX, startPointY + BOUNDARY_CORNER_LENGTH));
    canvas.DrawLine(RSPoint(startPointX + frameMarginSize_.Width() - BOUNDARY_CORNER_LENGTH, startPointY),
        RSPoint(startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY));
    canvas.DrawLine(RSPoint(startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY),
        RSPoint(
            startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET, startPointY + BOUNDARY_CORNER_LENGTH));
    canvas.DrawLine(RSPoint(startPointX, startPointY + frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(
            startPointX + BOUNDARY_CORNER_LENGTH, startPointY + frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas.DrawLine(RSPoint(startPointX,
        startPointY + frameMarginSize_.Height() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(startPointX, startPointY + frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas.DrawLine(RSPoint(startPointX + frameMarginSize_.Width() - BOUNDARY_CORNER_LENGTH - HALF_STROKE_WIDTH_OFFSET,
        startPointY + frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET),
        RSPoint(startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET));
    canvas.DrawLine(RSPoint(startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET,
        startPointY + frameMarginSize_.Height() - BOUNDARY_CORNER_LENGTH),
        RSPoint(startPointX + frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET,
            startPointY + frameMarginSize_.Height()));
    canvas.DetachPen();
}

} // namespace OHOS::Ace::NG