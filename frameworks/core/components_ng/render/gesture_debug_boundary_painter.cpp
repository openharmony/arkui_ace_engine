/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/gesture_debug_boundary_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF_STROKE_WIDTH_OFFSET = 0.5;
} // namespace

void GestureDebugBoundaryPainter::DrawGestureDebugBoundaries(RSCanvas& canvas, const OffsetF& offset) const
{
    if (gestureMask_ == 0 || colors_.empty()) {
        return;
    }
    PaintGestureDebugBoundary(canvas, offset);
}

void GestureDebugBoundaryPainter::PaintGestureDebugBoundary(RSCanvas& canvas, const OffsetF& offset) const
{
    auto marginOffset = contentOffset_ - offset;
    RSRect paintRect = RSRect(-marginOffset.GetX() - paddingOffset_.GetX(),
        -marginOffset.GetY() - paddingOffset_.GetY(),
        frameMarginSize_.Width() - HALF_STROKE_WIDTH_OFFSET - marginOffset.GetX() - paddingOffset_.GetX(),
        frameMarginSize_.Height() - HALF_STROKE_WIDTH_OFFSET - marginOffset.GetY() - paddingOffset_.GetY());

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidthPx_);

    const auto colorCount = colors_.size();
    const float totalWidth = paintRect.GetWidth();
    const float segmentWidth = totalWidth / static_cast<float>(colorCount);
    const float startX = paintRect.GetLeft();

    for (size_t i = 0; i < colorCount; ++i) {
        canvas.Save();
        RSRect clipRect(startX + static_cast<float>(i) * segmentWidth, paintRect.GetTop(),
            startX + static_cast<float>(i + 1) * segmentWidth, paintRect.GetBottom());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
        pen.SetColor(colors_[i].GetValue());
        canvas.AttachPen(pen);
        canvas.DrawRect(paintRect);
        canvas.DetachPen();
        canvas.Restore();
    }
}

} // namespace OHOS::Ace::NG