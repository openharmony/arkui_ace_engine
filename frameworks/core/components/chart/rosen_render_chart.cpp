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

#include "core/components/chart/rosen_render_chart.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkColor.h"
#include "include/core/SkPaint.h"
#include "include/effects/Sk1DPathEffect.h"
#include "include/effects/SkGradientShader.h"
#endif
#include "rosen_text/typography.h"
#include "rosen_text/typography_create.h"

#include "core/components/font/rosen_font_collection.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

#ifndef WEARABLE_PRODUCT
constexpr double EDGE_PADDING = 20.0;
constexpr double TEXT_PADDING = 10.0;
#else
constexpr double EDGE_PADDING = 2.0;
constexpr double TEXT_PADDING = 1.0;
#endif
constexpr double TICK_LENGTH = 5.0;
constexpr double RATIO_CONSTANT = 1.732;
constexpr double BARS_INTERVAL_PROPORTION = 0.3;
constexpr double BAR_INTERVAL_PROPORTION = 0.1;
constexpr double DEFAULT_AXISTICK = 10.0;
constexpr double DEFAULT_AXIS_STROKE_WIDTH = 3.0;
constexpr double BEZIER_CONSTANT = 6.0;
constexpr double DOUBLE_TEXT_PADDING = TEXT_PADDING * 2;
constexpr int32_t MIN_SDK_VERSION = 6;
constexpr float HALF = 0.5f;

} // namespace

void RosenRenderChart::Update(const RefPtr<Component>& component)
{
    RenderChart::Update(component);
}

Offset RosenRenderChart::ConvertDataToPosition(const Rect& paintRegion, const PointInfo& point)
{
    double xLength = horizontal_.max - horizontal_.min;
    double yLength = vertical_.max - vertical_.min;
    if (NearEqual(xLength, 0.0) || NearEqual(yLength, 0.0)) {
        return Offset(0, 0);
    }
    return Offset(paintRegion.GetOffset().GetX() + (point.GetX() - horizontal_.min) * paintRegion.Width() / xLength,
        paintRegion.GetOffset().GetY() + paintRegion.Height() -
            (point.GetY() - vertical_.min) * paintRegion.Height() / yLength);
}

