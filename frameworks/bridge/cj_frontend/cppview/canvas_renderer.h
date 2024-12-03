/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_RENDERER_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_RENDERER_H

#include "ffi_remote_data.h"
#include "pixel_map_impl.h"

#include "base/memory/referenced.h"
#include "bridge/cj_frontend/cppview/canvas_gradient.h"
#include "bridge/cj_frontend/cppview/canvas_path.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/common/utils/utils.h"
#include "core/components/custom_paint/custom_paint_component.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

namespace OHOS::Ace::Framework {

struct Metrics {
    double width;
    double height;
};

class ACE_EXPORT NativeCanvasRenderer : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeCanvasRenderer, OHOS::FFI::FFIData)
public:
    explicit NativeCanvasRenderer(bool antialias);
    ~NativeCanvasRenderer() override;

    void SetCanvasPattern(const RefPtr<AceType>& canvas);
    void SetAntiAlias();

    static RefPtr<CanvasPath2D> MakePath2D(const std::string& capStr);

    void SetFillStyle(const Color& color);
    void SetFillStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient);
    void SetLineWidth(const double lineWidth);
    void SetStrokeStyle(const Color& color);
    void SetStrokeStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient);
    void SetLineCap(const LineCapStyle lineCap);
    void SetLineJoin(const LineJoinStyle lineJoin);
    void SetMiterLimit(double limit);
    void SetFont(const FontStyle style, const std::string& weight, const Dimension& size, const std::string& family);
    void SetTextAlign(const TextAlign align);
    void SetTextBaseline(const TextBaseline baseline);
    void SetGlobalAlpha(double alpha);
    void SetLineDash(std::vector<double>& lineDash);
    void SetLineDashOffset(double lineDashOffset);
    void SetGlobalCompositeOperation(const CompositeOperation type);
    void SetShadowBlur(double blur);
    void SetShadowColor(const Color& color);
    void SetShadowOffsetX(double offsetX);
    void SetShadowOffsetY(double offsetY);
    void SetImageSmoothingEnabled(bool enabled);
    void SetImageSmoothingQuality(const std::string& quality);
    void RestoreLayer();
    void SaveLayer();
    void SetFilter(const std::string& value);
    double GetWidth();
    double GetHeight();
    void FillRect(const Rect& rect);
    void StrokeRect(const Rect& rect);
    void ClearRect(const Rect& rect);
    void FillText(double x, double y, const std::string& text);
    void StrokeText(double x, double y, const std::string& text);
    Metrics MeasureText(const std::string& text);
    void Stroke();
    void Stroke(const sptr<NativeCanvasPath>& canvasPath);
    void BeginPath();
    void MoveTo(double x, double y);
    void LineTo(double x, double y);
    void ClosePath();
    void BezierCurveTo(const BezierCurveParam& param);
    void QuadraticCurveTo(const QuadraticCurveParam& param);
    void Arc(const ArcParam& param);
    void ArcTo(const ArcToParam& param);
    void Ellipse(const EllipseParam& param);
    void NormalRect(const Rect& rect);
    void Fill();
    void Clip();
    void Rotate(double angle);
    void Scale(double x, double y);
    void Transform(const TransformParam& param);
    void SetTransform(TransformParam param);
    void Translate(double x, double y);
    void Restore();
    void Save();
    int64_t CreateLinearGradient(double x0, double y0, double x1, double y1);
    int64_t CreateRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
    void DrawImage(const CanvasImage& image);
    void DrawImage(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, const CanvasImage& image);
    std::unique_ptr<ImageData> GetImageData(double fLeft, double fTop, double fWidth, double fHeight);
    int64_t GetPixelMap(double left, double top, double width, double height);

private:
    bool antialias_ = false;
    bool isInitializeShadow_ = false;

    RefPtr<AceType> canvasPattern_;
    RefPtr<RenderingContext2DModel> renderingContext2DModel_;

    PaintState paintState_;
    TextStyle style_;
    ImageData imageData_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_RENDERER_H
