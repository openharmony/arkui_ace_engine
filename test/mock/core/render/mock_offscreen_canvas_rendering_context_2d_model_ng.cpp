/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h"

#include "securec.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::NG {

void OffscreenCanvasRenderingContext2DModelNG::SetPattern(RefPtr<AceType> pattern) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo) {}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo)
{}

void OffscreenCanvasRenderingContext2DModelNG::SetAntiAlias(bool anti) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFontWeight(const FontWeight& weight) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFontStyle(const Ace::FontStyle& fontStyle) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFontFamilies(const std::vector<std::string>& families) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFontSize(const Dimension& size) {}

void OffscreenCanvasRenderingContext2DModelNG::SetLetterSpacing(const Dimension& letterSpacing) {}

std::vector<double> OffscreenCanvasRenderingContext2DModelNG::GetLineDash()
{
    return std::vector<double> {};
}

void OffscreenCanvasRenderingContext2DModelNG::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFillColor(const Color& color, bool colorFlag) {}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient) {}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern) {}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokeColor(const Color& color, bool colorFlag) {}

void OffscreenCanvasRenderingContext2DModelNG::DrawImage(const ImageInfo& imageInfo) {}

void OffscreenCanvasRenderingContext2DModelNG::DrawSvgImage(const ImageInfo& imageInfo) {}

void OffscreenCanvasRenderingContext2DModelNG::PutImageData(const Ace::ImageData& imageData) {}

void OffscreenCanvasRenderingContext2DModelNG::CloseImageBitmap(const std::string& src) {}

std::unique_ptr<Ace::ImageData> OffscreenCanvasRenderingContext2DModelNG::GetImageData(const ImageSize& imageSize)
{
    return nullptr;
}

void OffscreenCanvasRenderingContext2DModelNG::DrawPixelMap(const ImageInfo& imageInfo) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFilterParam(const std::string& src) {}

void OffscreenCanvasRenderingContext2DModelNG::SetTextDirection(const TextDirection& direction) {}

std::string OffscreenCanvasRenderingContext2DModelNG::GetJsonData(const std::string& path)
{
    return "";
}

std::string OffscreenCanvasRenderingContext2DModelNG::ToDataURL(const std::string& dataUrl, double quality)
{
    return "";
}

void OffscreenCanvasRenderingContext2DModelNG::SetLineCap(const LineCapStyle& lineCap) {}

void OffscreenCanvasRenderingContext2DModelNG::SetLineJoin(const LineJoinStyle& lineJoin) {}

void OffscreenCanvasRenderingContext2DModelNG::SetMiterLimit(double limit) {}

void OffscreenCanvasRenderingContext2DModelNG::SetLineWidth(double lineWidth) {}

void OffscreenCanvasRenderingContext2DModelNG::SetGlobalAlpha(double alpha) {}

void OffscreenCanvasRenderingContext2DModelNG::SetCompositeType(const CompositeOperation& type) {}

void OffscreenCanvasRenderingContext2DModelNG::SetLineDashOffset(double lineDashOffset) {}

void OffscreenCanvasRenderingContext2DModelNG::SetShadowBlur(double blur) {}

void OffscreenCanvasRenderingContext2DModelNG::SetShadowColor(const Color& color) {}

void OffscreenCanvasRenderingContext2DModelNG::SetShadowOffsetX(double offsetX) {}

void OffscreenCanvasRenderingContext2DModelNG::SetShadowOffsetY(double offsetY) {}

void OffscreenCanvasRenderingContext2DModelNG::SetSmoothingEnabled(bool enabled) {}

void OffscreenCanvasRenderingContext2DModelNG::SetSmoothingQuality(const std::string& quality) {}

void OffscreenCanvasRenderingContext2DModelNG::MoveTo(double x, double y) {}

void OffscreenCanvasRenderingContext2DModelNG::LineTo(double x, double y) {}