void RosenRenderChart::Paint(RenderContext& context, const Offset& offset)
{
    if (LessOrEqual(vertical_.max, vertical_.min)) {
        vertical_.min = 0.0;
        vertical_.max = 100.0;
    }
    if (LessOrEqual(horizontal_.max, horizontal_.min)) {
        horizontal_.min = 0.0;
        horizontal_.max = 100.0;
    }
    Rect verticalPaintRegion =
        Rect(offset.GetX(), offset.GetY(), GetLayoutSize().Width() * 0.1, GetLayoutSize().Height());
    Rect horizontalPaintRegion =
        Rect(offset.GetX(), offset.GetY() + GetLayoutSize().Height() - GetLayoutSize().Height() * 0.1,
            GetLayoutSize().Width(), GetLayoutSize().Height() * 0.1);
    Rect dataRegion;
    if (!vertical_.display && !horizontal_.display && type_ == ChartType::LINE) {
        dataRegion = Rect(offset.GetX() + EDGE_PADDING, offset.GetY() + DOUBLE_TEXT_PADDING,
            GetLayoutSize().Width() - 2 * EDGE_PADDING, GetLayoutSize().Height() - 2 * DOUBLE_TEXT_PADDING);
    } else {
        PaintVerticalAxis(context, offset, verticalPaintRegion);
        PaintHorizontalAxis(context, horizontalPaintRegion);
        dataRegion = Rect(verticalPaintRegion.Width() - HALF * TICK_LENGTH,
                          GetLayoutSize().Height() - vertical_.tickNumber * tickOffset_ -
                              horizontalPaintRegion.Height() + HALF * TICK_LENGTH,
                          horizontal_.tickNumber * tickHorizontalOffset_, vertical_.tickNumber * tickOffset_);
    }
    if (!dataRegion.IsValid()) {
        LOGW("chart paint data region is not valid height:%{public}lf, width:%{public}lf. do not paint data",
            dataRegion.Height(), dataRegion.Width());
        return;
    }
    // We Do not clip here(compare with FlutterRenderChart).
    // Cliping here may cause Axis not display when horizontal_.display = true or vertical_.display = true
    paintWidth_ = dataRegion.GetSize().Width();
    PaintDatas(context, dataRegion);
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintStylePoints(SkCanvas* canvas, const Rect& paintRegion, const MainChart& chartData)
{
    SkPaint paint;
    paint.setAntiAlias(true);

    for (const auto& points : chartData.GetData()) {
        const PointInfo& point = points.GetPointInfo();
        if (point.GetDisplay()) {
            PaintPoint(canvas, ConvertDataToPosition(paintRegion, point), paint, point);
        }
    }
    PointInfo headPoint = chartData.GetHeadPoint();
    if (headPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, headPoint), paint, headPoint);
    }
    PointInfo topPoint = chartData.GetTopPoint();
    if (topPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, topPoint), paint, topPoint);
    }
    PointInfo bottomPoint = chartData.GetBottomPoint();
    if (bottomPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, bottomPoint), paint, bottomPoint);
    }
}
#else
void RosenRenderChart::PaintStylePoints(RSCanvas* canvas, const Rect& paintRegion, const MainChart& chartData)
{
    RSPen pen;
    RSBrush brush;
    pen.SetAntiAlias(true);
    brush.SetAntiAlias(true);

    for (const auto& points : chartData.GetData()) {
        const PointInfo& point = points.GetPointInfo();
        if (point.GetDisplay()) {
            PaintPoint(canvas, ConvertDataToPosition(paintRegion, point), pen, brush, point);
        }
    }
    PointInfo headPoint = chartData.GetHeadPoint();
    if (headPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, headPoint), pen, brush, headPoint);
    }
    PointInfo topPoint = chartData.GetTopPoint();
    if (topPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, topPoint), pen, brush, topPoint);
    }
    PointInfo bottomPoint = chartData.GetBottomPoint();
    if (bottomPoint.GetDisplay()) {
        PaintPoint(canvas, ConvertDataToPosition(paintRegion, bottomPoint), pen, brush, bottomPoint);
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintText(SkCanvas* canvas, const Rect& paintRegion, const MainChart& chartData)
#else
void RosenRenderChart::PaintText(RSCanvas* canvas, const Rect& paintRegion, const MainChart& chartData)
#endif
{
    if (chartData.GetData().empty()) {
        return;
    }

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("PaintText: fontCollection is null");
        return;
    }
    Rosen::TypographyStyle style;
    Rosen::TextStyle txtStyle;
    txtStyle.fontSize = chartData.GetTextSize();
    txtStyle.fontFamilies = chartData.GetFontFamily();
    txtStyle.fontWeight = Rosen::FontWeight::W400;
    std::unique_ptr<Rosen::TypographyCreate> builder;
    double paragraphSize = paintRegion.Width() / chartData.GetData().size();
    style.maxLines = 1;
    for (const auto& point : chartData.GetData()) {
        const TextInfo& text = point.GetTextInfo();
        const PointInfo& pointInfo = point.GetPointInfo();
        Offset pointPosition = ConvertDataToPosition(paintRegion, pointInfo);
        txtStyle.color = text.GetColor().GetValue();
        builder = Rosen::TypographyCreate::Create(style, fontCollection);
        builder->PushStyle(txtStyle);
        builder->AppendText(StringUtils::Str8ToStr16(text.GetTextValue()));
        auto paragraph = builder->CreateTypography();
        paragraph->Layout(paragraphSize);
        Size textSize = Size(paragraph->GetMinIntrinsicWidth(), paragraph->GetHeight());
        if (text.GetPlacement() == Placement::TOP) {
            paragraph->Paint(canvas, pointPosition.GetX() - textSize.Width() / 2,
                pointPosition.GetY() - textSize.Height() - TEXT_PADDING);
        } else if (text.GetPlacement() == Placement::BOTTOM) {
            paragraph->Paint(canvas, pointPosition.GetX() - textSize.Width() / 2,
                pointPosition.GetY() + TEXT_PADDING);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::SetEdgeStyle(const PointInfo& point, SkPaint& paint) const
{
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(NormalizeToPx(point.GetPointStrokeWidth()));
    paint.setColor(point.GetStrokeColor().GetValue());
}
#else
void RosenRenderChart::SetEdgeStyle(const PointInfo& point, RSPen& pen) const
{
    pen.SetWidth(NormalizeToPx(point.GetPointStrokeWidth()));
    pen.SetColor(point.GetStrokeColor().GetValue());
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintPoint(SkCanvas* canvas, const Offset& offset, SkPaint paint, const PointInfo& point)
{
    paint.setColor(point.GetFillColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    double pointSize = NormalizeToPx(point.GetPointSize());
    double halfThickness = NormalizeToPx(point.GetPointStrokeWidth()) / 2;
    double innerRadius = pointSize / 2 - halfThickness;
    // first fill point color, then draw edge of point.
    switch (point.GetPointShape()) {
        case PointShape::CIRCLE: {
            canvas->drawCircle(offset.GetX(), offset.GetY(), innerRadius, paint);
            SetEdgeStyle(point, paint);
            canvas->drawCircle(offset.GetX(), offset.GetY(), pointSize / 2, paint);
            break;
        }
        case PointShape::SQUARE: {
            canvas->drawRect(SkRect::MakeLTRB(offset.GetX() - innerRadius, offset.GetY() - innerRadius,
                                              offset.GetX() + innerRadius, offset.GetY() + innerRadius),
                paint);
            SetEdgeStyle(point, paint);
            canvas->drawRect(SkRect::MakeLTRB(offset.GetX() - pointSize / 2, offset.GetY() - pointSize / 2,
                                              offset.GetX() + pointSize / 2, offset.GetY() + pointSize / 2),
                paint);
            break;
        }
        case PointShape::TRIANGLE: {
            SkPath path;
            path.moveTo(offset.GetX(), offset.GetY() - innerRadius);
            path.lineTo(offset.GetX() - RATIO_CONSTANT * innerRadius / 2, offset.GetY() + innerRadius / 2);
            path.lineTo(offset.GetX() + RATIO_CONSTANT * innerRadius / 2, offset.GetY() + innerRadius / 2);
            path.close();
            canvas->drawPath(path, paint);
            path.reset();
            path.moveTo(offset.GetX(), offset.GetY() - pointSize / 2);
            path.lineTo(offset.GetX() - RATIO_CONSTANT * pointSize / 4, offset.GetY() + pointSize / 4);
            path.lineTo(offset.GetX() + RATIO_CONSTANT * pointSize / 4, offset.GetY() + pointSize / 4);
            path.close();
            SetEdgeStyle(point, paint);
            canvas->drawPath(path, paint);
            break;
        }
        default: {
            canvas->drawCircle(offset.GetX(), offset.GetY(), innerRadius, paint);
            SetEdgeStyle(point, paint);
            canvas->drawCircle(offset.GetX(), offset.GetY(), pointSize / 2, paint);
            break;
        }
    }
}
#else
void RosenRenderChart::PaintPoint(
    RSCanvas* canvas, const Offset& offset, RSPen pen, RSBrush brush, const PointInfo& point)
{
    pen.SetColor(point.GetFillColor().GetValue());
    brush.SetColor(point.GetFillColor().GetValue());

    double pointSize = NormalizeToPx(point.GetPointSize());
    double halfThickness = NormalizeToPx(point.GetPointStrokeWidth()) / 2;
    double innerRadius = pointSize / 2 - halfThickness;
    // first fill point color, then draw edge of point.
    switch (point.GetPointShape()) {
        case PointShape::CIRCLE: {
            canvas->AttachBrush(brush);
            canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), innerRadius);
            canvas->DetachBrush();
            SetEdgeStyle(point, pen);
            canvas->AttachPen(pen);
            canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), pointSize / 2);
            canvas->DetachPen();
            break;
        }
        case PointShape::SQUARE: {
            canvas->AttachBrush(brush);
            canvas->DrawRect(RSRect(offset.GetX() - innerRadius, offset.GetY() - innerRadius,
                offset.GetX() + innerRadius, offset.GetY() + innerRadius));
            canvas->DetachBrush();
            SetEdgeStyle(point, pen);
            canvas->AttachPen(pen);
            canvas->DrawRect(RSRect(offset.GetX() - pointSize / 2, offset.GetY() - pointSize / 2,
                offset.GetX() + pointSize / 2, offset.GetY() + pointSize / 2));
            canvas->DetachPen();
            break;
        }
        case PointShape::TRIANGLE: {
            RSRecordingPath path;
            path.MoveTo(offset.GetX(), offset.GetY() - innerRadius);
            path.LineTo(offset.GetX() - RATIO_CONSTANT * innerRadius / 2, offset.GetY() + innerRadius / 2);
            path.LineTo(offset.GetX() + RATIO_CONSTANT * innerRadius / 2, offset.GetY() + innerRadius / 2);
            path.Close();
            canvas->AttachBrush(brush);
            canvas->DrawPath(path);
            canvas->DetachBrush();
            path.Reset();
            path.MoveTo(offset.GetX(), offset.GetY() - pointSize / 2);
            path.LineTo(offset.GetX() - RATIO_CONSTANT * pointSize / 4, offset.GetY() + pointSize / 4);
            path.LineTo(offset.GetX() + RATIO_CONSTANT * pointSize / 4, offset.GetY() + pointSize / 4);
            path.Close();
            SetEdgeStyle(point, pen);
            canvas->AttachPen(pen);
            canvas->DrawPath(path);
            canvas->DetachPen();
            break;
        }
        default: {
            canvas->AttachBrush(brush);
            canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), innerRadius);
            canvas->DetachBrush();
            SetEdgeStyle(point, pen);
            canvas->AttachPen(pen);
            canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), pointSize / 2);
            canvas->DetachPen();
            break;
        }
    }
}
#endif

