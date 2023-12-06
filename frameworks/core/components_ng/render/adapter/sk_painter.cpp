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

#include "core/components_ng/render/adapter/sk_painter.h"

#include "include/core/SkColor.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/utils/SkParsePath.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/shape/path_paint_property.h"

namespace OHOS::Ace::NG {
void SkPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const ShapePaintProperty& shapePaintProperty)
{
#ifndef USE_ROSEN_DRAWING
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    SkPaint skPen;
    SkPaint skBrush;
    SkPath skPath;
    bool ret = SkParsePath::FromSVGString(commands.c_str(), &skPath);
    if (!ret) {
        return;
    }
    // do brush first then do pen
    SetBrush(skBrush, shapePaintProperty);
    skCanvas->drawPath(skPath, skBrush);
    if (SetPen(skPen, shapePaintProperty)) {
        skCanvas->drawPath(skPath, skPen);
    }
#else
    RSBrush brush;
    RSPen pen;
    RSRecordingPath rsPath;
    bool ret = rsPath.BuildFromSVGString(commands.c_str());
    if (!ret) {
        return;
    }
    SetBrush(brush, shapePaintProperty);
    canvas.AttachBrush(brush);
    canvas.DrawPath(rsPath);
    canvas.DetachBrush();
    if (SetPen(pen, shapePaintProperty)) {
        canvas.AttachPen(pen);
        canvas.DrawPath(rsPath);
        canvas.DetachPen();
    }
#endif
}

#ifndef USE_ROSEN_DRAWING
bool SkPainter::SetPen(SkPaint& skPaint, const ShapePaintProperty& shapePaintProperty)
{
    if (shapePaintProperty.HasStrokeWidth()) {
        // Return false will not call 'drawPath'.
        // The path will be stroked once 'drawPath' has been called even if the strokeWidth is zero.
        if (NearZero(shapePaintProperty.GetStrokeWidth()->Value())) {
            return false;
        }
        skPaint.setStrokeWidth(static_cast<SkScalar>(shapePaintProperty.GetStrokeWidthValue().ConvertToPx()));
    } else {
        skPaint.setStrokeWidth(static_cast<SkScalar>(shapePaintProperty.STROKE_WIDTH_DEFAULT.ConvertToPx()));
    }
    skPaint.setStyle(SkPaint::Style::kStroke_Style);
    if (shapePaintProperty.HasAntiAlias()) {
        skPaint.setAntiAlias(shapePaintProperty.GetAntiAliasValue());
    } else {
        skPaint.setAntiAlias(shapePaintProperty.ANTIALIAS_DEFAULT);
    }

    if (shapePaintProperty.HasStrokeLineCap()) {
        int lineCap = shapePaintProperty.GetStrokeLineCapValue();
        if (static_cast<int>(LineCapStyle::ROUND) == lineCap) {
            skPaint.setStrokeCap(SkPaint::Cap::kRound_Cap);
        } else if (static_cast<int>(LineCapStyle::SQUARE) == lineCap) {
            skPaint.setStrokeCap(SkPaint::Cap::kSquare_Cap);
        } else {
            skPaint.setStrokeCap(SkPaint::Cap::kButt_Cap);
        }
    } else {
        skPaint.setStrokeCap(SkPaint::Cap::kButt_Cap);
    }

    if (shapePaintProperty.HasStrokeLineJoin()) {
        int lineJoin = shapePaintProperty.GetStrokeLineJoinValue();
        if (static_cast<int>(LineJoinStyle::ROUND) == lineJoin) {
            skPaint.setStrokeJoin(SkPaint::Join::kRound_Join);
        } else if (static_cast<int>(LineJoinStyle::BEVEL) == lineJoin) {
            skPaint.setStrokeJoin(SkPaint::Join::kBevel_Join);
        } else {
            skPaint.setStrokeJoin(SkPaint::Join::kMiter_Join);
        }
    } else {
        skPaint.setStrokeJoin(SkPaint::Join::kMiter_Join);
    }

    Color strokeColor = Color::BLACK;
    if (shapePaintProperty.HasStroke()) {
        strokeColor = shapePaintProperty.GetStrokeValue();
    }
    double curOpacity = shapePaintProperty.STROKE_OPACITY_DEFAULT;
    if (shapePaintProperty.HasStrokeOpacity()) {
        curOpacity = shapePaintProperty.GetStrokeOpacityValue();
    }
    skPaint.setColor(strokeColor.BlendOpacity(curOpacity).GetValue());

    if (shapePaintProperty.HasStrokeDashArray()) {
        auto lineDashState = shapePaintProperty.GetStrokeDashArrayValue();
        SkScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<SkScalar>(lineDashState[i].ConvertToPx());
        }
        SkScalar phase = 0.0f;
        if (shapePaintProperty.HasStrokeDashOffset()) {
            phase = static_cast<SkScalar>(shapePaintProperty.GetStrokeDashOffsetValue().ConvertToPx());
        }
        skPaint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
    }

    if (shapePaintProperty.HasStrokeMiterLimit()) {
        skPaint.setStrokeMiter(static_cast<SkScalar>(shapePaintProperty.GetStrokeMiterLimitValue()));
    }
    return true;
}
#else
bool SkPainter::SetPen(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    if (shapePaintProperty.HasStrokeWidth()) {
        // Return false will not call 'drawPath'.
        // The path will be stroked once 'drawPath' has been called even if the strokeWidth is zero.
        if (NearZero(shapePaintProperty.GetStrokeWidth()->Value())) {
            return false;
        }
        pen.SetWidth(static_cast<Rosen::Drawing::scalar>(shapePaintProperty.GetStrokeWidthValue().ConvertToPx()));
    } else {
        pen.SetWidth(static_cast<Rosen::Drawing::scalar>(shapePaintProperty.STROKE_WIDTH_DEFAULT.ConvertToPx()));
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
        Rosen::Drawing::scalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<Rosen::Drawing::scalar>(lineDashState[i].ConvertToPx());
        }
        Rosen::Drawing::scalar phase = 0.0f;
        if (shapePaintProperty.HasStrokeDashOffset()) {
            phase = static_cast<Rosen::Drawing::scalar>(shapePaintProperty.GetStrokeDashOffsetValue().ConvertToPx());
        }
        pen.SetPathEffect(RSPathEffect::CreatDashPathEffect(intervals, lineDashState.size(), phase));
    }

    if (shapePaintProperty.HasStrokeMiterLimit()) {
        pen.SetMiterLimit(static_cast<Rosen::Drawing::scalar>(shapePaintProperty.GetStrokeMiterLimitValue()));
    }
    return true;
}
#endif

