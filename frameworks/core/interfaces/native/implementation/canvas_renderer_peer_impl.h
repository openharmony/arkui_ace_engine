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
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "canvas_path_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const auto IMAGE_FLAG_0 = 0;
const auto IMAGE_FLAG_1 = 1;
const auto IMAGE_FLAG_2 = 2;
enum class ParamType { DEFAULT, INT32, STRING, COLOR, CANVAS_GRADIENT, CANVAS_PATTERN };
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
    void DrawPixelMap(image_PixelMapPeer* pixelMap, const DrawImageParam& params);
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
    void GetImageData(const ImageSize& imageSize, uint8_t* buffer);
    RefPtr<Ace::PixelMap> GetPixelMap(const double x, const double y, const double width, const double height);
    void PutImageData(Ace::ImageData& src, const PutImageDataParam& params);
    void PutImageData(const Ace::ImageData& imageData);
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
    void SetFillStyle(const std::optional<Color>& color);
    void SetFillStyle(const uint32_t colorNum);
    void SetFillStyle(CanvasGradientPeer* gradientPeer);
    void SetFillStyle(CanvasPatternPeer* canvasPatternPeer);
    void SetStrokeStyle(const std::string& colorStr);
    void SetStrokeStyle(const std::optional<Color>& color);
    void SetStrokeStyle(const uint32_t colorNum);
    void SetStrokeStyle(CanvasGradientPeer* gradientPeer);
    void SetStrokeStyle(CanvasPatternPeer* canvasPatternPeer);
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
    void SetLetterSpacing(const std::string& letterSpacing);
    void SetLetterSpacing(const Ace::Dimension& letterSpacing);
    void Path2DArc(const ArcParam& params) override;
    void Path2DArcTo(const ArcToParam& params) override;
    void Path2DBezierCurveTo(const BezierCurveToParam& params) override;
    void Path2DClosePath() override;
    void Path2DEllipse(const EllipseParam& params) override;
    void Path2DLineTo(double x, double y) override;
    void Path2DMoveTo(double x, double y) override;
    void Path2DQuadraticCurveTo(double cpx, double cpy, double x, double y) override;
    void Path2DRect(double x, double y, double width, double height) override;

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

    ParamType GetFillStyleType() const
    {
        return fillStyleType_;
    }

    std::string GetFillStyleString() const
    {
        return fillStyleString_;
    }

    CanvasGradientPeer* GetFillStyleGradient() const
    {
        return fillStyleGradient_;
    }

    CanvasPatternPeer* GetFillStylePattern() const
    {
        return fillStylePattern_;
    }

    ParamType GetStrokeStyleType() const
    {
        return strokeStyleType_;
    }

    std::string GetStrokeStyleString() const
    {
        return strokeStyleString_;
    }

    CanvasGradientPeer* GetStrokeStyleGradient() const
    {
        return strokeStyleGradient_;
    }

    CanvasPatternPeer* GetStrokeStylePattern() const
    {
        return strokeStylePattern_;
    }

    const Dimension& GetLetterSpacing() const
    {
        return letterSpacing_;
    }

    double GetGlobalAlpha() const
    {
        return globalAlpha_;
    }

    std::string GetGlobalCompositeOperation() const
    {
        return globalCompositeOperation_;
    }

    std::string GetFilter() const
    {
        return filter_;
    }

    bool GetImageSmoothingEnabled() const
    {
        return imageSmoothingEnabled_;
    }

    std::string GetImageSmoothingQuality() const
    {
        return imageSmoothingQuality_;
    }

    std::string GetLineCap() const
    {
        return lineCap_;
    }

    double GetLineDashOffset() const
    {
        return lineDashOffset_;
    }

    std::string GetLineJoin() const
    {
        return lineJoin_;
    }

    double GetLineWidth() const
    {
        return lineWidth_;
    }

    double GetMiterLimit() const
    {
        return miterLimit_;
    }

    double GetShadowBlur() const
    {
        return shadowBlur_;
    }

    std::string GetShadowColor() const
    {
        return shadowColor_;
    }

    double GetShadowOffsetX() const
    {
        return shadowOffsetX_;
    }

    double GetShadowOffsetY() const
    {
        return shadowOffsetY_;
    }

    std::string GetDirection() const
    {
        return direction_;
    }

    std::string GetFont() const
    {
        return font_;
    }

    std::string GetTextAlign() const
    {
        return textAlign_;
    }

    std::string GetTextBaseline() const
    {
        return textBaseline_;
    }

    std::function<void*()> wrapAnalyzerConfigImpl = nullptr;

protected:
    OHOS::Ace::RefPtr<OHOS::Ace::RenderingContext2DModel> renderingContext2DModel_;
    OHOS::Ace::RefPtr<OHOS::Ace::AceType> offscreenPattern_;
    bool anti_ = false;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

private:
    void ExtractInfoToImage(Ace::CanvasImage& image, const DrawImageParam& params);
    Dimension GetDimensionValue(const std::string& str);
    Dimension GetDimensionValue(const Dimension& dimension);
    Ace::Pattern GetPattern(unsigned int id);
    std::shared_ptr<Ace::Pattern> GetPatternPtr(int32_t id);
    void ParseImageData(Ace::ImageData& imageData, const PutImageDataParam& params);
    bool IsValidLetterSpacing(const std::string& letterSpacing);

    static std::unordered_map<int32_t, std::shared_ptr<Ace::Pattern>> pattern_;
    static unsigned int patternCount_;
    double density_ = 1.0;
    std::vector<OHOS::Ace::PaintState> savePaintState_;
    OHOS::Ace::PaintState paintState_;
    bool isInitializeShadow_ = false;
    bool isOffscreenInitializeShadow_ = false;
    int32_t densityCallbackId_ = 0;

    ParamType fillStyleType_ = ParamType::DEFAULT;
    ParamType strokeStyleType_ = ParamType::DEFAULT;
    bool imageSmoothingEnabled_ = false;
    double globalAlpha_ = 1.0;
    double lineDashOffset_ = 0.0;
    double lineWidth_;
    double miterLimit_;
    double shadowBlur_ = 0.0;
    double shadowOffsetX_ = 0.0;
    double shadowOffsetY_ = 0.0;
    std::string fillStyleString_ = "";
    std::string strokeStyleString_ = "";
    std::string globalCompositeOperation_ = "source-over";
    std::string filter_ = "none";
    std::string imageSmoothingQuality_ = "low";
    std::string lineCap_ = "butt";
    std::string lineJoin_ = "miter";
    std::string shadowColor_ = "#00000000";
    std::string direction_ = "inherit";
    std::string font_ = "normal normal 14px sans-serif";
    std::string textAlign_ = "left";
    std::string textBaseline_ = "alphabetic";
    Dimension letterSpacing_ = Dimension(0.0, DimensionUnit::VP);
    CanvasGradientPeer* fillStyleGradient_ = nullptr;
    CanvasGradientPeer* strokeStyleGradient_ = nullptr;
    CanvasPatternPeer* fillStylePattern_ = nullptr;
    CanvasPatternPeer* strokeStylePattern_ = nullptr;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