void RosenRenderChart::PaintDatas(RenderContext& context, const Rect& paintRect)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    if (NearEqual(paintRect.Width(), 0.0) || NearEqual(paintRect.Height(), 0.0)) {
        LOGE("data paint region width:%{public}lf height:%{public}lf", paintRect.Width(), paintRect.Height());
        return;
    }
    if (type_ == ChartType::LINE) {
        PaintLinearGraph(canvas, paintRect);
    } else {
#ifndef USE_ROSEN_DRAWING
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::Style::kStrokeAndFill_Style);
#else
        RSPen pen;
        RSBrush brush;
        pen.SetAntiAlias(true);
        brush.SetAntiAlias(true);
#endif

        const int32_t barGroupNumber = static_cast<int32_t>(mainCharts_.size());
        auto barsAreaNumber = horizontal_.tickNumber;
        for (int32_t barGroupIndex = 0; barGroupIndex < barGroupNumber; ++barGroupIndex) {
            auto barGroup = mainCharts_[barGroupIndex];
#ifndef USE_ROSEN_DRAWING
            paint.setColor(barGroup.GetFillColor().GetValue());
            PaintBar(canvas, paint, barGroup.GetData(), paintRect, barGroupNumber, barsAreaNumber, barGroupIndex);
#else
            pen.SetColor(barGroup.GetFillColor().GetValue());
            brush.SetColor(barGroup.GetFillColor().GetValue());
            PaintBar(canvas, pen, brush, barGroup.GetData(), paintRect, barGroupNumber, barsAreaNumber, barGroupIndex);
#endif
        }
    }
}

