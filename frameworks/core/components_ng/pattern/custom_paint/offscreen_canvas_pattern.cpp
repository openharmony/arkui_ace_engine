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

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"

namespace OHOS::Ace::NG {
OffscreenCanvasPattern::OffscreenCanvasPattern(int32_t width, int32_t height)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    offscreenPaintMethod_ = MakeRefPtr<OffscreenCanvasPaintMethod>(context, width, height);
}

void OffscreenCanvasPattern::FillRect(const Rect& rect)
{
    offscreenPaintMethod_->FillRect(nullptr, rect);
}

void OffscreenCanvasPattern::StrokeRect(const Rect& rect)
{
    offscreenPaintMethod_->StrokeRect(nullptr, rect);
}

void OffscreenCanvasPattern::ClearRect(const Rect& rect)
{
    offscreenPaintMethod_->ClearRect(nullptr, rect);
}

void OffscreenCanvasPattern::Fill()
{
    offscreenPaintMethod_->Fill(nullptr);
}

void OffscreenCanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    offscreenPaintMethod_->Fill(nullptr, path);
}

void OffscreenCanvasPattern::Stroke()
{
    offscreenPaintMethod_->Stroke(nullptr);
}

void OffscreenCanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    offscreenPaintMethod_->Stroke(nullptr, path);
}

void OffscreenCanvasPattern::BeginPath()
{
    offscreenPaintMethod_->BeginPath();
}

void OffscreenCanvasPattern::ClosePath()
{
    offscreenPaintMethod_->ClosePath();
}

void OffscreenCanvasPattern::MoveTo(double x, double y)
{
    offscreenPaintMethod_->MoveTo(nullptr, x, y);
}

void OffscreenCanvasPattern::LineTo(double x, double y)
{
    offscreenPaintMethod_->LineTo(nullptr, x, y);
}

void OffscreenCanvasPattern::Arc(const ArcParam& param)
{
    offscreenPaintMethod_->Arc(nullptr, param);
}

void OffscreenCanvasPattern::ArcTo(const ArcToParam& param)
{
    offscreenPaintMethod_->ArcTo(nullptr, param);
}

void OffscreenCanvasPattern::AddRect(const Rect& rect)
{
    offscreenPaintMethod_->AddRect(nullptr, rect);
}

void OffscreenCanvasPattern::Ellipse(const EllipseParam& param)
{
    offscreenPaintMethod_->Ellipse(nullptr, param);
}

void OffscreenCanvasPattern::BezierCurveTo(const BezierCurveParam& param)
{
    offscreenPaintMethod_->BezierCurveTo(nullptr, param);
}

void OffscreenCanvasPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    offscreenPaintMethod_->QuadraticCurveTo(nullptr, param);
}

void OffscreenCanvasPattern::FillText(const std::string& text, double x, double y, const PaintState& state)
{
    offscreenPaintMethod_->FillText(text, x, y, state);
}

void OffscreenCanvasPattern::StrokeText(const std::string& text, double x, double y, const PaintState& state)
{
    offscreenPaintMethod_->StrokeText(text, x, y, state);
}

double OffscreenCanvasPattern::MeasureText(const std::string& text, const PaintState& state)
{
    return offscreenPaintMethod_->MeasureText(text, state);
}

double OffscreenCanvasPattern::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    return offscreenPaintMethod_->MeasureTextHeight(text, state);
}

TextMetrics OffscreenCanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return offscreenPaintMethod_->MeasureTextMetrics(text, state);
}

void OffscreenCanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
    offscreenPaintMethod_->DrawImage(nullptr, image, width, height);
}

void OffscreenCanvasPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
    offscreenPaintMethod_->DrawPixelMap(pixelMap, image);
}

std::unique_ptr<Ace::ImageData> OffscreenCanvasPattern::GetImageData(
    double left, double top, double width, double height)
{
    return offscreenPaintMethod_->GetImageData(left, top, width, height);
}

void OffscreenCanvasPattern::PutImageData(const Ace::ImageData& imageData)
{
    offscreenPaintMethod_->PutImageData(nullptr, imageData);
}

void OffscreenCanvasPattern::UpdateFillColor(const Color& color)
{
    offscreenPaintMethod_->SetFillColor(color);
}

void OffscreenCanvasPattern::SetFillRuleForPath(const CanvasFillRule rule)
{
    offscreenPaintMethod_->SetFillRuleForPath(rule);
}

void OffscreenCanvasPattern::SetFillRuleForPath2D(const CanvasFillRule rule)
{
    offscreenPaintMethod_->SetFillRuleForPath2D(rule);
}

int32_t OffscreenCanvasPattern::GetWidth()
{
    return offscreenPaintMethod_->GetWidth();
}

int32_t OffscreenCanvasPattern::GetHeight()
{
    return offscreenPaintMethod_->GetHeight();
}

const LineDashParam& OffscreenCanvasPattern::GetLineDash() const
{
    return offscreenPaintMethod_->GetLineDash();
}

void OffscreenCanvasPattern::SetLineDash(const std::vector<double>& segments)
{
    offscreenPaintMethod_->SetLineDash(segments);
}

void OffscreenCanvasPattern::Save()
{
    offscreenPaintMethod_->Save();
}

void OffscreenCanvasPattern::Restore()
{
    offscreenPaintMethod_->Restore();
}

void OffscreenCanvasPattern::Scale(double x, double y)
{
    offscreenPaintMethod_->Scale(x, y);
}

void OffscreenCanvasPattern::Rotate(double angle)
{
    offscreenPaintMethod_->Rotate(angle);
}

void OffscreenCanvasPattern::SetTransform(const TransformParam& param)
{
    offscreenPaintMethod_->SetTransform(param);
}

void OffscreenCanvasPattern::Transform(const TransformParam& param)
{
    offscreenPaintMethod_->Transform(param);
}

void OffscreenCanvasPattern::Translate(double x, double y)
{
    offscreenPaintMethod_->Translate(x, y);
}

std::string OffscreenCanvasPattern::ToDataURL(const std::string& type, const double quality)
{
    return offscreenPaintMethod_->ToDataURL(type, quality);
}
} // namespace OHOS::Ace::NG
