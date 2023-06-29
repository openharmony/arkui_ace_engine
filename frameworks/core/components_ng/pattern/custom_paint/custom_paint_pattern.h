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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_event_hub.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class OffscreenCanvasPattern;
class RenderingContext2DModifier;
// CustomPaintPattern is the base class for custom paint render node to perform paint canvas.
class ACE_EXPORT CustomPaintPattern : public Pattern {
    DECLARE_ACE_TYPE(CustomPaintPattern, Pattern);

public:
    CustomPaintPattern() = default;
    ~CustomPaintPattern() override = default;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::INCREMENTAL_CANVAS };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CustomPaintLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CustomPaintEventHub>();
    }

    void SetCanvasSize(std::optional<SizeF> canvasSize)
    {
        canvasSize_ = canvasSize;
    }

    void SetAntiAlias(bool isEnabled);

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
    double MeasureText(const std::string& text, const PaintState& state);
    double MeasureTextHeight(const std::string& text, const PaintState& state);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);

    void DrawImage(const Ace::CanvasImage& image, double width, double height);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void PutImageData(const Ace::ImageData& imageData);
    void TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvasPattern);
    void CloseImageBitmap(const std::string& src);

    void UpdateFillColor(const Color& color);
    void UpdateFillRuleForPath(const CanvasFillRule rule);
    void UpdateFillRuleForPath2D(const CanvasFillRule rule);
    double GetWidth();
    double GetHeight();

    const LineDashParam& GetLineDash() const;
    void UpdateLineDash(const std::vector<double>& segments);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    void SetTransform(const TransformParam& param);
    void ResetTransform();
    void Transform(const TransformParam& param);
    void Translate(double x, double y);
    std::string ToDataURL(const std::string& args);
    std::string GetJsonData(const std::string& path);

    void UpdateGlobalAlpha(double alpha);
    void UpdateCompositeOperation(CompositeOperation type);
    void UpdateSmoothingEnabled(bool enabled);
    void UpdateSmoothingQuality(const std::string& quality);
    void UpdateLineCap(LineCapStyle cap);
    void UpdateLineDashOffset(double dash);
    void UpdateLineWidth(double width);
    void UpdateMiterLimit(double limit);
    void UpdateShadowBlur(double blur);
    void UpdateShadowOffsetX(double offsetX);
    void UpdateShadowOffsetY(double offsetY);
    void UpdateTextAlign(TextAlign align);
    void UpdateTextBaseline(TextBaseline baseline);
    void UpdateStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern);
    void UpdateStrokeColor(const Color& color);
    void UpdateFontWeight(FontWeight weight);
    void UpdateFontStyle(FontStyle style);
    void UpdateFontFamilies(const std::vector<std::string>& families);
    void UpdateFontSize(const Dimension& size);
    void UpdateLineJoin(LineJoinStyle join);
    void UpdateFillGradient(const Ace::Gradient& gradient);
    void UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern);
    void UpdateShadowColor(const Color& color);
    void UpdateStrokeGradient(const Ace::Gradient& grad);
    void SetTextDirection(TextDirection direction);
    void SetFilterParam(const std::string& filterStr);
    TransformParam GetTransform() const;

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    RefPtr<CanvasPaintMethod> paintMethod_;
    std::optional<SizeF> canvasSize_;
    bool isCanvasInit_ = false;

    RefPtr<RenderingContext2DModifier> contentModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(CustomPaintPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H
