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

#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"

#include "securec.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::NG {

void CanvasRenderingContext2DModelNG::SetOnAttach(std::function<void()>&& callback)
{
    isAttached_ = true;
}

void CanvasRenderingContext2DModelNG::SetOnDetach(std::function<void()>&& callback) {}

int32_t CanvasRenderingContext2DModelNG::GetId()
{
    return 0;
}

void CanvasRenderingContext2DModelNG::OnAttachToCanvas() {}

void CanvasRenderingContext2DModelNG::OnDetachFromCanvas() {}

void CanvasRenderingContext2DModelNG::SetPattern(RefPtr<AceType> newPattern) {}

void CanvasRenderingContext2DModelNG::Release() {}

void CanvasRenderingContext2DModelNG::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo) {}

void CanvasRenderingContext2DModelNG::SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo) {}

void CanvasRenderingContext2DModelNG::SetAntiAlias(bool anti) {}

void CanvasRenderingContext2DModelNG::SetFontWeight(const FontWeight& weight) {}

void CanvasRenderingContext2DModelNG::SetFontStyle(const Ace::FontStyle& fontStyle) {}

void CanvasRenderingContext2DModelNG::SetFontFamilies(const std::vector<std::string>& families) {}

void CanvasRenderingContext2DModelNG::SetFontSize(const Dimension& size) {}

void CanvasRenderingContext2DModelNG::SetLetterSpacing(const Dimension& letterSpacing) {}

std::vector<double> CanvasRenderingContext2DModelNG::GetLineDash()
{
    return std::vector<double> {};
}

void CanvasRenderingContext2DModelNG::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient) {}

void CanvasRenderingContext2DModelNG::SetFillPattern(const std::shared_ptr<Ace::Pattern>& acePattern) {}

void CanvasRenderingContext2DModelNG::SetFillColor(const Color& color, bool colorFlag) {}

void CanvasRenderingContext2DModelNG::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient) {}

void CanvasRenderingContext2DModelNG::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& acePattern) {}

void CanvasRenderingContext2DModelNG::SetStrokeColor(const Color& color, bool colorFlag) {}

void CanvasRenderingContext2DModelNG::DrawImage(const ImageInfo& imageInfo) {}

void CanvasRenderingContext2DModelNG::DrawSvgImage(const ImageInfo& imageInfo) {}

void CanvasRenderingContext2DModelNG::PutImageData(const Ace::ImageData& imageData) {}

void CanvasRenderingContext2DModelNG::CloseImageBitmap(const std::string& src) {}

std::unique_ptr<Ace::ImageData> CanvasRenderingContext2DModelNG::GetImageData(const ImageSize& imageSize)
{
    return nullptr;
}

void CanvasRenderingContext2DModelNG::DrawPixelMap(const ImageInfo& imageInfo) {}

void CanvasRenderingContext2DModelNG::SetFilterParam(const std::string& src) {}

void CanvasRenderingContext2DModelNG::SetTextDirection(const TextDirection& direction) {}

std::string CanvasRenderingContext2DModelNG::GetJsonData(const std::string& path)
{
    return "";
}

std::string CanvasRenderingContext2DModelNG::ToDataURL(const std::string& dataUrl, double quality)
{
    return "";
}

void CanvasRenderingContext2DModelNG::SetLineCap(const LineCapStyle& lineCap) {}

void CanvasRenderingContext2DModelNG::SetLineJoin(const LineJoinStyle& lineJoin) {}

void CanvasRenderingContext2DModelNG::SetMiterLimit(double limit) {}

void CanvasRenderingContext2DModelNG::SetLineWidth(double lineWidth) {}

void CanvasRenderingContext2DModelNG::SetGlobalAlpha(double alpha) {}

void CanvasRenderingContext2DModelNG::SetCompositeType(const CompositeOperation& type) {}

void CanvasRenderingContext2DModelNG::SetLineDashOffset(double lineDashOffset) {}

void CanvasRenderingContext2DModelNG::SetShadowBlur(double blur) {}

void CanvasRenderingContext2DModelNG::SetShadowColor(const Color& color) {}

void CanvasRenderingContext2DModelNG::SetShadowOffsetX(double offsetX) {}

