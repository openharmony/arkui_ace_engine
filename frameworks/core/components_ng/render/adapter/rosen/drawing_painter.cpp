/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/rosen/drawing_painter.h"

namespace OHOS::Ace::NG {
void DrawingPainter::DrawPath(
    RSCanvas& canvas, const std::string& commands, const ShapePaintProperty& shapePaintProperty)
{
    RSPen pen;
    RSBrush brush;
    RSRecordingPath path;
    bool ret = path.BuildFromSVGString(commands);
    if (!ret) {
        return;
    }
    // do brush first then do pen
    SetBrush(brush, shapePaintProperty);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    if (SetPen(pen, shapePaintProperty)) {
        canvas.AttachPen(pen);
        canvas.DrawPath(path);
        canvas.DetachPen();
    }
}

bool DrawingPainter::SetPen(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    if (shapePaintProperty.HasStrokeWidth()) {
        // Return false will not call 'drawPath'.
        // The path will be stroked once 'drawPath' has been called even if the strokeWidth is zero.
        if (NearZero(shapePaintProperty.GetStrokeWidth()->Value())) {
            return false;
        }
        pen.SetWidth(static_cast<RSScalar>(shapePaintProperty.GetStrokeWidthValue().ConvertToPx()));
    } else {
        pen.SetWidth(static_cast<RSScalar>(shapePaintProperty.STROKE_WIDTH_DEFAULT.ConvertToPx()));
    }
    if (shapePaintProperty.HasAntiAlias()) {
        pen.SetAntiAlias(shapePaintProperty.GetAntiAliasValue());
    } else {
        pen.SetAntiAlias(shapePaintProperty.ANTIALIAS_DEFAULT);
    }

    if (shapePaintProperty.HasStrokeLineCap()) {
        int lineCap = shapePaintProperty.GetStrokeLineCapValue();
        if (static_cast<int>(LineCapStyle::ROUND) == lineCap) {
            pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        } else if (static_cast<int>(LineCapStyle::SQUARE) == lineCap) {
            pen.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
        } else {
            pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
        }
    } else {
        pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
    }

    if (shapePaintProperty.HasStrokeLineJoin()) {
        int lineJoin = shapePaintProperty.GetStrokeLineJoinValue();
        if (static_cast<int>(LineJoinStyle::ROUND) == lineJoin) {
            pen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
        } else if (static_cast<int>(LineJoinStyle::BEVEL) == lineJoin) {
            pen.SetJoinStyle(RSPen::JoinStyle::BEVEL_JOIN);
        } else {
            pen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
        }
    } else {
        pen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
    }

    Color strokeColor = Color::BLACK;
    if (shapePaintProperty.HasStroke()) {
        strokeColor = shapePaintProperty.GetStrokeValue();
    }
    double curOpacity = shapePaintProperty.STROKE_OPACITY_DEFAULT;
    if (shapePaintProperty.HasStrokeOpacity()) {
        curOpacity = shapePaintProperty.GetStrokeOpacityValue();
    }
    pen.SetColor(strokeColor.BlendOpacity(curOpacity).GetValue());

    if (shapePaintProperty.HasStrokeDashArray()) {
        auto lineDashState = shapePaintProperty.GetStrokeDashArrayValue();
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i].ConvertToPx());
        }
        RSScalar phase = 0.0f;
        if (shapePaintProperty.HasStrokeDashOffset()) {
            phase = static_cast<RSScalar>(shapePaintProperty.GetStrokeDashOffsetValue().ConvertToPx());
        }
        pen.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }

    if (shapePaintProperty.HasStrokeMiterLimit()) {
        pen.SetMiterLimit(static_cast<RSScalar>(shapePaintProperty.GetStrokeMiterLimitValue()));
    }
    return true;
}

void DrawingPainter::SetBrush(RSBrush& brush, const ShapePaintProperty& shapePaintProperty)
{
    Color fillColor = Color::BLACK;
    if (shapePaintProperty.HasFill()) {
        fillColor = shapePaintProperty.GetFillValue();
    }
    double curOpacity = shapePaintProperty.FILL_OPACITY_DEFAULT;
    if (shapePaintProperty.HasFillOpacity()) {
        curOpacity = shapePaintProperty.GetFillOpacityValue();
    }
    brush.SetColor(fillColor.BlendOpacity(curOpacity).GetValue());
    if (shapePaintProperty.HasAntiAlias()) {
        brush.SetAntiAlias(shapePaintProperty.GetAntiAliasValue());
    } else {
        brush.SetAntiAlias(shapePaintProperty.ANTIALIAS_DEFAULT);
    }
}

void DrawingPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const OffsetF& offset)
{
    RSRecordingPath path;
    if (!path.BuildFromSVGString(commands)) {
        LOGE("Invalid path value.");
        return;
    }

    path.Offset(offset.GetX(), offset.GetY());
    canvas.DrawPath(path);
}

SizeF DrawingPainter::GetPathSize(const std::string& commands)
{
    RSRecordingPath path;
    if (!path.BuildFromSVGString(commands)) {
        LOGE("Invalid path value.");
        return SizeF();
    }

    auto rect = path.GetBounds();
    return SizeF(rect.GetRight(), rect.GetBottom());
}
} // namespace OHOS::Ace::NG