void RosenRenderChart::UpdateLineGradientPoint(
    const std::vector<LineInfo>& pointInfo, const MainChart& line, const Rect& paintRect)
{
    if (line.GetHeadPointIndex() > 0 && line.GetErasePointNumber() > 0) {
        startGradientIndex_ = static_cast<size_t>(line.GetHeadPointIndex() + line.GetErasePointNumber() - 1);
        endGradientIndex_ = startGradientIndex_ + 1;
        if (static_cast<size_t>(startGradientIndex_) >= pointInfo.size()) {
            startGradientIndex_ = pointInfo.size() - 1;
        }
        if (static_cast<size_t>(endGradientIndex_) >= pointInfo.size()) {
            endGradientIndex_ = pointInfo.size() - 1;
        }
        startGradientPoint_ = ConvertDataToPosition(paintRect, pointInfo[startGradientIndex_].GetPointInfo());
        endGradientPoint_ = ConvertDataToPosition(paintRect, pointInfo[endGradientIndex_].GetPointInfo());
    } else {
        startGradientPoint_ = Offset(0.0, 0.0);
        endGradientPoint_ = Offset(0.0, 0.0);
        gradientOfLine_ = false;
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintLinearGraph(SkCanvas* canvas, const Rect& paintRect)
#else
void RosenRenderChart::PaintLinearGraph(RSCanvas* canvas, const Rect& paintRect)
#endif
{
    for (const auto& line : mainCharts_) {
        const auto& pointInfo = line.GetData();
        if (pointInfo.empty()) {
            // there is no data in current data set, and skip this line
            continue;
        }
        auto previousSegment = pointInfo[0].GetSegmentInfo();
        auto previousPoint = pointInfo[0].GetPointInfo();
        Offset previousPosition = ConvertDataToPosition(paintRect, previousPoint);
        startOffset_ = previousPosition;
#ifndef USE_ROSEN_DRAWING
        SkPath edgePath;
        SkPath gradientPath;
        edgePath.moveTo(previousPosition.GetX(), previousPosition.GetY());
        gradientPath.moveTo(previousPosition.GetX(), paintRect.Bottom());
        gradientPath.lineTo(previousPosition.GetX(), previousPosition.GetY());
#else
        RSRecordingPath edgePath;
        RSRecordingPath gradientPath;
        edgePath.MoveTo(previousPosition.GetX(), previousPosition.GetY());
        gradientPath.MoveTo(previousPosition.GetX(), paintRect.Bottom());
        gradientPath.LineTo(previousPosition.GetX(), previousPosition.GetY());
#endif

        UpdateLineGradientPoint(pointInfo, line, paintRect);

        for (size_t index = 1; index < pointInfo.size(); index++) {
            const auto& currentPoint = pointInfo[index].GetPointInfo();
            Offset currentPosition = ConvertDataToPosition(paintRect, currentPoint);
            if (line.GetSmoothFlag()) {
                bool isEnd = previousSegment != pointInfo[index].GetSegmentInfo();
                AddCubicPath(gradientPath, paintRect, line.GetData(), index, isEnd);
                AddCubicPath(edgePath, paintRect, line.GetData(), index, isEnd);
            } else {
#ifndef USE_ROSEN_DRAWING
                gradientPath.lineTo(currentPosition.GetX(), currentPosition.GetY());
                edgePath.lineTo(currentPosition.GetX(), currentPosition.GetY());
#else
                gradientPath.LineTo(currentPosition.GetX(), currentPosition.GetY());
                edgePath.LineTo(currentPosition.GetX(), currentPosition.GetY());
#endif
            }
            wholeLineGradient_ = line.GetWholeLineGradient();
            if (wholeLineGradient_) {
                targetColor_ = line.GetTargetColor();
            }
            int32_t i = static_cast<int32_t>(index);
            if ((line.GetHeadPointIndex() > 0) && (i > line.GetHeadPointIndex()) &&
                (i <= line.GetHeadPointIndex() + line.GetErasePointNumber())) {
#ifndef USE_ROSEN_DRAWING
                gradientPath.reset();
                if (i < line.GetHeadPointIndex() + line.GetErasePointNumber()) {
                    edgePath.reset();
                    edgePath.moveTo(currentPosition.GetX(), currentPosition.GetY());
                } else {
                    edgePath.lineTo(currentPosition.GetX(), currentPosition.GetY());
                    gradientPath.moveTo(currentPosition.GetX(), paintRect.Bottom());
                    gradientPath.lineTo(currentPosition.GetX(), currentPosition.GetY());
                    gradientOfLine_ = true;
                }
#else
                gradientPath.Reset();
                if (i < line.GetHeadPointIndex() + line.GetErasePointNumber()) {
                    edgePath.Reset();
                    edgePath.MoveTo(currentPosition.GetX(), currentPosition.GetY());
                } else {
                    edgePath.LineTo(currentPosition.GetX(), currentPosition.GetY());
                    gradientPath.MoveTo(currentPosition.GetX(), paintRect.Bottom());
                    gradientPath.LineTo(currentPosition.GetX(), currentPosition.GetY());
                    gradientOfLine_ = true;
                }
#endif
                previousSegment = pointInfo[index].GetSegmentInfo();
                previousPoint = currentPoint;
                previousPosition = currentPosition;
                continue;
            }
            if (previousSegment != pointInfo[index].GetSegmentInfo() ||
                (line.GetHeadPointIndex() > 0 && line.GetHeadPointIndex() == i)) {
#ifndef USE_ROSEN_DRAWING
                gradientPath.lineTo(currentPosition.GetX(), paintRect.Bottom());
                gradientPath.close();
                if (line.GetGradient()) {
                    PaintLineGradient(canvas, gradientPath, paintRect, line.GetFillColor(), line.GetTopPoint());
                }
                PaintLineEdge(canvas, edgePath, previousSegment, line.GetLineWidth(), false);
                // print gradient
                gradientPath.reset();
                edgePath.reset();
                previousSegment = pointInfo[index].GetSegmentInfo();
                previousPoint = currentPoint;
                previousPosition = currentPosition;
                edgePath.moveTo(previousPosition.GetX(), previousPosition.GetY());
                gradientPath.moveTo(previousPosition.GetX(), paintRect.Bottom());
                gradientPath.lineTo(previousPosition.GetX(), previousPosition.GetY());
#else
                gradientPath.LineTo(currentPosition.GetX(), paintRect.Bottom());
                gradientPath.Close();
                if (line.GetGradient()) {
                    PaintLineGradient(canvas, gradientPath, paintRect, line.GetFillColor(), line.GetTopPoint());
                }
                PaintLineEdge(canvas, edgePath, previousSegment, line.GetLineWidth(), false);
                // print gradient
                gradientPath.Reset();
                edgePath.Reset();
                previousSegment = pointInfo[index].GetSegmentInfo();
                previousPoint = currentPoint;
                previousPosition = currentPosition;
                edgePath.MoveTo(previousPosition.GetX(), previousPosition.GetY());
                gradientPath.MoveTo(previousPosition.GetX(), paintRect.Bottom());
                gradientPath.LineTo(previousPosition.GetX(), previousPosition.GetY());
#endif
            } else {
                previousSegment = pointInfo[index].GetSegmentInfo();
                previousPoint = currentPoint;
                previousPosition = currentPosition;
            }
        }
#ifndef USE_ROSEN_DRAWING
        gradientPath.lineTo(previousPosition.GetX(), paintRect.Bottom());
        gradientPath.close();
#else
        gradientPath.LineTo(previousPosition.GetX(), paintRect.Bottom());
        gradientPath.Close();
#endif
        if (line.GetGradient()) {
            PaintLineGradient(canvas, gradientPath, paintRect, line.GetFillColor(), line.GetTopPoint());
        }
        PaintLineEdge(canvas, edgePath, previousSegment, line.GetLineWidth(), true);
        PaintStylePoints(canvas, paintRect, line);
        PaintText(canvas, paintRect, line);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintLineEdge(
    SkCanvas* canvas, SkPath& path, const SegmentInfo segmentInfo, double thickness, bool drawGradient)
{
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(segmentInfo.GetSegmentColor().GetValue());
    if (segmentInfo.GetLineType() == LineType::DASHED) {
        SkPath subPath;
        subPath.addRRect(
            SkRRect::MakeRectXY(SkRect::MakeXYWH(0.0, -0.5 * thickness, segmentInfo.GetSolidWidth(), thickness),
                0.5 * thickness, 0.5 * thickness));
        paint.setPathEffect(SkPath1DPathEffect::Make(subPath, segmentInfo.GetSpaceWidth() +
            segmentInfo.GetSolidWidth(), 5.0f, SkPath1DPathEffect::kMorph_Style));
    } else {
        paint.setStrokeWidth(thickness);
    }
    if (wholeLineGradient_) {
        double end = startGradientPoint_.GetX();
        if (NearZero(end)) {
            end = startOffset_.GetX() + paintWidth_;
        }
        SkPoint points[2] = { SkPoint::Make(startOffset_.GetX(), 0.0f), SkPoint::Make(end, 0.0f) };
        SkColor colors[2] = { segmentInfo.GetSegmentColor().GetValue(), targetColor_.GetValue() };
        paint.setShader(SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr));
    }
    if (gradientOfLine_ && drawGradient) {
        SkPoint points[2] = { SkPoint::Make(startGradientPoint_.GetX(), 0.0f),
            SkPoint::Make(endGradientPoint_.GetX(), 0.0f) };
        SkColor colors[2] = { segmentInfo.GetSegmentColor().ChangeAlpha(0).GetValue(),
            segmentInfo.GetSegmentColor().GetValue() };
        paint.setShader(SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr));
    }
    paint.setStyle(SkPaint::Style::kStroke_Style);
    canvas->drawPath(path, paint);
}
#else
void RosenRenderChart::PaintLineEdge(
    RSCanvas* canvas, RSPath& path, const SegmentInfo segmentInfo, double thickness, bool drawGradient)
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(segmentInfo.GetSegmentColor().GetValue());
    if (segmentInfo.GetLineType() == LineType::DASHED) {
        RSRecordingPath subPath;
        subPath.AddRoundRect(
            RSRoundRect(RSRect(0.0, -0.5 * thickness, segmentInfo.GetSolidWidth(), thickness - 0.5 * thickness),
                0.5 * thickness, 0.5 * thickness));
        pen.SetPathEffect(RSPathEffect::CreatePathDashEffect(
            subPath, segmentInfo.GetSpaceWidth() + segmentInfo.GetSolidWidth(), 5.0f, RSPathDashStyle::MORPH));
    } else {
        pen.SetWidth(thickness);
    }
    if (wholeLineGradient_) {
        double end = startGradientPoint_.GetX();
        if (NearZero(end)) {
            end = startOffset_.GetX() + paintWidth_;
        }
        std::vector<RSPoint> points = { RSPoint(startOffset_.GetX(), 0.0f), RSPoint(end, 0.0f) };
        std::vector<RSColorQuad> colors = { segmentInfo.GetSegmentColor().GetValue(), targetColor_.GetValue() };
        std::vector<RSScalar> pos = { 0.0f };
        pen.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));
    }
    if (gradientOfLine_ && drawGradient) {
        std::vector<RSPoint> points = { RSPoint(startGradientPoint_.GetX(), 0.0f),
            RSPoint(endGradientPoint_.GetX(), 0.0f) };
        std::vector<RSColorQuad> colors = { segmentInfo.GetSegmentColor().ChangeAlpha(0).GetValue(),
            segmentInfo.GetSegmentColor().GetValue() };
        std::vector<RSScalar> pos = { 0.0f };
        pen.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));
    }
    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintLineGradient(
    SkCanvas* canvas, SkPath& path, const Rect& paintRect, Color fillColor, const PointInfo& peekPoint)
{
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setShader(CreateFillGradientShader(paintRect, fillColor, ConvertDataToPosition(paintRect, peekPoint).GetY()));

    paint.setStyle(SkPaint::Style::kStrokeAndFill_Style);
    canvas->drawPath(path, paint);
}
#else
void RosenRenderChart::PaintLineGradient(
    RSCanvas* canvas, RSPath& path, const Rect& paintRect, Color fillColor, const PointInfo& peekPoint)
{
    RSPen pen;
    RSBrush brush;
    pen.SetAntiAlias(true);
    brush.SetAntiAlias(true);
    pen.SetShaderEffect(
        CreateFillGradientShader(paintRect, fillColor, ConvertDataToPosition(paintRect, peekPoint).GetY()));
    brush.SetShaderEffect(
        CreateFillGradientShader(paintRect, fillColor, ConvertDataToPosition(paintRect, peekPoint).GetY()));
    canvas->AttachPen(pen);
    canvas->AttachBrush(brush);
    canvas->DrawPath(path);
    canvas->DetachPen();
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkShader> RosenRenderChart::CreateFillGradientShader(const Rect& paintRect, const Color& fillColor, double top)
{
    SkPoint points[2] = { SkPoint::Make(paintRect.GetOffset().GetX(), top),
        SkPoint::Make(paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY() + paintRect.Height()) };
    SkColor colors[2] = { fillColor.GetValue(), fillColor.ChangeAlpha(0).GetValue() };
    return SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr);
}
#else
std::shared_ptr<RSShaderEffect> RosenRenderChart::CreateFillGradientShader(
    const Rect& paintRect, const Color& fillColor, double top)
{
    std::vector<RSPoint> points = { RSPoint(paintRect.GetOffset().GetX(), top),
        RSPoint(paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY() + paintRect.Height()) };
    std::vector<RSColorQuad> colors = { fillColor.GetValue(), fillColor.ChangeAlpha(0).GetValue() };
    std::vector<RSScalar> pos = { 0.0f };

    return RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP);
}
#endif