#ifndef USE_ROSEN_DRAWING
void SkPainter::SetBrush(SkPaint& skPaint, const ShapePaintProperty& shapePaintProperty)
{
    skPaint.setStyle(SkPaint::Style::kFill_Style);
    Color fillColor = Color::BLACK;
    if (shapePaintProperty.HasFill()) {
        fillColor = shapePaintProperty.GetFillValue();
    }
    double curOpacity = shapePaintProperty.FILL_OPACITY_DEFAULT;
    if (shapePaintProperty.HasFillOpacity()) {
        curOpacity = shapePaintProperty.GetFillOpacityValue();
    }
    skPaint.setColor(fillColor.BlendOpacity(curOpacity).GetValue());
    if (shapePaintProperty.HasAntiAlias()) {
        skPaint.setAntiAlias(shapePaintProperty.GetAntiAliasValue());
    } else {
        skPaint.setAntiAlias(shapePaintProperty.ANTIALIAS_DEFAULT);
    }
}
#else
void SkPainter::SetBrush(RSBrush& brush, const ShapePaintProperty& shapePaintProperty)
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
#endif

void SkPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const OffsetF& offset)
{
    SkPath skPath;
    if (!SkParsePath::FromSVGString(commands.c_str(), &skPath)) {
        LOGE("Invalid path value.");
        return;
    }

    RSPath rsPath;
    auto rsSkPath = rsPath.GetImpl<RSSkPath>();
    CHECK_NULL_VOID(rsSkPath);
    rsSkPath->SetPath(skPath);
    rsSkPath->Offset(offset.GetX(), offset.GetY());
    canvas.DrawPath(rsPath);
}

SizeF SkPainter::GetPathSize(const std::string& commands)
{
    SkPath skPath;
    if (!SkParsePath::FromSVGString(commands.c_str(), &skPath)) {
        LOGE("Invalid path value.");
        return SizeF();
    }

    auto skRect = skPath.getBounds();
    return SizeF(skRect.right(), skRect.bottom());
}
} // namespace OHOS::Ace::NG
