/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CANVAS_RENDERER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CANVAS_RENDERER_MODEL_IMPL_H

#include "core/components_ng/pattern/canvas_renderer/canvas_renderer_model.h"

namespace OHOS::Ace::Framework {
class CanvasRendererModelImpl : public OHOS::Ace::CanvasRendererModel {
public:
    void SetFillText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo) override;
    void SetStrokeText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo) override;
    void SetAntiAlias(const BaseInfo& baseInfo) override;
    void SetFontWeight(const BaseInfo& baseInfo, const FontWeight& weight) override;
    void SetFontStyle(const BaseInfo& baseInfo, const FontStyle& fontStyle) override;
    void SetFontFamilies(const BaseInfo& baseInfo, const std::vector<std::string>& families) override;
    void SetFontSize(const BaseInfo& baseInfo, const Dimension& size) override;
    std::vector<double> GetLineDash(const BaseInfo& baseInfo) override;
    void SetFillGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient) override;
    void SetFillPattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern) override;
    void SetFillColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag) override;
    void SetStrokeGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient) override;
    void SetStrokePattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern) override;
    void SetStrokeColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag) override;
    void DrawImage(const BaseInfo& baseInfo, const ImageInfo& imageInfo) override;
    void PutImageData(const BaseInfo& baseInfo, const ImageData& imageData) override;
    std::unique_ptr<ImageData> GetImageData(const BaseInfo& baseInfo, const ImageSize& imageSize) override;
    void DrawPixelMap(const BaseInfo& baseInfo, const ImageInfo& imageInfo) override;
    std::string GetJsonData(const BaseInfo& baseInfo, const std::string& path) override;
    std::string ToDataURL(const BaseInfo& baseInfo, const std::string& dataUrl, double quality) override;
    void SetLineCap(const BaseInfo& baseInfo, const LineCapStyle& lineCap) override;
    void SetLineJoin(const BaseInfo& baseInfo, const LineJoinStyle& lineJoin) override;
    void SetMiterLimit(const BaseInfo& baseInfo, double limit) override;
    void SetLineWidth(const BaseInfo& baseInfo, double lineWidth) override;
    void SetGlobalAlpha(const BaseInfo& baseInfo, double alpha) override;
    void SetCompositeType(const BaseInfo& baseInfo, const CompositeOperation& type) override;
    void SetLineDashOffset(const BaseInfo& baseInfo, double lineDashOffset) override;
    void SetShadowBlur(const BaseInfo& baseInfo, double blur) override;
    void SetShadowColor(const BaseInfo& baseInfo, const Color& color) override;
    void SetShadowOffsetX(const BaseInfo& baseInfo, double offsetX) override;
    void SetShadowOffsetY(const BaseInfo& baseInfo, double offsetY) override;
    void SetSmoothingEnabled(const BaseInfo& baseInfo, bool enabled) override;
    void SetSmoothingQuality(const BaseInfo& baseInfo, const std::string& quality) override;
    void MoveTo(const BaseInfo& baseInfo, double x, double y) override;
    void LineTo(const BaseInfo& baseInfo, double x, double y) override;
    void BezierCurveTo(const BaseInfo& baseInfo, const BezierCurveParam& param) override;
    void QuadraticCurveTo(const BaseInfo& baseInfo, const QuadraticCurveParam& param) override;
    void ArcTo(const BaseInfo& baseInfo, const ArcToParam& param) override;
    void Arc(const BaseInfo& baseInfo, const ArcParam& param) override;
    void Ellipse(const BaseInfo& baseInfo, const EllipseParam& param) override;
    void SetFillRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) override;
    void SetFillRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) override;
    void SetStrokeRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) override;
    void SetStrokeRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) override;
    void SetClipRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) override;
    void SetClipRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) override;
    void AddRect(const BaseInfo& baseInfo, const Rect& rect) override;
    void BeginPath(const BaseInfo& baseInfo) override;
    void ClosePath(const BaseInfo& baseInfo) override;
    void Restore(const BaseInfo& baseInfo) override;
    void CanvasRendererSave(const BaseInfo& baseInfo) override;
    void CanvasRendererRotate(const BaseInfo& baseInfo, double angle) override;
    void CanvasRendererScale(const BaseInfo& baseInfo, double x, double y) override;
    void SetTransform(const BaseInfo& baseInfo, TransformParam& param, bool lengthFlag) override;
    void ResetTransform(const BaseInfo& baseInfo) override;
    void Transform(const BaseInfo& baseInfo, const TransformParam& param) override;
    void Translate(const BaseInfo& baseInfo, double x, double y) override;
    void SetLineDash(const BaseInfo& baseInfo, const std::vector<double>& lineDash) override;
    void SetTextAlign(const BaseInfo& baseInfo, const TextAlign& align) override;
    void SetTextBaseline(const BaseInfo& baseInfo, const TextBaseline& baseline) override;
    double GetMeasureTextWidth(const BaseInfo& baseInfo, const std::string& text) override;
    double GetMeasureTextHeight(const BaseInfo& baseInfo, const std::string& text) override;
    void FillRect(const BaseInfo& baseInfo, const Rect& rect) override;
    void StrokeRect(const BaseInfo& baseInfo, const Rect& rect) override;
    void ClearRect(const BaseInfo& baseInfo, const Rect& rect) override;
    void DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo) override;
    RefPtr<Ace::PixelMap> GetPixelMap(const BaseInfo& baseInfo, const ImageSize& imageSize) override;
    void GetImageDataModel(const BaseInfo& baseInfo, const ImageSize& imageSize, uint8_t* buffer) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CANVAS_RENDERER_MODEL_IMPL_H
