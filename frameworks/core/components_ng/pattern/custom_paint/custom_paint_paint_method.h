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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H

#ifdef NEW_SKIA
#include "include/core/SkSamplingOptions.h"
#include "modules/svg/include/SkSVGDOM.h"
#else
#include "experimental/svg/model/SkSVGDOM.h"
#endif
#include "txt/paragraph.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/custom_paint/rendering_context2d_modifier.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/image/image_loader.h"
#include "core/image/image_object.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Rosen {
class RSRecordingCanvas;
}

namespace OHOS::Ace::NG {
enum class FilterType {
    NONE,
    GRAYSCALE,
    SEPIA,
    INVERT,
    OPACITY,
    BRIGHTNESS,
    CONTRAST,
    BLUR,
    DROP_SHADOW,
    SATURATE,
    HUE_ROTATE
};

// BT.709
constexpr float LUMR = 0.2126f;
constexpr float LUMG = 0.7152f;
constexpr float LUMB = 0.0722f;

class CustomPaintPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CustomPaintPaintMethod, NodePaintMethod)
public:
    ~CustomPaintPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return contentModifier_;
    }

    void SetFillRuleForPath(const CanvasFillRule& rule);
    void SetFillRuleForPath2D(const CanvasFillRule& rule);

    void FillRect(PaintWrapper* paintWrapper, const Rect& rect);
    void StrokeRect(PaintWrapper* paintWrapper, const Rect& rect);
    void ClearRect(PaintWrapper* paintWrapper, const Rect& rect);
    void Fill(PaintWrapper* paintWrapper);
    void Fill(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path);
    void Stroke(PaintWrapper* paintWrapper);
    void Stroke(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path);
    void Clip();
    void Clip(const RefPtr<CanvasPath2D>& path);
    void BeginPath();
    void ClosePath();
    void MoveTo(PaintWrapper* paintWrapper, double x, double y);
    void LineTo(PaintWrapper* paintWrapper, double x, double y);
    void Arc(PaintWrapper* paintWrapper, const ArcParam& param);
    void ArcTo(PaintWrapper* paintWrapper, const ArcToParam& param);
    void AddRect(PaintWrapper* paintWrapper, const Rect& rect);
    void Ellipse(PaintWrapper* paintWrapper, const EllipseParam& param);
    void BezierCurveTo(PaintWrapper* paintWrapper, const BezierCurveParam& param);
    void QuadraticCurveTo(PaintWrapper* paintWrapper, const QuadraticCurveParam& param);
    void PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    virtual void SetTransform(const TransformParam& param) = 0;
    virtual TransformParam GetTransform() const;
    void ResetTransform();
    void Transform(const TransformParam& param);
    void Translate(double x, double y);

    void SetFilterParam(const std::string& filterStr)
    {
        filterParam_ = filterStr;
    }

    void SetAntiAlias(bool isEnabled)
    {
        antiAlias_ = isEnabled;
    }

    void SetFillColor(const Color& color)
    {
        fillState_.SetColor(color);
        fillState_.SetTextColor(color);
    }

    void SetFillPattern(const Ace::Pattern& pattern)
    {
        fillState_.SetPattern(pattern);
    }

    void SetFillPatternNG(const std::weak_ptr<Ace::Pattern>& pattern)
    {
        fillState_.SetPatternNG(pattern);
    }

    void SetFillGradient(const Ace::Gradient& gradient)
    {
        fillState_.SetGradient(gradient);
    }

    void SetAlpha(double alpha)
    {
        globalState_.SetAlpha(alpha);
    }

    void SetCompositeType(CompositeOperation operation)
    {
        globalState_.SetType(operation);
    }

    // direction is also available in strokeText
    void SetTextDirection(TextDirection direction)
    {
        fillState_.SetOffTextDirection(direction);
    }

    void SetStrokeColor(const Color& color)
    {
        strokeState_.SetColor(color);
    }

    void SetStrokePatternNG(const std::weak_ptr<Ace::Pattern>& pattern)
    {
        strokeState_.SetPatternNG(pattern);
    }

    void SetStrokePattern(const Ace::Pattern& pattern)
    {
        strokeState_.SetPattern(pattern);
    }

    void SetStrokeGradient(const Ace::Gradient& gradient)
    {
        strokeState_.SetGradient(gradient);
    }

    void SetLineCap(LineCapStyle style)
    {
        strokeState_.SetLineCap(style);
    }

    void SetLineDashOffset(double offset)
    {
        strokeState_.SetLineDashOffset(offset);
    }

    void SetLineJoin(LineJoinStyle style)
    {
        strokeState_.SetLineJoin(style);
    }

    void SetLineWidth(double width)
    {
        strokeState_.SetLineWidth(width);
    }

    void SetMiterLimit(double limit)
    {
        strokeState_.SetMiterLimit(limit);
    }

    LineDashParam GetLineDash() const
    {
        return strokeState_.GetLineDash();
    }

    void SetLineDash(const std::vector<double>& segments)
    {
        strokeState_.SetLineDash(segments);
    }

    void SetTextAlign(TextAlign align)
    {
        fillState_.SetTextAlign(align);
        strokeState_.SetTextAlign(align);
    }

    void SetTextBaseline(TextBaseline baseline)
    {
        fillState_.SetTextBaseline(baseline);
        strokeState_.SetTextBaseline(baseline);
    }

    void SetShadowColor(const Color& color)
    {
        shadow_.SetColor(color);
    }

    void SetShadowBlur(double blur)
    {
        shadow_.SetBlurRadius(blur);
    }

    void SetShadowOffsetX(double x)
    {
        shadow_.SetOffsetX(x);
    }

    void SetShadowOffsetY(double y)
    {
        shadow_.SetOffsetY(y);
    }

    void SetSmoothingEnabled(bool enabled)
    {
        smoothingEnabled_ = enabled;
    }

    void SetSmoothingQuality(const std::string& quality)
    {
        smoothingQuality_ = quality;
    }

    void SetFontSize(const Dimension& size)
    {
        fillState_.SetFontSize(size);
        strokeState_.SetFontSize(size);
    }

    void SetFontStyle(FontStyle style)
    {
        fillState_.SetFontStyle(style);
        strokeState_.SetFontStyle(style);
    }

    void SetFontWeight(FontWeight weight)
    {
        fillState_.SetFontWeight(weight);
        strokeState_.SetFontWeight(weight);
    }

    void SetFontFamilies(const std::vector<std::string>& fontFamilies)
    {
        fillState_.SetFontFamilies(fontFamilies);
        strokeState_.SetFontFamilies(fontFamilies);
    }

    void SaveStates()
    {
        PaintHolder holder;
        holder.shadow = shadow_;
        holder.fillState = fillState_;
        holder.globalState = globalState_;
        holder.strokeState = strokeState_;
        saveStates_.push(holder);
    }

    void RestoreStates()
    {
        if (saveStates_.empty()) {
            return;
        }
        auto saveState = saveStates_.top();
        shadow_ = saveState.shadow;
        fillState_ = saveState.fillState;
        strokeState_ = saveState.strokeState;
        globalState_ = saveState.globalState;
        saveStates_.pop();
    }

    void FlushPipelineImmediately()
    {
        auto context = context_.Upgrade();
        if (context) {
            context->FlushPipelineImmediately();
        }
    }

    void SaveMatrix();
    void RestoreMatrix();
    void ResetTransformMatrix();
    void RotateMatrix(double angle);
    void ScaleMatrix(double x, double y);
    void SetTransformMatrix(const TransformParam& param);
    void TransformMatrix(const TransformParam& param);
    void TranslateMatrix(double tx, double ty);

    void UpdateRecordingCanvas(float width, float height);

