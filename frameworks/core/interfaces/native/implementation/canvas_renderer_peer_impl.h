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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H

#include "core/components_ng/pattern/canvas/rendering_context_2d_model.h"
#include "canvas_path_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const auto IMAGE_FLAG_0 = 0;
const auto IMAGE_FLAG_1 = 1;
const auto IMAGE_FLAG_2 = 2;
class CanvasRendererPeerImpl : public CanvasPathPeerImpl {
public:
    enum class SizeParam {
        TWO_ARGS, FOUR_ARGS, SIX_ARGS, EIGHT_ARGS
    };
    struct DrawImageParam {
        double sx;
        double sy;
        double sWidth;
        double sHeight;
        double dx;
        double dy;
        double dWidth;
        double dHeight;
        SizeParam size;
    };
    struct PutImageDataParam {
        std::optional<Dimension> x;
        std::optional<Dimension> y;
        std::optional<Dimension> dirtyX;
        std::optional<Dimension> dirtyY;
        std::optional<Dimension> dirtyWidth;
        std::optional<Dimension> dirtyHeight;
        SizeParam size;
    };
    struct LinearGradientParam {
        double x0;
        double y0;
        double x1;
        double y1;
    };
    struct RadialGradientParam {
        double x0;
        double y0;
        double r0;
        double x1;
        double y1;
        double r1;
    };
    struct ConicGradientParam {
        double x;
        double y;
        double startAngle;
    };

    CanvasRendererPeerImpl();
    ~CanvasRendererPeerImpl() override;

    static RefPtr<CanvasPath2D> MakePath2D();
    void DrawImage(ImageBitmapPeer* bitmap, const DrawImageParam& params);
    void DrawSvgImage(ImageBitmapPeer* bitmap, const DrawImageParam& params);
    void DrawPixelMap(PixelMapPeer* pixelMap, const DrawImageParam& params);
    void BeginPath();
    void Clip(const std::optional<std::string>& ruleStr);
    void Clip(const std::optional<std::string>& ruleStr, const RefPtr<CanvasPath2D>& path);
    void Fill(const std::optional<std::string>& ruleStr);
    void Fill(const std::optional<std::string>& ruleStr, const RefPtr<CanvasPath2D>& path);
    void Stroke();
    void Stroke(const RefPtr<CanvasPath2D>& path);
    std::shared_ptr<OHOS::Ace::Gradient> CreateLinearGradient(double x0, double y0, double x1, double y1);
    void CreatePattern(
        ImageBitmapPeer* bitmap, CanvasPatternPeer* canvasPattern, std::optional<std::string>& repetition);
    std::shared_ptr<OHOS::Ace::Gradient> CreateRadialGradient(const RadialGradientParam& params);
    std::shared_ptr<OHOS::Ace::Gradient> CreateConicGradient(double x, double y, double startangle);
    void CreateImageData(
        std::vector<uint8_t>& vbuffer, double fWidth, double fHeight, uint32_t& width, uint32_t& height);
    void CreateImageData(
        std::vector<uint8_t>& vbuffer, const Ace::ImageData& imageData, uint32_t& width, uint32_t& height);
    void GetImageData(std::vector<uint8_t>& vbuffer, Ace::ImageSize& imageSize, uint32_t& width, uint32_t& height);
    RefPtr<Ace::PixelMap> GetPixelMap(const double x, const double y, const double width, const double height);
    void PutImageData(Ace::ImageData& src, const PutImageDataParam& params);
    std::vector<double> GetLineDash();
    void SetLineDash(const std::vector<double>& segments);
    void ClearRect(const double x, const double y, const double width, const double height);
    void FillRect(const double x, const double y, const double width, const double height);
    void StrokeRect(const double x, const double y, const double width, const double height);
    void Restore();
    void Save();
    void FillText(const std::string& text, double x, double y, const std::optional<float>& optWidth);
    void MeasureText(Ace::TextMetrics& textMetrics, const std::string& text);
    void StrokeText(const std::string& text, double x, double y, const std::optional<float>& optWidth);
    void GetTransform(Matrix2DPeer* matrix);
    void ResetTransform();
    void Rotate(double angle);
    void Scale(double x, double y);
    void SetTransform(TransformParam& param);
    void SetTransform(const std::optional<Matrix2DPeer*>& optMatrix);
    void SetTransform(unsigned int id, const TransformParam& transform);
    void Transform(TransformParam& param);
    void Translate(double x, double y);
    void SetPixelMap(const RefPtr<Ace::PixelMap>& pixelMap);
    void TransferFromImageBitmap(ImageBitmapPeer* bitmap);
    void SaveLayer();
    void RestoreLayer();
    void Reset();
    void SetGlobalAlpha(double alpha);
    void SetGlobalCompositeOperation(const std::string& compositeStr);
    void SetFillStyle(const std::string& colorStr);
    void SetFillStyle(const uint32_t colorNum);
    void SetFillStyle(const std::shared_ptr<Ace::Gradient>& gradient);
    void SetFillStyle(const int32_t id);
    void SetStrokeStyle(const std::string& colorStr);
    void SetStrokeStyle(const uint32_t colorNum);
    void SetStrokeStyle(const std::shared_ptr<Ace::Gradient>& gradient);
    void SetStrokeStyle(const int32_t id);
    void SetFilter(const std::string& filterStr);
    void SetImageSmoothingEnabled(bool enabled);
    void SetImageSmoothingQuality(const std::string& quality);
    void SetLineCap(const std::string& capStr);
    void SetLineDashOffset(double lineDashOffset);
    void SetLineJoin(const std::string& joinStr);
    void SetLineWidth(double lineWidth);
    void SetMiterLimit(double limit);
    void SetShadowBlur(double blur);
    void SetShadowColor(const std::string& colorStr);
    void SetShadowOffsetX(double offsetX);
    void SetShadowOffsetY(double offsetY);
    void SetTextDirection(const std::string& directionStr);
    void SetFont(std::string fontStr);
    void SetTextAlign(const std::string& alignStr);
    void SetTextBaseline(const std::string& baselineStr);