void OffscreenCanvasRenderingContext2DModelNG::BezierCurveTo(const BezierCurveParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::QuadraticCurveTo(const QuadraticCurveParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::ArcTo(const ArcToParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::Arc(const ArcParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::Ellipse(const EllipseParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFillRuleForPath(const CanvasFillRule& fillRule) {}

void OffscreenCanvasRenderingContext2DModelNG::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void OffscreenCanvasRenderingContext2DModelNG::SetStrokeRuleForPath(const CanvasFillRule& fillRule) {}

void OffscreenCanvasRenderingContext2DModelNG::SetClipRuleForPath(const CanvasFillRule& fillRule) {}

void OffscreenCanvasRenderingContext2DModelNG::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void OffscreenCanvasRenderingContext2DModelNG::AddRect(const Rect& rect) {}

void OffscreenCanvasRenderingContext2DModelNG::BeginPath() {}

void OffscreenCanvasRenderingContext2DModelNG::ClosePath() {}

void OffscreenCanvasRenderingContext2DModelNG::Restore() {}

void OffscreenCanvasRenderingContext2DModelNG::CanvasRendererSave() {}

void OffscreenCanvasRenderingContext2DModelNG::CanvasRendererRotate(double angle) {}

void OffscreenCanvasRenderingContext2DModelNG::CanvasRendererScale(double x, double y) {}

void OffscreenCanvasRenderingContext2DModelNG::SetTransform(TransformParam& param, bool lengthFlag) {}

void OffscreenCanvasRenderingContext2DModelNG::ResetTransform() {}

void OffscreenCanvasRenderingContext2DModelNG::Transform(const TransformParam& param) {}

void OffscreenCanvasRenderingContext2DModelNG::Translate(double x, double y) {}

void OffscreenCanvasRenderingContext2DModelNG::SetLineDash(const std::vector<double>& lineDash) {}

void OffscreenCanvasRenderingContext2DModelNG::SetTextAlign(const TextAlign& align) {}

void OffscreenCanvasRenderingContext2DModelNG::SetTextBaseline(const TextBaseline& baseline) {}

void OffscreenCanvasRenderingContext2DModelNG::FillRect(const Rect& rect) {}

void OffscreenCanvasRenderingContext2DModelNG::StrokeRect(const Rect& rect) {}

void OffscreenCanvasRenderingContext2DModelNG::ClearRect(const Rect& rect) {}

TransformParam OffscreenCanvasRenderingContext2DModelNG::GetTransform()
{
    return TransformParam {};
}

RefPtr<Ace::PixelMap> OffscreenCanvasRenderingContext2DModelNG::GetPixelMap(const ImageSize& imageSize)
{
    return nullptr;
}

void OffscreenCanvasRenderingContext2DModelNG::GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer) {}

TextMetrics OffscreenCanvasRenderingContext2DModelNG::GetMeasureTextMetrics(
    const PaintState& state, const std::string& text)
{
    return TextMetrics {};
}

void OffscreenCanvasRenderingContext2DModelNG::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData) {}

void OffscreenCanvasRenderingContext2DModelNG::SaveLayer() {}

void OffscreenCanvasRenderingContext2DModelNG::RestoreLayer() {}

void OffscreenCanvasRenderingContext2DModelNG::Reset() {}

void OffscreenCanvasRenderingContext2DModelNG::SetDensity(double density) {}

void OffscreenCanvasRenderingContext2DModelNG::SetTransform(
    std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{}

// All interfaces that only the 'OffscreenCanvasRenderingContext2D' has.
RefPtr<AceType> OffscreenCanvasRenderingContext2DModelNG::CreateOffscreenPattern(int width, int height)
{
    return nullptr;
}

size_t OffscreenCanvasRenderingContext2DModelNG::GetBitmapSize(RefPtr<AceType> offscreenPattern)
{
    return 0;
}
} // namespace OHOS::Ace::NG