protected:
    std::optional<double> CalcTextScale(double maxIntrinsicWidth, std::optional<double> maxWidth);
    bool HasShadow() const;
#ifndef USE_ROSEN_DRAWING
    void UpdateLineDash(SkPaint& paint);
    void UpdatePaintShader(const OffsetF& offset, SkPaint& paint, const Ace::Gradient& gradient);
    void UpdatePaintShader(const Ace::Pattern& pattern, SkPaint& paint);
    void InitPaintBlend(SkPaint& paint);
    sk_sp<SkShader> MakeConicGradient(SkPaint& paint, const Ace::Gradient& gradient);
#else
    void UpdateLineDash(RSPen& pen);
    void UpdatePaintShader(const OffsetF& offset, RSPen* pen, RSBrush* brush, const Ace::Gradient& gradient);
    void UpdatePaintShader(const Ace::Pattern& pattern, RSPen* pen, RSBrush* brush);
    void InitPaintBlend(RSBrush& brush);
    std::shared_ptr<RSShaderEffect> MakeConicGradient(RSBrush* brush, const Ace::Gradient& gradient);
#endif

    void Path2DFill(const OffsetF& offset);
    void Path2DStroke(const OffsetF& offset);
    void Path2DClip();
    void ParsePath2D(const OffsetF& offset, const RefPtr<CanvasPath2D>& path);
    void Path2DAddPath(const OffsetF& offset, const PathArgs& args);
    void Path2DClosePath(const OffsetF& offset, const PathArgs& args);
    void Path2DMoveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DLineTo(const OffsetF& offset, const PathArgs& args);
    void Path2DArc(const OffsetF& offset, const PathArgs& args);
    void Path2DArcTo(const OffsetF& offset, const PathArgs& args);
    virtual void Path2DRect(const OffsetF& offset, const PathArgs& args) = 0;
    void Path2DEllipse(const OffsetF& offset, const PathArgs& args);
    void Path2DBezierCurveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DQuadraticCurveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DSetTransform(const OffsetF& offset, const PathArgs& args);