void CanvasRenderingContext2DModelNG::SetShadowOffsetY(double offsetY) {}

void CanvasRenderingContext2DModelNG::SetSmoothingEnabled(bool enabled) {}

void CanvasRenderingContext2DModelNG::SetSmoothingQuality(const std::string& quality) {}

void CanvasRenderingContext2DModelNG::MoveTo(double x, double y) {}

void CanvasRenderingContext2DModelNG::LineTo(double x, double y) {}

void CanvasRenderingContext2DModelNG::BezierCurveTo(const BezierCurveParam& param) {}

void CanvasRenderingContext2DModelNG::QuadraticCurveTo(const QuadraticCurveParam& param) {}

void CanvasRenderingContext2DModelNG::ArcTo(const ArcToParam& param) {}

void CanvasRenderingContext2DModelNG::Arc(const ArcParam& param) {}

void CanvasRenderingContext2DModelNG::Ellipse(const EllipseParam& param) {}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath(const CanvasFillRule& fillRule) {}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath(const CanvasFillRule& fillRule) {}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath(const CanvasFillRule& fillRule) {}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{}

void CanvasRenderingContext2DModelNG::AddRect(const Rect& rect) {}

void CanvasRenderingContext2DModelNG::BeginPath() {}

void CanvasRenderingContext2DModelNG::ClosePath() {}

void CanvasRenderingContext2DModelNG::Restore() {}

void CanvasRenderingContext2DModelNG::CanvasRendererSave() {}

void CanvasRenderingContext2DModelNG::CanvasRendererRotate(double angle) {}

void CanvasRenderingContext2DModelNG::CanvasRendererScale(double x, double y) {}

void CanvasRenderingContext2DModelNG::SetTransform(TransformParam& param, bool lengthFlag) {}

void CanvasRenderingContext2DModelNG::ResetTransform() {}

void CanvasRenderingContext2DModelNG::Transform(const TransformParam& param) {}

void CanvasRenderingContext2DModelNG::Translate(double x, double y) {}

void CanvasRenderingContext2DModelNG::SetLineDash(const std::vector<double>& lineDash) {}

void CanvasRenderingContext2DModelNG::SetTextAlign(const TextAlign& align) {}

void CanvasRenderingContext2DModelNG::SetTextBaseline(const TextBaseline& baseline) {}

void CanvasRenderingContext2DModelNG::FillRect(const Rect& rect) {}

void CanvasRenderingContext2DModelNG::StrokeRect(const Rect& rect) {}

void CanvasRenderingContext2DModelNG::ClearRect(const Rect& rect) {}

TransformParam CanvasRenderingContext2DModelNG::GetTransform()
{
    return TransformParam {};
}

RefPtr<Ace::PixelMap> CanvasRenderingContext2DModelNG::GetPixelMap(const ImageSize& imageSize)
{
    return nullptr;
}

void CanvasRenderingContext2DModelNG::GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer) {}

TextMetrics CanvasRenderingContext2DModelNG::GetMeasureTextMetrics(const PaintState& state, const std::string& text)
{
    return TextMetrics {};
}

void CanvasRenderingContext2DModelNG::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData) {}

void CanvasRenderingContext2DModelNG::SaveLayer() {}

void CanvasRenderingContext2DModelNG::RestoreLayer() {}

void CanvasRenderingContext2DModelNG::Reset() {}

void CanvasRenderingContext2DModelNG::SetTransform(
    std::shared_ptr<Ace::Pattern> acePattern, const TransformParam& transform)
{}

// All interfaces that only the 'CanvasRenderingContext2D' has.
void CanvasRenderingContext2DModelNG::GetWidth(double& width) {}

void CanvasRenderingContext2DModelNG::GetHeight(double& height) {}

void CanvasRenderingContext2DModelNG::SetDensity(double density) {}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const RefPtr<AceType>& pixelMap) {}
#else
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const std::shared_ptr<Ace::ImageData>& imageData) {}
#endif

void CanvasRenderingContext2DModelNG::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed) {}

void CanvasRenderingContext2DModelNG::StopImageAnalyzer() {}
} // namespace OHOS::Ace::NG
