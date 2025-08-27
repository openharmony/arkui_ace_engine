/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_OFFSCREEN_CANVAS_RENDERING_CONTEXT_2D_MODEL_NG_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_OFFSCREEN_CANVAS_RENDERING_CONTEXT_2D_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/canvas/rendering_context_2d_model.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT OffscreenCanvasRenderingContext2DModelNG
    : public OHOS::Ace::OffscreenCanvasRenderingContext2DModel {
    DECLARE_ACE_TYPE(OffscreenCanvasRenderingContext2DModelNG, OffscreenCanvasRenderingContext2DModel);

public:
    OffscreenCanvasRenderingContext2DModelNG() = default;
    ~OffscreenCanvasRenderingContext2DModelNG() override = default;

    void SetPattern(RefPtr<AceType> pattern) override;
    void SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo) override;
    void SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo) override;
    void SetAntiAlias(bool anti) override;
    void SetFontWeight(const FontWeight& weight) override;
    void SetFontStyle(const Ace::FontStyle& fontStyle) override;
    void SetFontFamilies(const std::vector<std::string>& families) override;
    void SetFontSize(const Dimension& size) override;
    void SetLetterSpacing(const Dimension& letterSpacing) override;
    std::vector<double> GetLineDash() override;
    void SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient) override;
    void SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern) override;
    void SetFillColor(const Color& color, bool colorFlag) override;
    void SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient) override;
    void SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern) override;
    void SetStrokeColor(const Color& color, bool colorFlag) override;
    void DrawImage(const ImageInfo& imageInfo) override;
    void DrawSvgImage(const ImageInfo& imageInfo) override;
    void PutImageData(const Ace::ImageData& imageData) override;
    void CloseImageBitmap(const std::string& src) override;
    std::unique_ptr<Ace::ImageData> GetImageData(const ImageSize& imageSize) override;
    void DrawPixelMap(const ImageInfo& imageInfo) override;
    void SetFilterParam(const std::string& src) override;
    void SetTextDirection(const TextDirection& direction) override;
    std::string GetJsonData(const std::string& path) override;
    std::string ToDataURL(const std::string& dataUrl, double quality) override;
    void SetLineCap(const LineCapStyle& lineCap) override;
    void SetLineJoin(const LineJoinStyle& lineJoin) override;
    void SetMiterLimit(double limit) override;
    void SetLineWidth(double lineWidth) override;
    void SetGlobalAlpha(double alpha) override;
    void SetCompositeType(const CompositeOperation& type) override;
    void SetLineDashOffset(double lineDashOffset) override;
    void SetShadowBlur(double blur) override;
    void SetShadowColor(const Color& color) override;
    void SetShadowOffsetX(double offsetX) override;
    void SetShadowOffsetY(double offsetY) override;
    void SetSmoothingEnabled(bool enabled) override;
    void SetSmoothingQuality(const std::string& quality) override;
    void MoveTo(double x, double y) override;
    void LineTo(double x, double y) override;
    void BezierCurveTo(const BezierCurveParam& param) override;
    void QuadraticCurveTo(const QuadraticCurveParam& param) override;
    void ArcTo(const ArcToParam& param) override;
    void Arc(const ArcParam& param) override;
    void Ellipse(const EllipseParam& param) override;
    void SetFillRuleForPath(const CanvasFillRule& fillRule) override;
    void SetFillRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) override;
    void SetStrokeRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) override;
    void SetStrokeRuleForPath(const CanvasFillRule& fillRule) override;
    void SetClipRuleForPath(const CanvasFillRule& fillRule) override;
    void SetClipRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) override;
    void AddRect(const Rect& rect) override;
    void AddRoundRect(const Rect& rect, const std::vector<double>& radii) override;
    void BeginPath() override;
    void ClosePath() override;
    void Restore() override;
    void CanvasRendererSave() override;
    void CanvasRendererRotate(double angle) override;
    void CanvasRendererScale(double x, double y) override;
    void SetTransform(TransformParam& param, bool lengthFlag) override;
    void ResetTransform() override;
    void Transform(const TransformParam& param) override;
    void Translate(double x, double y) override;
    void SetLineDash(const std::vector<double>& lineDash) override;
    void SetTextAlign(const TextAlign& align) override;
    void SetTextBaseline(const TextBaseline& baseline) override;
    void FillRect(const Rect& rect) override;
    void StrokeRect(const Rect& rect) override;
    void ClearRect(const Rect& rect) override;
    TransformParam GetTransform() override;
    RefPtr<Ace::PixelMap> GetPixelMap(const ImageSize& imageSize) override;
    void GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer) override;
    void SaveLayer() override;
    void RestoreLayer() override;
    void Reset() override;
    TextMetrics GetMeasureTextMetrics(const PaintState& state, const std::string& text) override;
    void SetDensity(double density) override;
    void SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform) override;

    // All interfaces that only the 'OffscreenCanvasRenderingContext2D' has.
    RefPtr<AceType> CreateOffscreenPattern(int width, int height) override;
    size_t GetBitmapSize(RefPtr<AceType> offscreenPattern) override;

private:
    void GetImageData(const std::shared_ptr<Ace::ImageData>& imageData);

    RefPtr<OffscreenCanvasPattern> pattern_;

    ACE_DISALLOW_COPY_AND_MOVE(OffscreenCanvasRenderingContext2DModelNG);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_OFFSCREEN_CANVAS_RENDERING_CONTEXT_2D_MODEL_NG_H