#ifndef USE_ROSEN_DRAWING
    SkMatrix GetMatrixFromPattern(const Ace::Pattern& pattern);

    void SetGrayFilter(const std::string& percent, SkPaint& paint);
    void SetSepiaFilter(const std::string& percent, SkPaint& paint);
    void SetSaturateFilter(const std::string& percent, SkPaint& paint);
    void SetHueRotateFilter(const std::string& percent, SkPaint& paint);
    void SetInvertFilter(const std::string& percent, SkPaint& paint);
    void SetOpacityFilter(const std::string& percent, SkPaint& paint);
    void SetBrightnessFilter(const std::string& percent, SkPaint& paint);
    void SetContrastFilter(const std::string& percent, SkPaint& paint);
    void SetBlurFilter(const std::string& percent, SkPaint& paint);

    void SetColorFilter(float matrix[20], SkPaint& paint);
#else
    RSMatrix GetMatrixFromPattern(const Ace::Pattern& pattern);

    void SetGrayFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetSepiaFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetSaturateFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetHueRotateFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetInvertFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetOpacityFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetBrightnessFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetContrastFilter(const std::string& percent, RSPen* pen, RSBrush* brush);
    void SetBlurFilter(const std::string& percent, RSPen* pen, RSBrush* brush);

    void SetColorFilter(float matrix[20], RSPen* pen, RSBrush* brush);
#endif

    bool GetFilterType(FilterType& filterType, std::string& filterParam);
    bool IsPercentStr(std::string& percentStr);
    double PxStrToDouble(const std::string& str);
    double BlurStrToDouble(const std::string& str);
    bool CheckNumberAndPercentage(const std::string& param, bool isClamped, float& result);
#ifndef USE_ROSEN_DRAWING
#ifndef NEW_SKIA
    void InitImagePaint(SkPaint& paint);
    void GetStrokePaint(SkPaint& paint);
#else
    void InitImagePaint(SkPaint& paint, SkSamplingOptions& options);
    void GetStrokePaint(SkPaint& paint, SkSamplingOptions& options);
