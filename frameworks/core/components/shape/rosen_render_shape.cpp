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

#include "core/components/shape/rosen_render_shape.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPaint.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/utils/SkParsePath.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"
#include "frameworks/core/components/common/painter/rosen_svg_painter.h"

namespace OHOS::Ace {

Size RosenRenderShape::CalcSize()
{
    switch (shapeType_) {
        case ShapeType::RECT:
            return CreateRect();
        case ShapeType::CIRCLE:
            return CreateCircle();
        case ShapeType::ELLIPSE:
            return CreateEllipse();
        case ShapeType::LINE:
#ifndef USE_ROSEN_DRAWING
            path_.reset();
            path_.moveTo(NormalizePercentToPx(start_.first, false), NormalizePercentToPx(start_.second, true));
            path_.lineTo(NormalizePercentToPx(end_.first, false), NormalizePercentToPx(end_.second, true));
#else
            path_.Reset();
            path_.MoveTo(NormalizePercentToPx(start_.first, false), NormalizePercentToPx(start_.second, true));
            path_.LineTo(NormalizePercentToPx(end_.first, false), NormalizePercentToPx(end_.second, true));
#endif
            break;
        case ShapeType::POLYLINE:
            return CreatePolygon(false);
        case ShapeType::POLYGON:
            return CreatePolygon(true);
        case ShapeType::PATH:
            return CreatePath();
        default:
            LOGE("invalid shapeType");
            return Size();
    }
#ifndef USE_ROSEN_DRAWING
    auto skRect = path_.getBounds();
    if (width_.IsValid() && height_.IsValid()) {
        return Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    }
    return Size(skRect.right(), skRect.bottom());
#else
    auto rect = path_.GetBounds();
    if (width_.IsValid() && height_.IsValid()) {
        return Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    }
    return Size(rect.GetRight(), rect.GetBottom());
#endif
}

Size RosenRenderShape::CreateRect()
{
    if (!GetLayoutParam().GetMaxSize().IsValid()) {
        return Size();
    }
#ifndef USE_ROSEN_DRAWING
    SkRect rect =
        SkRect::MakeLTRB(0.0f, 0.0f, NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
#else
    RSRect rect =
        RSRect(0.0f, 0.0f, NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
#endif
    float topLeftRadiusX = GetFloatRadiusValue(topLeftRadius_.GetX(), topLeftRadius_.GetY(), false);
    float topLeftRadiusY = GetFloatRadiusValue(topLeftRadius_.GetY(), topLeftRadius_.GetX(), true);
    float topRightRadiusX = GetFloatRadiusValue(topRightRadius_.GetX(), topRightRadius_.GetY(), false);
    float topRightRadiusY = GetFloatRadiusValue(topRightRadius_.GetY(), topRightRadius_.GetX(), true);
    float bottomRightRadiusX = GetFloatRadiusValue(bottomRightRadius_.GetX(), bottomRightRadius_.GetY(), false);
    float bottomRightRadiusY = GetFloatRadiusValue(bottomRightRadius_.GetY(), bottomRightRadius_.GetX(), true);
    float bottomLeftRadiusX = GetFloatRadiusValue(bottomLeftRadius_.GetX(), bottomLeftRadius_.GetY(), false);
    float bottomLeftRadiusY = GetFloatRadiusValue(bottomLeftRadius_.GetY(), bottomLeftRadius_.GetX(), true);
#ifndef USE_ROSEN_DRAWING
    const SkVector fRadii[4] = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    path_.reset();
    SkRRect roundRect;
    roundRect.setRectRadii(rect, fRadii);
    path_.addRRect(roundRect);
    auto skRect = path_.getBounds();
    return Size(skRect.right(), skRect.bottom());
#else
    std::vector<RSPoint> fRadii = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    path_.Reset();
    RSRoundRect roundRect(rect, fRadii);
    path_.AddRoundRect(roundRect);
    auto drRect = path_.GetBounds();

    return Size(drRect.GetRight(), drRect.GetBottom());
#endif
}

float RosenRenderShape::GetFloatRadiusValue(const Dimension& src, const Dimension& dest, bool isVertical)
{
    if (src.Value() < 0.0 && dest.Value() > 0.0) {
        return static_cast<float>(NormalizePercentToPx(dest, isVertical));
    }
    return static_cast<float>(NormalizePercentToPx(src, isVertical));
}

Size RosenRenderShape::CreateCircle()
{
    if (!GetLayoutParam().GetMaxSize().IsValid()) {
        return Size();
    }
#ifndef USE_ROSEN_DRAWING
    path_.reset();
#else
    path_.Reset();
#endif
    double width = NormalizePercentToPx(width_, false);
    double height = NormalizePercentToPx(height_, true);
#ifndef USE_ROSEN_DRAWING
    path_.addCircle(width * 0.5, height * 0.5, std::min(width, height) * 0.5);
#else
    path_.AddCircle(width * 0.5, height * 0.5, std::min(width, height) * 0.5);
#endif
    return Size(width, height);
}

Size RosenRenderShape::CreateEllipse()
{
    if (!GetLayoutParam().GetMaxSize().IsValid()) {
        return Size();
    }
#ifndef USE_ROSEN_DRAWING
    path_.reset();
    auto width = NormalizePercentToPx(width_, false);
    auto height = NormalizePercentToPx(height_, true);
    SkRect rect = SkRect::MakeXYWH(0.0f, 0.0f, width, height);
    path_.addOval(rect);
#else
    path_.Reset();
    auto width = NormalizePercentToPx(width_, false);
    auto height = NormalizePercentToPx(height_, true);
    auto rect = RSRect(0.0f, 0.0f, width, height);
    path_.AddOval(rect);
#endif
    return Size(width, height);
}

Size RosenRenderShape::CreatePolygon(bool needClose)
{
#ifndef USE_ROSEN_DRAWING
    path_.reset();
    std::vector<SkPoint> skPoints;
    for (auto point : points_) {
        skPoints.emplace_back(
            SkPoint::Make(NormalizePercentToPx(point.first, false), NormalizePercentToPx(point.second, true)));
    }
    if (skPoints.empty()) {
        return Size();
    }
    path_.addPoly(&skPoints[0], skPoints.size(), needClose);
    auto skRect = path_.getBounds();
    if (width_.IsValid() && height_.IsValid()) {
        return Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    }
    return Size(skRect.right(), skRect.bottom());
#else
    path_.Reset();
    std::vector<RSPoint> points;
    for (auto point : points_) {
        points.emplace_back(
            RSPoint(NormalizePercentToPx(point.first, false), NormalizePercentToPx(point.second, true)));
    }
    if (points.empty()) {
        return Size();
    }
    path_.AddPoly(points, points.size(), needClose);
    auto rect = path_.GetBounds();
    if (width_.IsValid() && height_.IsValid()) {
        return Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    }
    return Size(rect.GetRight(), rect.GetBottom());
#endif
}

Size RosenRenderShape::CreatePath()
{
    if (pathCmd_.GetValue().empty()) {
        return Size();
    }
#ifndef USE_ROSEN_DRAWING
    path_.reset();
    bool ret = SkParsePath::FromSVGString(pathCmd_.GetValue().c_str(), &path_);
#else
    path_.Reset();
    bool ret = path_.BuildFromSVGString(pathCmd_.GetValue());
#endif
    if (width_.IsValid() && height_.IsValid()) {
        return Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    }
    if (!ret) {
        LOGW("path value is invalid");
        return Size();
    }
#ifndef USE_ROSEN_DRAWING
    auto skRect = path_.getBounds();
    auto right = skRect.right();
    auto bottom = skRect.bottom();
    if (NearZero(right) && NearZero(bottom)) {
        return Size();
    }
    auto lineWidth = strokeState_.GetLineWidth();
    if (NearZero(right)) {
        right = lineWidth.ConvertToPx();
    }
    if (NearZero(bottom)) {
        bottom = lineWidth.ConvertToPx();
    }
    return Size(right, bottom);
#else
    auto rect = path_.GetBounds();

    auto right = rect.GetRight();
    auto bottom = rect.GetBottom();
    if (NearZero(right) && NearZero(bottom)) {
        return Size();
    }
    auto lineWidth = strokeState_.GetLineWidth();
    if (NearZero(right)) {
        right = lineWidth.ConvertToPx();
    }
    if (NearZero(bottom)) {
        bottom = lineWidth.ConvertToPx();
    }
    return Size(right, bottom);
#endif
}

void RosenRenderShape::Paint(RenderContext& context, const Offset& offset)
{
    const auto renderContext = static_cast<RosenRenderContext*>(&context);
    auto canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    PaintOnCanvas(canvas, offset);
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderShape::PaintOnCanvas(SkCanvas* skCanvas, const Offset& offset)
{
    SkPath path = path_;
    path_.offset(offset.GetX(), offset.GetY(), &path);
    RosenSvgPainter::SetFillStyle(skCanvas, path, fillState_, UINT8_MAX, antiAlias_.second);
    DrawStroke(skCanvas, path);
}
#else
void RosenRenderShape::PaintOnCanvas(RSCanvas* canvas, const Offset& offset)
{
    RSRecordingPath path;
    path.AddPath(path_);
    path.Offset(offset.GetX(), offset.GetY());
    RosenSvgPainter::SetFillStyle(canvas, path, fillState_, UINT8_MAX, antiAlias_.second);
    DrawStroke(canvas, path);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderShape::DrawStroke(SkCanvas* skCanvas, const SkPath& path)
{
    if (strokeState_.GetColor() != Color::TRANSPARENT && GreatNotEqual(strokeState_.GetLineWidth().Value(), 0.0)) {
        SkPaint strokePaint;
        RosenSvgPainter::SetStrokeStyle(strokePaint, strokeState_, UINT8_MAX, antiAlias_.second);
        strokePaint.setStrokeWidth(NormalizePercentToPx(strokeState_.GetLineWidth(), false));
        if (!strokeState_.GetStrokeDashArray().empty()) {
            auto lineDashState = strokeState_.GetStrokeDashArray();
            SkScalar intervals[lineDashState.size()];
            for (size_t i = 0; i < lineDashState.size(); ++i) {
                intervals[i] = SkDoubleToScalar(NormalizePercentToPx(lineDashState[i], false));
            }
            SkScalar phase = SkDoubleToScalar(NormalizePercentToPx(strokeState_.GetStrokeDashOffset(), false));
            strokePaint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
        }
        skCanvas->drawPath(path, strokePaint);
    }
}
#else
void RosenRenderShape::DrawStroke(RSCanvas* canvas, const RSPath& path)
{
    if (strokeState_.GetColor() != Color::TRANSPARENT && GreatNotEqual(strokeState_.GetLineWidth().Value(), 0.0)) {
        RSPen strokePen;
        RosenSvgPainter::SetStrokeStyle(strokePen, strokeState_, UINT8_MAX, antiAlias_.second);
        strokePen.SetWidth(NormalizePercentToPx(strokeState_.GetLineWidth(), false));
        if (!strokeState_.GetStrokeDashArray().empty()) {
            auto lineDashState = strokeState_.GetStrokeDashArray();
            RSScalar intervals[lineDashState.size()];
            for (size_t i = 0; i < lineDashState.size(); ++i) {
                intervals[i] = static_cast<RSScalar>(NormalizePercentToPx(lineDashState[i], false));
            }
            RSScalar phase = static_cast<RSScalar>(NormalizePercentToPx(strokeState_.GetStrokeDashOffset(), false));
            strokePen.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals,
                lineDashState.size(), phase));
        }
        canvas->AttachPen(strokePen);
        canvas->DrawPath(path);
        canvas->DetachPen();
    }
}
#endif

} // namespace OHOS::Ace
