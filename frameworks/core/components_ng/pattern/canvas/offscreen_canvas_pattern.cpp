/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"

namespace OHOS::Ace::NG {
OffscreenCanvasPattern::OffscreenCanvasPattern(int32_t width, int32_t height)
{
    offscreenPaintMethod_ = MakeRefPtr<OffscreenCanvasPaintMethod>(std::max(width, 0), std::max(height, 0));
}

void OffscreenCanvasPattern::UpdateSize(int32_t width, int32_t height)
{
    CHECK_NULL_VOID(offscreenPaintMethod_);
    return offscreenPaintMethod_->UpdateSize(std::max(width, 0), std::max(height, 0));
}

void OffscreenCanvasPattern::FillRect(const Rect& rect)
{
    offscreenPaintMethod_->FillRect(rect);
}

void OffscreenCanvasPattern::StrokeRect(const Rect& rect)
{
    offscreenPaintMethod_->StrokeRect(rect);
}

void OffscreenCanvasPattern::ClearRect(const Rect& rect)
{
    offscreenPaintMethod_->ClearRect(rect);
}

void OffscreenCanvasPattern::Fill()
{
    offscreenPaintMethod_->Fill();
}

void OffscreenCanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    offscreenPaintMethod_->Fill(path);
}

void OffscreenCanvasPattern::Stroke()
{
    offscreenPaintMethod_->Stroke();
}

void OffscreenCanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    offscreenPaintMethod_->Stroke(path);
}

void OffscreenCanvasPattern::Clip()
{
    offscreenPaintMethod_->Clip();
}

void OffscreenCanvasPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
    offscreenPaintMethod_->Clip(path);
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
    offscreenPaintMethod_->MoveTo(x, y);
}

void OffscreenCanvasPattern::LineTo(double x, double y)
{
    offscreenPaintMethod_->LineTo(x, y);
}

void OffscreenCanvasPattern::Arc(const ArcParam& param)
{
    offscreenPaintMethod_->Arc(param);
}

void OffscreenCanvasPattern::ArcTo(const ArcToParam& param)
{
    offscreenPaintMethod_->ArcTo(param);
}

void OffscreenCanvasPattern::AddRect(const Rect& rect)
{
    offscreenPaintMethod_->AddRect(rect);
}

void OffscreenCanvasPattern::Ellipse(const EllipseParam& param)
{
    offscreenPaintMethod_->Ellipse(param);
}

void OffscreenCanvasPattern::BezierCurveTo(const BezierCurveParam& param)
{
    offscreenPaintMethod_->BezierCurveTo(param);
}

void OffscreenCanvasPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    offscreenPaintMethod_->QuadraticCurveTo(param);
}

void OffscreenCanvasPattern::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    UpdateTextDefaultDirection();
    offscreenPaintMethod_->FillText(text, x, y, maxWidth);
}

void OffscreenCanvasPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    UpdateTextDefaultDirection();
    offscreenPaintMethod_->StrokeText(text, x, y, maxWidth);
}

TextMetrics OffscreenCanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return offscreenPaintMethod_->MeasureTextMetrics(text, state);
}

void OffscreenCanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
    offscreenPaintMethod_->DrawImage(image, width, height);
}

void OffscreenCanvasPattern::DrawSvgImage(
    RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit)
{
    offscreenPaintMethod_->DrawSvgImage(svgDom, image, imageFit);
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

void OffscreenCanvasPattern::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(offscreenPaintMethod_);
    offscreenPaintMethod_->GetImageData(imageData);
}

void OffscreenCanvasPattern::PutImageData(const Ace::ImageData& imageData)
{
    offscreenPaintMethod_->PutImageData(imageData);
}

void OffscreenCanvasPattern::SetAntiAlias(bool isEnabled)
{
    offscreenPaintMethod_->SetAntiAlias(isEnabled);
}

void OffscreenCanvasPattern::SetFillColor(const Color& color)
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

LineDashParam OffscreenCanvasPattern::GetLineDash() const
{
    return offscreenPaintMethod_->GetLineDash();
}

void OffscreenCanvasPattern::SetLineDash(const std::vector<double>& segments)
{
    offscreenPaintMethod_->SetLineDash(segments);
}