#endif
#else
    void InitImagePaint(RSPen* pen, RSBrush* brush, RSSamplingOptions& options);
    void GetStrokePaint(RSPen& pen, RSSamplingOptions& options);
#endif
    void InitImageCallbacks();

#ifndef USE_ROSEN_DRAWING
    void SetPaintImage(SkPaint& paint);
    void ClearPaintImage(SkPaint& paint);
#else
    void SetPaintImage(RSPen* pen, RSBrush* brush);
    void ClearPaintImage(RSPen* pen, RSBrush* brush);
#endif
    float PercentStrToFloat(const std::string& percentStr);
    FilterType FilterStrToFilterType(const std::string& filterStr);
    bool HasImageShadow() const;

    virtual void ImageObjReady(const RefPtr<Ace::ImageObject>& imageObj) = 0;
    virtual void ImageObjFailed() = 0;
#ifndef USE_ROSEN_DRAWING
    virtual sk_sp<SkImage> GetImage(const std::string& src) = 0;
#else
    virtual std::shared_ptr<RSImage> GetImage(const std::string& src) = 0;
#endif
    void DrawSvgImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage);
#ifndef USE_ROSEN_DRAWING
    virtual SkCanvas* GetRawPtrOfSkCanvas() = 0;
    virtual void PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas, const SkPaint* paint) = 0;
#else
    virtual RSCanvas* GetRawPtrOfRSCanvas() = 0;
    virtual void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas* canvas) = 0;
#endif
    virtual OffsetF GetContentOffset(PaintWrapper* paintWrapper) const
    {
        return OffsetF(0.0f, 0.0f);
    }

    double GetAlignOffset(TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph);
    txt::TextAlign GetEffectiveAlign(txt::TextAlign align, txt::TextDirection direction) const;

    PaintState fillState_;
    StrokePaintState strokeState_;

    // save alpha and compositeType in GlobalPaintState
    GlobalPaintState globalState_;

    // PaintHolder includes fillState, strokeState, globalState and shadow for save
    std::stack<PaintHolder> saveStates_;
    std::stack<SkMatrix> matrixStates_;
    SkMatrix matrix_;

    bool smoothingEnabled_ = true;
    std::string smoothingQuality_ = "low";
    bool antiAlias_ = false;
    Shadow shadow_;
    std::unique_ptr<txt::Paragraph> paragraph_;

    WeakPtr<PipelineBase> context_;

#ifndef USE_ROSEN_DRAWING
    SkPath skPath_;
    SkPath skPath2d_;
    SkPaint imagePaint_;
#ifdef NEW_SKIA
    SkSamplingOptions sampleOptions_;
#endif
    SkBitmap canvasCache_;
    std::shared_ptr<SkCanvas> skCanvas_;
#else
    RSPath rsPath_;
    RSPath rsPath2d_;
    RSBrush imageBrush_;
    RSSamplingOptions sampleOptions_;
    RSBitmap canvasCache_;
    std::shared_ptr<RSCanvas> rsCanvas_;
#endif

    sk_sp<SkSVGDOM> skiaDom_ = nullptr;
    Ace::CanvasImage canvasImage_;
    std::string filterParam_ = "";
    std::unique_ptr<Shadow> imageShadow_;

    ImageSourceInfo currentSource_;
    ImageSourceInfo loadingSource_;
    ImageObjSuccessCallback imageObjSuccessCallback_;
    UploadSuccessCallback uploadSuccessCallback_;
    OnPostBackgroundTask onPostBackgroundTask_;
    FailedCallback failedCallback_;

    RefPtr<RenderingContext2DModifier> contentModifier_;
#ifndef USE_ROSEN_DRAWING
    std::shared_ptr<OHOS::Rosen::RSRecordingCanvas> rsRecordingCanvas_;
#else
    std::shared_ptr<RSRecordingCanvas> rsRecordingCanvas_;
#endif

    SizeF lastLayoutSize_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