Offset RosenRenderChart::CalculateControlA(const Offset& prev, const Offset& cur, const Offset& next)
{
    return Offset(cur.GetX() + (next.GetX() - prev.GetX()) / BEZIER_CONSTANT,
        cur.GetY() + (next.GetY() - prev.GetY()) / BEZIER_CONSTANT);
}

Offset RosenRenderChart::CalculateControlB(const Offset& cur, const Offset& next, const Offset& nextNext)
{
    return Offset(next.GetX() - (nextNext.GetX() - cur.GetX()) / BEZIER_CONSTANT,
        next.GetY() - (nextNext.GetY() - cur.GetY()) / BEZIER_CONSTANT);
}

#ifndef USE_ROSEN_DRAWING
int32_t RosenRenderChart::PaintLine(
    uint32_t startIndex, const std::vector<LineInfo>& line, SkPath& path, const MainChart& data, const Rect& paintRect)
#else
int32_t RosenRenderChart::PaintLine(
    uint32_t startIndex, const std::vector<LineInfo>& line, RSPath& path, const MainChart& data, const Rect& paintRect)
#endif
{
    uint32_t index = startIndex;
    startIndex_ = startIndex;
    bool startPoint = true;
    for (; index < line.size(); index++) {
        const auto& point = line[index].GetPointInfo();
        if (point.GetX() > horizontal_.max || point.GetX() < horizontal_.min || point.GetY() > vertical_.max ||
            point.GetY() < vertical_.min) {
            continue;
        }
        if (startPoint) {
            Offset position = ConvertDataToPosition(paintRect, point);
#ifndef USE_ROSEN_DRAWING
            if (data.GetGradient() && !drawLine_) {
                path.moveTo(position.GetX(), paintRect.GetOffset().GetY() + paintRect.GetSize().Height());
                path.lineTo(position.GetX(), position.GetY());
            } else {
                path.moveTo(position.GetX(), position.GetY());
            }
#else
            if (data.GetGradient() && !drawLine_) {
                path.MoveTo(position.GetX(), paintRect.GetOffset().GetY() + paintRect.GetSize().Height());
                path.LineTo(position.GetX(), position.GetY());
            } else {
                path.MoveTo(position.GetX(), position.GetY());
            }
#endif
            startPoint = false;
        } else if (index == line.size() - 1 ||
                   (data.GetHeadPointIndex() >= 0 && (index == static_cast<uint32_t>(data.GetHeadPointIndex())))) {
            Offset position = ConvertDataToPosition(paintRect, point);
#ifndef USE_ROSEN_DRAWING
            if (data.GetSmoothFlag()) {
                AddCubicPath(path, paintRect, line, index, true);
            } else {
                path.lineTo(position.GetX(), position.GetY());
            }
            if (data.GetGradient() && !drawLine_) {
                path.lineTo(position.GetX(), paintRect.GetOffset().GetY() + paintRect.GetSize().Height());
            }
#else
            if (data.GetSmoothFlag()) {
                AddCubicPath(path, paintRect, line, index, true);
            } else {
                path.LineTo(position.GetX(), position.GetY());
            }
            if (data.GetGradient() && !drawLine_) {
                path.LineTo(position.GetX(), paintRect.GetOffset().GetY() + paintRect.GetSize().Height());
            }
#endif
            index += 1;
            break;
        } else {
            if (data.GetSmoothFlag()) {
                AddCubicPath(path, paintRect, line, index, false);
            } else {
                Offset position = ConvertDataToPosition(paintRect, point);
#ifndef USE_ROSEN_DRAWING
                path.lineTo(position.GetX(), position.GetY());
#else
                path.LineTo(position.GetX(), position.GetY());
#endif
            }
        }
    }
    return index;
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::AddCubicPath(
    SkPath& path, const Rect& paintRect, const std::vector<LineInfo>& line, uint32_t index, bool isEnd)
#else
void RosenRenderChart::AddCubicPath(
    RSPath& path, const Rect& paintRect, const std::vector<LineInfo>& line, uint32_t index, bool isEnd)
#endif
{
    // use control point A = [(Xi + (Xi+1 - Xi-1) / 4), (Yi + (Yi+1 - Yi-1) / 4)]
    // and control point B = [(Xi+1 - (Xi+2 - Xi) / 4), (Yi+1 - (Yi+2 - Yi) / 4)]
    if (index > 0 && index < line.size()) {
        Offset prev = ConvertDataToPosition(
            paintRect, line[(index < 2 || index - 2 < startIndex_) ? startIndex_ : index - 2].GetPointInfo());
        Offset cur = ConvertDataToPosition(paintRect, line[index - 1].GetPointInfo());
        Offset next = ConvertDataToPosition(paintRect, line[index].GetPointInfo());
        Offset nextNext = ConvertDataToPosition(paintRect,
            (isEnd || index + 1 >= line.size()) ? line[index].GetPointInfo() : line[index + 1].GetPointInfo());
        Offset controlA = CalculateControlA(prev, cur, next);
        Offset controlB = CalculateControlB(cur, next, nextNext);
#ifndef USE_ROSEN_DRAWING
        path.cubicTo(controlA.GetX(), controlA.GetY(), controlB.GetX(), controlB.GetY(), next.GetX(), next.GetY());
#else
        path.CubicTo(controlA.GetX(), controlA.GetY(), controlB.GetX(), controlB.GetY(), next.GetX(), next.GetY());
#endif
    } else {
        LOGW("index out of region");
    }
}

void RosenRenderChart::PaintHorizontalAxis(RenderContext& context, const Rect& paintRect)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    const Offset offset = paintRect.GetOffset();
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(horizontal_.color.GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(DEFAULT_AXIS_STROKE_WIDTH);
#else
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(horizontal_.color.GetValue());
    pen.SetWidth(DEFAULT_AXIS_STROKE_WIDTH);
#endif

    if ((horizontal_.tickNumber <= 0) || (horizontal_.tickNumber + 1 == 0)) {
        horizontal_.tickNumber = DEFAULT_AXISTICK;
    }
    tickHorizontalOffset_ = (paintRect.Width() - 2 * EDGE_PADDING) / (horizontal_.tickNumber + 1);

    if (!horizontal_.display) {
        return;
    }

    double tickPosition = EDGE_PADDING + tickHorizontalOffset_;
#ifndef USE_ROSEN_DRAWING
    for (int32_t index = 0; index < horizontal_.tickNumber; index++) {
        canvas->drawLine(offset.GetX() + tickPosition, offset.GetY(), offset.GetX() + tickPosition,
            offset.GetY() + TICK_LENGTH, paint);
        tickPosition += tickHorizontalOffset_;
    }

    canvas->drawLine(offset.GetX(), offset.GetY() + 0.5 * TICK_LENGTH, offset.GetX() + paintRect.Width(),
        offset.GetY() + 0.5 * TICK_LENGTH, paint);
#else
    canvas->AttachPen(pen);
    for (int32_t index = 0; index < horizontal_.tickNumber; index++) {
        canvas->DrawLine(RSPoint(offset.GetX() + tickPosition, offset.GetY()),
            RSPoint(offset.GetX() + tickPosition, offset.GetY() + TICK_LENGTH));
        tickPosition += tickHorizontalOffset_;
    }

    canvas->DrawLine(RSPoint(offset.GetX(), offset.GetY() + 0.5 * TICK_LENGTH),
        RSPoint(offset.GetX() + paintRect.Width(), offset.GetY() + 0.5 * TICK_LENGTH));
    canvas->DetachPen();
#endif
}

void RosenRenderChart::PaintVerticalAxis(RenderContext& context, const Offset& offset, const Rect& paintRect)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(vertical_.color.GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(DEFAULT_AXIS_STROKE_WIDTH);
#else
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(vertical_.color.GetValue());
    pen.SetWidth(DEFAULT_AXIS_STROKE_WIDTH);
#endif

    if ((vertical_.tickNumber <= 0) || (vertical_.tickNumber + 1 == 0)) {
        vertical_.tickNumber = DEFAULT_AXISTICK;
    }
    tickOffset_ = (paintRect.Height() - 2 * EDGE_PADDING) / (vertical_.tickNumber + 1);

    if (!vertical_.display) {
        return;
    }

    double tickPosition = EDGE_PADDING + tickOffset_;
#ifndef USE_ROSEN_DRAWING
    for (int32_t index = 0; index < vertical_.tickNumber; index++) {
        canvas->drawLine(offset.GetX() + paintRect.Width() - TICK_LENGTH, offset.GetY() + tickPosition,
            offset.GetX() + paintRect.Width(), offset.GetY() + tickPosition, paint);
        tickPosition += tickOffset_;
    }

    canvas->drawLine(offset.GetX() + paintRect.Width() - 0.5 * TICK_LENGTH, offset.GetY(),
        offset.GetX() + paintRect.Width() - 0.5 * TICK_LENGTH, offset.GetY() + paintRect.Height(), paint);
#else
    canvas->AttachPen(pen);
    for (int32_t index = 0; index < vertical_.tickNumber; index++) {
        canvas->DrawLine(RSPoint(offset.GetX() + paintRect.Width() - TICK_LENGTH, offset.GetY() + tickPosition),
            RSPoint(offset.GetX() + paintRect.Width(), offset.GetY() + tickPosition));
        tickPosition += tickOffset_;
    }

    canvas->DrawLine(RSPoint(offset.GetX() + paintRect.Width() - 0.5 * TICK_LENGTH, offset.GetY()),
        RSPoint(offset.GetX() + paintRect.Width() - 0.5 * TICK_LENGTH, offset.GetY() + paintRect.Height()));
    canvas->DetachPen();
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderChart::PaintBar(SkCanvas* canvas, SkPaint& paint, const std::vector<LineInfo>& barGroupData,
    const Rect& paintRect, int32_t barGroupNum, int32_t barsAreaNum, int32_t barGroupIndex)
#else
void RosenRenderChart::PaintBar(RSCanvas* canvas, RSPen& pen, RSBrush brush, const std::vector<LineInfo>& barGroupData,
    const Rect& paintRect, int32_t barGroupNum, int32_t barsAreaNum, int32_t barGroupIndex)
#endif
{
    if (NearEqual(paintRect.Width(), 0.0) || NearEqual(paintRect.Height(), 0.0)) {
        LOGE("data paint region width:%{public}lf height:%{public}lf", paintRect.Width(), paintRect.Height());
        return;
    }
    const int32_t barSize = static_cast<int32_t>(barGroupData.size());
    for (int32_t barIndex = 0; barIndex < barSize; ++barIndex) {
        const auto point = barGroupData[barIndex].GetPointInfo();
        // If the actual number of data exceeds Tick, the extra part will not be laid out
        if (barIndex >= barsAreaNum) {
            return;
        }
        auto barsAreaPaintRect = GetBarsAreaPaintRect(paintRect, barIndex);
        double barInterval = BARS_INTERVAL_PROPORTION;
        auto context = GetContext().Upgrade();
        if (context && context->GetMinPlatformVersion() >= MIN_SDK_VERSION) {
            barInterval = 0;
        }
        auto barAreaPaintRect = GetBarAreaPaintRect(barsAreaPaintRect, barGroupIndex, barGroupNum, barInterval);
        Offset position = ConvertDataToPosition(paintRect, point);
        // barAreaPaintRect left add bar interval is originX
        auto originX = barAreaPaintRect.GetOffset().GetX() +
            (BAR_INTERVAL_PROPORTION / 2) * barAreaPaintRect.Width();
        auto originY = position.GetY();

#ifndef USE_ROSEN_DRAWING
        canvas->drawRect(
            SkRect::MakeLTRB(originX, originY, originX + barAreaPaintRect.Width() * (1 - BAR_INTERVAL_PROPORTION),
                paintRect.GetOffset().GetY() + paintRect.Height()),
            paint);
#else
        canvas->AttachPen(pen);
        canvas->AttachBrush(brush);
        canvas->DrawRect(RSRect(originX, originY, originX + barAreaPaintRect.Width() * (1 - BAR_INTERVAL_PROPORTION),
            paintRect.GetOffset().GetY() + paintRect.Height()));
        canvas->DetachPen();
        canvas->DetachBrush();
#endif
    }
}

Rect RosenRenderChart::GetBarsAreaPaintRect(const Rect& paintRect, int32_t barsAreaIndex)
{
    auto barsAreaWidth = paintRect.Width() / horizontal_.tickNumber;
    auto barsAreaHeight = paintRect.Height();
    Rect barsAreaRect =
        Rect(paintRect.Left() + barsAreaIndex * barsAreaWidth, paintRect.Top(), barsAreaWidth, barsAreaHeight);
    return barsAreaRect;
}

Rect RosenRenderChart::GetBarAreaPaintRect(
    const Rect& barsAreaPaintRect, int32_t barGroupIndex, int32_t barGroupNumber, double barInterval)
{
    // Divide 30% of the horizontal space of barsArea into 2 parts as left and right intervals,
    // and divide the remaining part by barGroupNumber to get barAreaWidth
    auto barAreaWidth = (1 - barInterval) * barsAreaPaintRect.Width() / barGroupNumber;
    auto barAreaHeight = barsAreaPaintRect.Height();
    // After leaving the interval, the left border of the barArea area is obtained
    auto barAreaLeft =
        barsAreaPaintRect.Left() + barInterval / 2 * barsAreaPaintRect.Width() + barGroupIndex * barAreaWidth;
    Rect barAreaRect = Rect(barAreaLeft, barsAreaPaintRect.Top(), barAreaWidth, barAreaHeight);
    return barAreaRect;
}

} // namespace OHOS::Ace