void OffscreenCanvasPattern::SetTextDirection(TextDirection direction)
{
    currentSetTextDirection_ = direction;
    if (direction == TextDirection::INHERIT) {
        direction = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    offscreenPaintMethod_->SetTextDirection(direction);
}

void OffscreenCanvasPattern::SetFilterParam(const std::string& filterStr)
{
    offscreenPaintMethod_->SetFilterParam(filterStr);
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

void OffscreenCanvasPattern::ResetTransform()
{
    offscreenPaintMethod_->ResetTransform();
}

void OffscreenCanvasPattern::Transform(const TransformParam& param)
{
    offscreenPaintMethod_->Transform(param);
}

void OffscreenCanvasPattern::Translate(double x, double y)
{
    offscreenPaintMethod_->Translate(x, y);
}

void OffscreenCanvasPattern::SetFillPattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    offscreenPaintMethod_->SetFillPatternNG(pattern);
}

void OffscreenCanvasPattern::SetFillGradient(const Ace::Gradient& gradient)
{
    offscreenPaintMethod_->SetFillGradient(gradient);
}

void OffscreenCanvasPattern::SetAlpha(double alpha)
{
    offscreenPaintMethod_->SetAlpha(alpha);
}

void OffscreenCanvasPattern::SetCompositeType(CompositeOperation operation)
{
    offscreenPaintMethod_->SetCompositeType(operation);
}

void OffscreenCanvasPattern::SetLineWidth(double width)
{
    offscreenPaintMethod_->SetLineWidth(width);
}

void OffscreenCanvasPattern::SetLineCap(LineCapStyle style)
{
    offscreenPaintMethod_->SetLineCap(style);
}

void OffscreenCanvasPattern::SetLineJoin(LineJoinStyle style)
{
    offscreenPaintMethod_->SetLineJoin(style);
}

void OffscreenCanvasPattern::SetMiterLimit(double limit)
{
    offscreenPaintMethod_->SetMiterLimit(limit);
}

void OffscreenCanvasPattern::SetTextAlign(TextAlign align)
{
    offscreenPaintMethod_->SetTextAlign(align);
}

void OffscreenCanvasPattern::SetTextBaseline(TextBaseline baseline)
{
    offscreenPaintMethod_->SetTextBaseline(baseline);
}

void OffscreenCanvasPattern::SetShadowBlur(double blur)
{
    offscreenPaintMethod_->SetShadowBlur(blur);
}

void OffscreenCanvasPattern::SetShadowOffsetX(double x)
{
    offscreenPaintMethod_->SetShadowOffsetX(x);
}

void OffscreenCanvasPattern::SetShadowOffsetY(double y)
{
    offscreenPaintMethod_->SetShadowOffsetY(y);
}

void OffscreenCanvasPattern::SetSmoothingEnabled(bool enabled)
{
    offscreenPaintMethod_->SetSmoothingEnabled(enabled);
}

void OffscreenCanvasPattern::SetSmoothingQuality(const std::string& quality)
{
    offscreenPaintMethod_->SetSmoothingQuality(quality);
}

void OffscreenCanvasPattern::SetLineDashOffset(double offset)
{
    offscreenPaintMethod_->SetLineDashOffset(offset);
}

void OffscreenCanvasPattern::SetShadowColor(const Color& color)
{
    offscreenPaintMethod_->SetShadowColor(color);
}

void OffscreenCanvasPattern::SetStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    offscreenPaintMethod_->SetStrokePatternNG(pattern);
}

void OffscreenCanvasPattern::SetStrokeGradient(const Ace::Gradient& gradient)
{
    offscreenPaintMethod_->SetStrokeGradient(gradient);
}

void OffscreenCanvasPattern::SetStrokeColor(const Color& color)
{
    offscreenPaintMethod_->SetStrokeColor(color);
}

void OffscreenCanvasPattern::SetFontWeight(FontWeight weight)
{
    offscreenPaintMethod_->SetFontWeight(weight);
}

void OffscreenCanvasPattern::SetFontStyle(FontStyle style)
{
    offscreenPaintMethod_->SetFontStyle(style);
}

void OffscreenCanvasPattern::SetFontFamilies(const std::vector<std::string>& fontFamilies)
{
    offscreenPaintMethod_->SetFontFamilies(fontFamilies);
}

void OffscreenCanvasPattern::SetFontSize(const Dimension& size)
{
    offscreenPaintMethod_->SetFontSize(size);
}

void OffscreenCanvasPattern::SetLetterSpacing(const Dimension& letterSpacing)
{
    offscreenPaintMethod_->SetLetterSpacing(letterSpacing);
}

std::string OffscreenCanvasPattern::ToDataURL(const std::string& type, const double quality)
{
    return offscreenPaintMethod_->ToDataURL(type, quality);
}

TransformParam OffscreenCanvasPattern::GetTransform() const
{
    return offscreenPaintMethod_->GetTransform();
}

void OffscreenCanvasPattern::SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{
    offscreenPaintMethod_->SetTransform(pattern, transform);
}

void OffscreenCanvasPattern::SaveLayer()
{
    offscreenPaintMethod_->SaveLayer();
}

void OffscreenCanvasPattern::RestoreLayer()
{
    offscreenPaintMethod_->RestoreLayer();
}

size_t OffscreenCanvasPattern::GetBitmapSize()
{
    CHECK_NULL_RETURN(offscreenPaintMethod_, 0);
    return offscreenPaintMethod_->GetBitmapSize();
}

void OffscreenCanvasPattern::Reset()
{
    offscreenPaintMethod_->Reset();
    offscreenPaintMethod_->SetTextDirection(
        AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
}

void OffscreenCanvasPattern::UpdateTextDefaultDirection()
{
    if (currentSetTextDirection_ != TextDirection::INHERIT) {
        return;
    }
    offscreenPaintMethod_->SetTextDirection(
        AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
}

RefPtr<PixelMap> OffscreenCanvasPattern::TransferToImageBitmap()
{
    return offscreenPaintMethod_->TransferToImageBitmap();
}

void OffscreenCanvasPattern::SetDensity(double density)
{
    offscreenPaintMethod_->SetDensity(density);
}
} // namespace OHOS::Ace::NG