    // inheritance
    void ResetPaintState();
    void SetAntiAlias();
    void SetDensity();
    std::string ToDataURL(const std::optional<std::string>& optType, const std::optional<float>& optQuality);

    void SetCanvasPattern(const RefPtr<AceType>& canvas)
    {
        CHECK_NULL_VOID(renderingContext2DModel_);
        CHECK_NULL_VOID(canvas);
        renderingContext2DModel_->SetPattern(canvas);
        if (isInitializeShadow_) {
            return;
        }
        isInitializeShadow_ = true;
        renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
    }

    void SetOffscreenPattern(const RefPtr<AceType>& offscreenCanvas)
    {
        offscreenPattern_ = offscreenCanvas;
        CHECK_NULL_VOID(renderingContext2DModel_);
        CHECK_NULL_VOID(offscreenCanvas);
        renderingContext2DModel_->SetPattern(offscreenCanvas);
        if (isOffscreenInitializeShadow_) {
            return;
        }
        isOffscreenInitializeShadow_ = true;
        renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
    }

    void SetAnti(bool anti)
    {
        anti_ = anti;
    }

    bool GetAnti()
    {
        return anti_;
    }

    double GetDensity(bool useSystemDensity = false)
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

    // test support
    void SetRenderingContext2DModel(const RefPtr<OHOS::Ace::RenderingContext2DModel>& renderingContext2DModel)
    {
        renderingContext2DModel_ = renderingContext2DModel;
    }

protected:
    OHOS::Ace::RefPtr<OHOS::Ace::RenderingContext2DModel> renderingContext2DModel_;
    OHOS::Ace::RefPtr<OHOS::Ace::AceType> offscreenPattern_;
    bool anti_ = false;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

private:
    void ExtractInfoToImage(Ace::CanvasImage& image, const DrawImageParam& params, bool isImage);
    Dimension GetDimensionValue(const std::string& str);
    Dimension GetDimensionValue(const Dimension& dimension);
    Ace::Pattern GetPattern(unsigned int id);
    std::shared_ptr<Ace::Pattern> GetPatternPtr(int32_t id);
    void ParseImageData(Ace::ImageData& imageData, const PutImageDataParam& params);

    static std::unordered_map<int32_t, std::shared_ptr<Ace::Pattern>> pattern_;
    static unsigned int patternCount_;
    double density_ = 1.0;
    std::vector<OHOS::Ace::PaintState> savePaintState_;
    OHOS::Ace::PaintState paintState_;
    bool isInitializeShadow_ = false;
    bool isOffscreenInitializeShadow_ = false;
    int32_t densityCallbackId_ = 0;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
