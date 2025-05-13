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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_RENDERING_CONTEXT_2D_MODEL_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_RENDERING_CONTEXT_2D_MODEL_H

#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/canvas/canvas_renderer_type.h"
#include <stdint.h>

namespace OHOS::Ace {
class RenderingContext2DModel : public AceType {
    DECLARE_ACE_TYPE(RenderingContext2DModel, AceType)

public:
    RenderingContext2DModel()
    {
        apiVersion_ = Container::GetCurrentApiTargetVersion();
    }
    virtual ~RenderingContext2DModel() = default;

    virtual void SetPattern(RefPtr<AceType> pattern) = 0;
    // All interfaces that both 'CanvasRenderingContext2D' and 'OffscreenCanvasRenderingContext2D' have.
    virtual void SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo) = 0;
    virtual void SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo) = 0;
    virtual void SetAntiAlias(bool anti) = 0;
    virtual void SetFontWeight(const FontWeight& weight) = 0;
    virtual void SetFontStyle(const FontStyle& fontStyle) = 0;
    virtual void SetFontFamilies(const std::vector<std::string>& families) = 0;
    virtual void SetFontSize(const Dimension& size) = 0;
    virtual void SetLetterSpacing(const Dimension& letterSpacing) {};
    virtual std::vector<double> GetLineDash() = 0;
    virtual void SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient) = 0;
    virtual void SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern) = 0;
    virtual void SetFillColor(const Color& color, bool colorFlag) = 0;
    virtual void SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient) = 0;
    virtual void SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern) = 0;
    virtual void SetStrokeColor(const Color& color, bool colorFlag) = 0;
    virtual void DrawImage(const ImageInfo& imageInfo) = 0;
    virtual void DrawSvgImage(const ImageInfo& imageInfo) {}
    virtual void PutImageData(const ImageData& imageData) = 0;
    virtual void CloseImageBitmap(const std::string& src) {}
    virtual std::unique_ptr<ImageData> GetImageData(const ImageSize& imageSize) = 0;
    virtual void DrawPixelMap(const ImageInfo& imageInfo) = 0;
    virtual void SetFilterParam(const std::string& src) {}
    virtual void SetTextDirection(const TextDirection& direction) {}
    virtual std::string GetJsonData(const std::string& path) = 0;
    virtual std::string ToDataURL(const std::string& dataUrl, double quality) = 0;
    virtual void SetLineCap(const LineCapStyle& lineCap) = 0;
    virtual void SetLineJoin(const LineJoinStyle& lineJoin) = 0;
    virtual void SetMiterLimit(double limit) = 0;
    virtual void SetLineWidth(double lineWidth) = 0;
    virtual void SetGlobalAlpha(double alpha) = 0;
    virtual void SetCompositeType(const CompositeOperation& type) = 0;
    virtual void SetLineDashOffset(double lineDashOffset) = 0;
    virtual void SetShadowBlur(double blur) = 0;
    virtual void SetShadowColor(const Color& color) = 0;
    virtual void SetShadowOffsetX(double offsetX) = 0;
    virtual void SetShadowOffsetY(double offsetY) = 0;
    virtual void SetSmoothingEnabled(bool enabled) = 0;
    virtual void SetSmoothingQuality(const std::string& quality) = 0;
    virtual void MoveTo(double x, double y) = 0;
    virtual void LineTo(double x, double y) = 0;
    virtual void BezierCurveTo(const BezierCurveParam& param) = 0;
    virtual void QuadraticCurveTo(const QuadraticCurveParam& param) = 0;
    virtual void ArcTo(const ArcToParam& param) = 0;
    virtual void Arc(const ArcParam& param) = 0;
    virtual void Ellipse(const EllipseParam& param) = 0;
    virtual void SetFillRuleForPath(const CanvasFillRule& fillRule) = 0;
    virtual void SetFillRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) = 0;
    virtual void SetStrokeRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) = 0;
    virtual void SetStrokeRuleForPath(const CanvasFillRule& fillRule) = 0;
    virtual void SetClipRuleForPath(const CanvasFillRule& fillRule) = 0;
    virtual void SetClipRuleForPath2D(const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path) = 0;
    virtual void AddRect(const Rect& rect) = 0;
    virtual void AddRoundRect(const Rect& rect, const std::vector<double>& radii) {};
    virtual void BeginPath() = 0;
    virtual void ClosePath() = 0;
    virtual void Restore() = 0;
    virtual void CanvasRendererSave() = 0;
    virtual void CanvasRendererRotate(double angle) = 0;
    virtual void CanvasRendererScale(double x, double y) = 0;
    virtual void SetTransform(TransformParam& param, bool lengthFlag) = 0;
    virtual void ResetTransform() = 0;
    virtual void Transform(const TransformParam& param) = 0;
    virtual void Translate(double x, double y) = 0;
    virtual void SetLineDash(const std::vector<double>& lineDash) = 0;
    virtual void SetTextAlign(const TextAlign& align) = 0;
    virtual void SetTextBaseline(const TextBaseline& baseline) = 0;
    virtual double GetMeasureTextWidth(const PaintState& state, const std::string& text) { return 0.0; };
    virtual double GetMeasureTextHeight(const PaintState& state, const std::string& text) { return 0.0; };
    virtual void FillRect(const Rect& rect) = 0;
    virtual void StrokeRect(const Rect& rect) = 0;
    virtual void ClearRect(const Rect& rect) = 0;
    virtual void DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo) {}
    virtual RefPtr<Ace::PixelMap> GetPixelMap(const ImageSize& imageSize) = 0;
    virtual void GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer) = 0;
    virtual void SaveLayer() {};
    virtual void RestoreLayer() {};
    virtual void Reset() {};
    virtual void SetDensity(double density) {};
    virtual TextMetrics GetMeasureTextMetrics(const PaintState& state, const std::string& text)
    {
        return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    }

    virtual TransformParam GetTransform()
    {
        TransformParam param;
        return param;
    }

    virtual void SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
    {
        pattern->SetScaleX(transform.scaleX);
        pattern->SetScaleY(transform.scaleY);
        pattern->SetSkewX(transform.skewX);
        pattern->SetSkewY(transform.skewY);
        pattern->SetTranslateX(transform.translateX);
        pattern->SetTranslateY(transform.translateY);
    }

