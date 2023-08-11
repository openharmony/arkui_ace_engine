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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/canvas_renderer/canvas_renderer_type.h"

namespace OHOS::Ace {
class CanvasRendererModel {
public:
    static CanvasRendererModel* GetInstance();
    virtual ~CanvasRendererModel() = default;

    virtual void SetFillText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo) = 0;
    virtual void SetStrokeText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo) = 0;
    virtual void SetAntiAlias(const BaseInfo& baseInfo) = 0;
    virtual void SetFontWeight(const BaseInfo& baseInfo, const FontWeight& weight) = 0;
    virtual void SetFontStyle(const BaseInfo& baseInfo, const FontStyle& fontStyle) = 0;
    virtual void SetFontFamilies(const BaseInfo& baseInfo, const std::vector<std::string>& families) = 0;
    virtual void SetFontSize(const BaseInfo& baseInfo, const Dimension& size) = 0;
    virtual std::vector<double> GetLineDash(const BaseInfo& baseInfo) = 0;
    virtual void SetFillGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient) = 0;
    virtual void SetFillPattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern) = 0;
    virtual void SetFillColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag) = 0;
    virtual void SetStrokeGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient) = 0;
    virtual void SetStrokePattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern) = 0;
    virtual void SetStrokeColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag) = 0;
    virtual void DrawImage(const BaseInfo& baseInfo, const ImageInfo& imageInfo) = 0;
    virtual void PutImageData(const BaseInfo& baseInfo, const ImageData& imageData) = 0;
    virtual void CloseImageBitmap(const BaseInfo& baseInfo, const std::string& src) {}
    virtual std::unique_ptr<ImageData> GetImageData(const BaseInfo& baseInfo, const ImageSize& imageSize) = 0;
    virtual void DrawPixelMap(const BaseInfo& baseInfo, const ImageInfo& imageInfo) = 0;
    virtual void SetFilterParam(const BaseInfo& baseInfo, const std::string& src) {}
    virtual void SetTextDirection(const BaseInfo& baseInfo, const TextDirection& direction) {}
    virtual std::string GetJsonData(const BaseInfo& baseInfo, const std::string& path) = 0;
    virtual std::string ToDataURL(const BaseInfo& baseInfo, const std::string& dataUrl, double quality) = 0;
    virtual void SetLineCap(const BaseInfo& baseInfo, const LineCapStyle& lineCap) = 0;
    virtual void SetLineJoin(const BaseInfo& baseInfo, const LineJoinStyle& lineJoin) = 0;
    virtual void SetMiterLimit(const BaseInfo& baseInfo, double limit) = 0;
    virtual void SetLineWidth(const BaseInfo& baseInfo, double lineWidth) = 0;
    virtual void SetGlobalAlpha(const BaseInfo& baseInfo, double alpha) = 0;
    virtual void SetCompositeType(const BaseInfo& baseInfo, const CompositeOperation& type) = 0;
    virtual void SetLineDashOffset(const BaseInfo& baseInfo, double lineDashOffset) = 0;
    virtual void SetShadowBlur(const BaseInfo& baseInfo, double blur) = 0;
    virtual void SetShadowColor(const BaseInfo& baseInfo, const Color& color) = 0;
    virtual void SetShadowOffsetX(const BaseInfo& baseInfo, double offsetX) = 0;
    virtual void SetShadowOffsetY(const BaseInfo& baseInfo, double offsetY) = 0;
    virtual void SetSmoothingEnabled(const BaseInfo& baseInfo, bool enabled) = 0;
    virtual void SetSmoothingQuality(const BaseInfo& baseInfo, const std::string& quality) = 0;
    virtual void MoveTo(const BaseInfo& baseInfo, double x, double y) = 0;
    virtual void LineTo(const BaseInfo& baseInfo, double x, double y) = 0;
    virtual void BezierCurveTo(const BaseInfo& baseInfo, const BezierCurveParam& param) = 0;
    virtual void QuadraticCurveTo(const BaseInfo& baseInfo, const QuadraticCurveParam& param) = 0;
    virtual void ArcTo(const BaseInfo& baseInfo, const ArcToParam& param) = 0;
    virtual void Arc(const BaseInfo& baseInfo, const ArcParam& param) = 0;
    virtual void Ellipse(const BaseInfo& baseInfo, const EllipseParam& param) = 0;
    virtual void SetFillRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) = 0;
    virtual void SetFillRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) = 0;
    virtual void SetStrokeRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) = 0;
    virtual void SetStrokeRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) = 0;
    virtual void SetClipRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule) = 0;
    virtual void SetClipRuleForPath2D(const BaseInfo& baseInfo, const CanvasFillRule& fillRule,
        const RefPtr<CanvasPath2D>& path) = 0;
    virtual void AddRect(const BaseInfo& baseInfo, const Rect& rect) = 0;
    virtual void BeginPath(const BaseInfo& baseInfo) = 0;
    virtual void ClosePath(const BaseInfo& baseInfo) = 0;
    virtual void Restore(const BaseInfo& baseInfo) = 0;
    virtual void CanvasRendererSave(const BaseInfo& baseInfo) = 0;
    virtual void CanvasRendererRotate(const BaseInfo& baseInfo, double angle) = 0;
    virtual void CanvasRendererScale(const BaseInfo& baseInfo, double x, double y) = 0;
    virtual void SetTransform(const BaseInfo& baseInfo, TransformParam& param, bool lengthFlag) = 0;
    virtual void ResetTransform(const BaseInfo& baseInfo) = 0;
    virtual void Transform(const BaseInfo& baseInfo, const TransformParam& param) = 0;
    virtual void Translate(const BaseInfo& baseInfo, double x, double y) = 0;
    virtual void SetLineDash(const BaseInfo& baseInfo, const std::vector<double>& lineDash) = 0;
    virtual void SetTextAlign(const BaseInfo& baseInfo, const TextAlign& align) = 0;
    virtual void SetTextBaseline(const BaseInfo& baseInfo, const TextBaseline& baseline) = 0;
    virtual double GetMeasureTextWidth(const BaseInfo& baseInfo, const std::string& text) = 0;
    virtual double GetMeasureTextHeight(const BaseInfo& baseInfo, const std::string& text) = 0;
    virtual void FillRect(const BaseInfo& baseInfo, const Rect& rect) = 0;
    virtual void StrokeRect(const BaseInfo& baseInfo, const Rect& rect) = 0;
    virtual void ClearRect(const BaseInfo& baseInfo, const Rect& rect) = 0;
    virtual void DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo) {}
    virtual TransformParam GetTransform(const BaseInfo& baseInfo)
    {
        TransformParam param;
        return param;
    }

private:
    static std::unique_ptr<CanvasRendererModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CANVAS_RENDERER_CANVAS_RENDERER_MODEL_H
