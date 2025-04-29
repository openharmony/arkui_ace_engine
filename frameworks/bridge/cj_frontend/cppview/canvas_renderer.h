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

#include <cstdint>
#include <string>

#include "ffi_remote_data.h"
#include "pixel_map_impl.h"

#include "base/memory/referenced.h"
#include "bridge/cj_frontend/cppview/canvas_gradient.h"
#include "bridge/cj_frontend/cppview/canvas_image_data.h"
#include "bridge/cj_frontend/cppview/canvas_path.h"
#include "bridge/cj_frontend/cppview/matrix2d.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/custom_paint/custom_paint_component.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"

namespace OHOS::Ace::Framework {

class NativeCanvasPattern;
class NativeCanvasPath;

struct RenderImage {
    CanvasUnit unit = CanvasUnit::DEFAULT;
    double width_ = 0;
    double height_ = 0;
    std::string src;
    std::shared_ptr<ImageData> imageData;
    int64_t pixMapID = -1;
};

struct Metrics {
    double width;
    double height;
    double actualBoundingBoxLeft;
    double actualBoundingBoxRight;
    double actualBoundingBoxAscent;
    double actualBoundingBoxDescent;
    double alphabeticBaseline;
    double emHeightAscent;
    double emHeightDescent;
    double fontBoundingBoxAscent;
    double fontBoundingBoxDescent;
    double hangingBaseline;
    double ideographicBaseline;
};

class ACE_EXPORT NativeCanvasRenderer : public OHOS::FFI::FFIData, public Referenced {
    DECL_TYPE(NativeCanvasRenderer, OHOS::FFI::FFIData)
public:
    explicit NativeCanvasRenderer(bool antialias);
    NativeCanvasRenderer();
    ~NativeCanvasRenderer() override;

    void SetCanvasPattern(const RefPtr<AceType>& canvas);
    void SetAntiAlias();

    static RefPtr<CanvasPath2D> MakePath2D(const std::string& capStr);

    void SetFillStyle(const Color& color);
    void SetFillStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient);
    void SetFillStyle(const sptr<NativeCanvasPattern>& nativeCanvasPattern);
    void SetLineWidth(const double lineWidth);
    void SetStrokeStyle(const Color& color);
    void SetStrokeStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient);
    void SetStrokeStyle(const sptr<NativeCanvasPattern>& nativeCanvasPattern);
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
    double GetHeight();
    void SetDirection(const std::string& directionStr);
    void SetDensity();
    int64_t GetTransform();
    int64_t CreateImageData(const double height, const double width);
    int64_t CreateImageData(const sptr<NativeImageData> imageData);
    void PutImageData(const sptr<NativeImageData> imageData, const double dx, const double dy, const double dirtyX,
        const double dirtyY, const double dirtyWidth, const double dirtyHeight);
    void PutImageData(const sptr<NativeImageData> imageData, const double dx, const double dy);

    void FillRect(const Rect& rect);
    void StrokeRect(const Rect& rect);
    void ClearRect(const Rect& rect);
    void FillText(double x, double y, const std::string& text);
    void FillText(double x, double y, const std::string& text, double maxWidth);
    void StrokeText(double x, double y, const std::string& text);
    void StrokeText(double x, double y, const std::string& text, double maxWidth);
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
    void Fill(const std::string& ruleStr);
    void Fill(const sptr<NativeCanvasPath>& canvasPath, const std::string& ruleStr);
    void Clip();
    void Clip(const std::string& ruleStr);
    void Clip(const sptr<NativeCanvasPath>& canvasPath, const std::string& ruleStr);
    void Rotate(double angle);
    void Scale(double x, double y);
    void Transform(const TransformParam& param);
    void ResetTransform();
    void SetTransform(TransformParam param);
    void SetTransform(unsigned int id, const TransformParam& transform);
    void SetTransformByMatrix(const sptr<NativeMatrix2d>& matrix2d);
    void Translate(double x, double y);
    void Restore();
    void Save();
    void Reset();
    int64_t CreateLinearGradient(double x0, double y0, double x1, double y1);
    int64_t CreateRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
    int64_t CreateConicGradient(const double startAngle, const double x, const double y);
    void DrawImage(const CanvasImage& image);
    void DrawImage(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, const CanvasImage& image);
    std::unique_ptr<ImageData> GetImageData(double fLeft, double fTop, double fWidth, double fHeight);
    int64_t GetNativeImageData(const double left, const double top, const double width, const double height);
    int64_t GetPixelMap(double left, double top, double width, double height);
    std::string ToDataURL(const std::string& dataUrl, double quality);
    std::string GetJsonData(const std::string& path);
    std::vector<double> GetLineDash();
    int64_t CreatePattern(int64_t bitMapId, const std::string& repeat);
    void SetPixelMap(const RefPtr<OHOS::Ace::PixelMap>& pixelMap);
    std::string ToDataUrl(const std::string type, const double quality);
    double GetWidth();
    void TransferFromImageBitmap(const sptr<CJRenderImage> cjImage);

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    void SetAntiAlias(bool antialias)
    {
        antialias_ = antialias;
    }

    inline double GetDensity(bool useSystemDensity = false)
    {
        if (useSystemDensity) {
            return !NearZero(density_) ? density_ : 1.0;
        } else {
            return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density_)) ? density_ : 1.0;
        }
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    void SetOffscreenPattern(const RefPtr<AceType>& offscreenCanvas)
    {
        canvasPattern_ = offscreenCanvas;
        renderingContext2DModel_->SetPattern(offscreenCanvas);
        if (isOffscreenInitializeShadow_) {
            return;
        }
        isOffscreenInitializeShadow_ = true;
        renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
    }

protected:
    bool antialias_ = false;

    RefPtr<AceType> canvasPattern_;
    RefPtr<RenderingContext2DModel> renderingContext2DModel_;

    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

private:
    double density_ = 1.0;
    std::vector<PaintState> savePaintState_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
    PaintState paintState_;
    TextStyle style_;
    ImageData imageData_;
    bool isOffscreenInitializeShadow_ = false;
    bool isInitializeShadow_ = false;
    static std::unordered_map<int32_t, std::shared_ptr<Pattern>> pattern_;
    std::shared_ptr<Pattern> GetPatternPtr(int32_t id);
    static unsigned int patternCount_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_RENDERER_H
