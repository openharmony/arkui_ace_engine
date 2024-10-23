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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H

#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "core/components_ng/pattern/canvas/canvas_event_hub.h"
#include "core/components_ng/pattern/canvas/canvas_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
class ImageAnalyzerManager;
}

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class OffscreenCanvasPattern;
class CanvasModifier;
// CanvasPattern is the base class for custom paint render node to perform paint canvas.
class ACE_EXPORT CanvasPattern : public Pattern {
    DECLARE_ACE_TYPE(CanvasPattern, Pattern);

public:
    CanvasPattern() = default;
    ~CanvasPattern() override;

    void SetOnContext2DAttach(std::function<void()>&& callback);
    void SetOnContext2DDetach(std::function<void()>&& callback);

    int32_t GetId() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, -1);
        return host->GetId();
    }

    void AttachRenderContext();
    void DetachRenderContext();
    void OnAttachToMainTree() override;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::INCREMENTAL_CANVAS };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CanvasLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CanvasEventHub>();
    }

    void SetCanvasSize(std::optional<SizeF> canvasSize)
    {
        canvasSize_ = canvasSize;
    }

    bool IsSupportDrawModifier() const override
    {
        return false;
    }

    bool IsAttached() const
    {
        return isAttached_;
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
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);

    void DrawImage(const Ace::CanvasImage& image, double width, double height);
    void DrawSvgImage(RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void GetImageData(const std::shared_ptr<Ace::ImageData>& imageData);
    void PutImageData(const Ace::ImageData& imageData);
#ifdef PIXEL_MAP_SUPPORTED
    void TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap);
#else
    void TransferFromImageBitmap(const Ace::ImageData& imageData);
#endif
    void CloseImageBitmap(const std::string& src);

    void UpdateFillColor(const Color& color);
    void UpdateFillRuleForPath(const CanvasFillRule rule);
    void UpdateFillRuleForPath2D(const CanvasFillRule rule);
    double GetWidth();
    double GetHeight();
    void SetRSCanvasCallback(std::function<void(RSCanvas*, double, double)>& callback);
    void SetInvalidate();

    LineDashParam GetLineDash() const;
    void UpdateLineDash(const std::vector<double>& segments);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    void SetTransform(const TransformParam& param);
    void ResetTransform();
    void Transform(const TransformParam& param);
    void Translate(double x, double y);
    std::string ToDataURL(const std::string& type, double quality);
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
    void SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient);
    void UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern);
    void UpdateShadowColor(const Color& color);
    void SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient);
    void SetTextDirection(TextDirection direction);
    void SetFilterParam(const std::string& filterStr);
    TransformParam GetTransform() const;
    void SetDensity(double density);
    void SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform);
    int32_t GetId();

    void SaveLayer();
    void RestoreLayer();
    void EnableAnalyzer(bool enable);
    void SetImageAIOptions(void* options);
    void StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed);
    void StopImageAnalyzer();
    void Reset();
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override;

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromMainTree() override;
    void FireOnContext2DAttach();
    void FireOnContext2DDetach();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnSizeChanged(const DirtySwapConfig& config, bool needReset);
    void CreateAnalyzerOverlay();
    void DestroyAnalyzerOverlay();
    void UpdateAnalyzerOverlay();
    void ReleaseImageAnalyzer();
    bool IsSupportImageAnalyzerFeature();
    void OnLanguageConfigurationUpdate() override;
    void OnModifyDone() override;
    void UpdateTextDefaultDirection();

    std::function<void()> onContext2DAttach_;
    std::function<void()> onContext2DDetach_;
    RefPtr<CanvasPaintMethod> paintMethod_;
    std::optional<SizeF> canvasSize_;
    SizeF dirtyPixelGridRoundSize_ = { -1, -1 };
    SizeF lastDirtyPixelGridRoundSize_ = { -1, -1 };
    DirtySwapConfig recordConfig_;
    std::shared_ptr<ImageAnalyzerManager> imageAnalyzerManager_;
    bool isEnableAnalyzer_ = false;
    TextDirection currentSetTextDirection_ = TextDirection::INHERIT;
    RefPtr<CanvasModifier> contentModifier_;
    bool isAttached_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(CanvasPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H
