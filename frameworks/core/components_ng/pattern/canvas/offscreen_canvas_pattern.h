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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class OffscreenCanvasPaintMethod;
// OffscreenCanvasPattern is the base class for custom paint render node to perform paint canvas.
class CJ_FORCE_EXPORT OffscreenCanvasPattern : public Pattern {
    DECLARE_ACE_TYPE(OffscreenCanvasPattern, Pattern);

public:
    OffscreenCanvasPattern(int32_t width, int32_t height);
    ~OffscreenCanvasPattern() override = default;

    void FillRect(const Rect& rect);
    void StrokeRect(const Rect& rect);
    void ClearRect(const Rect& rect);
    void Fill();
    void Fill(const RefPtr<CanvasPath2D>& path);
    void Stroke();
    void Stroke(const RefPtr<CanvasPath2D>& path);
    void Clip();
    void Clip(const RefPtr<CanvasPath2D>& path);
    void BeginPath();
    void ClosePath();
    void MoveTo(double x, double y);
    void LineTo(double x, double y);
    void Arc(const ArcParam& param);
    void ArcTo(const ArcToParam& param);
    void AddRect(const Rect& rect);
    void Ellipse(const EllipseParam& param);
    void BezierCurveTo(const BezierCurveParam& param);
    void QuadraticCurveTo(const QuadraticCurveParam& param);

    void FillText(const std::string& text, double x, double y, std::optional<double> maxWidth);
    void StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);

    void DrawImage(const Ace::CanvasImage& image, double width, double height);
    void DrawSvgImage(RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void GetImageData(const std::shared_ptr<Ace::ImageData>& imageData);
    void PutImageData(const Ace::ImageData& imageData);

    void SetAntiAlias(bool isEnabled);
    void SetFillRuleForPath(const CanvasFillRule rule);
    void SetFillRuleForPath2D(const CanvasFillRule rule);
    void SetFillPattern(const std::weak_ptr<Ace::Pattern>& pattern);
    void SetFillGradient(const Ace::Gradient& gradient);
    void SetAlpha(double alpha);
    void SetCompositeType(CompositeOperation operation);
    void SetLineWidth(double width);
    void SetLineCap(LineCapStyle style);
    void SetLineJoin(LineJoinStyle style);
    void SetMiterLimit(double limit);
    void SetTextAlign(TextAlign align);
    void SetTextBaseline(TextBaseline baseline);
    void SetShadowBlur(double blur);
    void SetShadowOffsetX(double x);
    void SetShadowOffsetY(double y);
    void SetSmoothingEnabled(bool enabled);
    void SetSmoothingQuality(const std::string& quality);
    void SetLineDashOffset(double offset);
    void SetShadowColor(const Color& color);
    void SetStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern);
    void SetStrokeGradient(const Ace::Gradient& gradient);
    void SetStrokeColor(const Color& color);
    void SetFontWeight(FontWeight weight);
    void SetFontStyle(FontStyle style);
    void SetFontFamilies(const std::vector<std::string>& fontFamilies);
    void SetFontSize(const Dimension& size);
    void SetLetterSpacing(const Dimension& letterSpacing);
    void SetFillColor(const Color& color);
    int32_t GetWidth();
    int32_t GetHeight();

    LineDashParam GetLineDash() const;
    void SetLineDash(const std::vector<double>& segments);

    void SetTextDirection(TextDirection direction);
    void SetFilterParam(const std::string& filterStr);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    void SetTransform(const TransformParam& param);
    void ResetTransform();
    void Transform(const TransformParam& param);
    void Translate(double x, double y);
    TransformParam GetTransform() const;
    std::string ToDataURL(const std::string& type, const double quality);
    void SaveLayer();
    void RestoreLayer();
    void UpdateSize(int32_t width, int32_t height);
    void Reset();
    RefPtr<PixelMap> TransferToImageBitmap();
    void SetDensity(double density);
    void SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform);

    size_t GetBitmapSize();
private:
    void UpdateTextDefaultDirection();
    RefPtr<OffscreenCanvasPaintMethod> offscreenPaintMethod_;
    TextDirection currentSetTextDirection_ = TextDirection::INHERIT;
    ACE_DISALLOW_COPY_AND_MOVE(OffscreenCanvasPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