protected:
    int32_t apiVersion_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(RenderingContext2DModel);
};

class CanvasRenderingContext2DModel : public RenderingContext2DModel {
    DECLARE_ACE_TYPE(CanvasRenderingContext2DModel, RenderingContext2DModel)

public:
    CanvasRenderingContext2DModel() = default;
    virtual ~CanvasRenderingContext2DModel() = default;
    virtual int32_t GetId() { return -1; };
    virtual void Release() {};
    virtual void SetOnAttach(std::function<void()>&& callback) {};
    virtual void SetOnDetach(std::function<void()>&& callback) {};
    virtual void GetWidth(double& width) = 0;
    virtual void GetHeight(double& height) = 0;
    virtual void SetTransferFromImageBitmap(RefPtr<AceType> offscreenCPattern) {};
#ifdef PIXEL_MAP_SUPPORTED
    virtual void TransferFromImageBitmap(const RefPtr<AceType>& pixelMap) {};
#else
    virtual void TransferFromImageBitmap(const std::shared_ptr<Ace::ImageData>& imageData) {};
#endif
    virtual void StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed) {};
    virtual void StopImageAnalyzer() {};

    ACE_DISALLOW_COPY_AND_MOVE(CanvasRenderingContext2DModel);
protected:
    std::function<void()> onContext2DAttach_;
    std::function<void()> onContext2DDetach_;
};

class OffscreenCanvasRenderingContext2DModel : public RenderingContext2DModel {
    DECLARE_ACE_TYPE(OffscreenCanvasRenderingContext2DModel, RenderingContext2DModel)

public:
    OffscreenCanvasRenderingContext2DModel() = default;
    virtual ~OffscreenCanvasRenderingContext2DModel() = default;
    virtual RefPtr<AceType> CreateOffscreenPattern(int width, int height) = 0;
    virtual size_t GetBitmapSize(RefPtr<AceType> offscreenPattern)
    {
        return 0;
    }

    ACE_DISALLOW_COPY_AND_MOVE(OffscreenCanvasRenderingContext2DModel);
};
} // namespace OHOS::Ace
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CANVAS_RENDERING_CONTEXT_2D_MODEL_H
