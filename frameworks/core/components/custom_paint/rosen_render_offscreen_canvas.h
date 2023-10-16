/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_OFFSCREEN_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_OFFSCREEN_CANVAS_H

#include "modules/svg/include/SkSVGDOM.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph.h"
#else
#include "rosen_text/text_style.h"
#include "rosen_text/typography.h"
#endif
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"
#endif

#include "core/components/custom_paint/offscreen_canvas.h"
#include "core/components/custom_paint/render_custom_paint.h"
#include "core/image/image_object.h"
#include "core/image/image_provider.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {
using setColorFunc = std::function<void(const std::string&)>;
class RosenRenderOffscreenCanvas : public RenderOffscreenCanvas {
    DECLARE_ACE_TYPE(RosenRenderOffscreenCanvas, RenderOffscreenCanvas);

public:
    RosenRenderOffscreenCanvas(const WeakPtr<PipelineBase>& context, int32_t width, int32_t height);
    ~RosenRenderOffscreenCanvas() override = default;
    void SetAntiAlias(bool isEnabled) override;
    void FillRect(Rect rect) override;
    void ClearRect(Rect rect) override;
    void StrokeRect(Rect rect) override;
    void FillText(const std::string& text, double x, double y, const PaintState& state) override;
    void StrokeText(const std::string& text, double x, double y, const PaintState& state) override;
    double MeasureText(const std::string& text, const PaintState& state) override;
    double MeasureTextHeight(const std::string& text, const PaintState& state) override;
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state) override;
    std::string ToDataURL(const std::string& type, const double quality) override;
    std::unique_ptr<ImageData> GetImageData(double left, double top, double width, double height) override;
    void BeginPath() override;
    void Arc(const ArcParam& param) override;
    void Stroke() override;
    void Stroke(const RefPtr<CanvasPath2D>& path) override;
    void ArcTo(const ArcToParam& param) override;
    void MoveTo(double x, double y) override;
    void ClosePath() override;
    void Rotate(double angle) override;
    void Scale(double x, double y) override;
    void AddRect(const Rect& rect) override;
    void Fill() override;
    void Fill(const RefPtr<CanvasPath2D>& path) override;
    void Clip() override;
    void Clip(const RefPtr<CanvasPath2D>& path) override;
    void PutImageData(const ImageData& imageData) override;
    void DrawImage(const CanvasImage& canvasImage, double width, double height) override;
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const CanvasImage& image) override;
    void LineTo(double x, double y) override;
    void BezierCurveTo(const BezierCurveParam& param) override;
    void QuadraticCurveTo(const QuadraticCurveParam& param) override;
    void Ellipse(const EllipseParam& param) override;
    void SetTransform(const TransformParam& param) override;
    void Transform(const TransformParam& param) override;
    void Translate(double x, double y) override;
    void Restore() override;
    void Save() override;
    bool IsPointInStroke(double x, double y) override;
    bool IsPointInStroke(const RefPtr<CanvasPath2D>& path, double x, double y) override;
    bool IsPointInPath(double x, double y) override;
    bool IsPointInPath(const RefPtr<CanvasPath2D>& path, double x, double y) override;
    void ResetTransform() override;
    void SetFillRuleForPath(const CanvasFillRule& rule) override;
    void SetFillRuleForPath2D(const CanvasFillRule& rule) override;

private:
    void InitImagePaint();
    void InitCachePaint();
    bool antiAlias_ = true;
#ifndef USE_ROSEN_DRAWING
    SkPaint GetStrokePaint();

    SkSamplingOptions options_;

#else
    RSPen GetStrokePaint();
    RSSamplingOptions options_;
#endif
    WeakPtr<PipelineBase> pipelineContext_;
#ifndef USE_ROSEN_DRAWING
    SkBitmap skBitmap_;
    SkPath skPath_;
    SkPath skPath2d_;
    SkPaint imagePaint_;
    SkPaint cachePaint_;
    SkBitmap cacheBitmap_;
    std::unique_ptr<SkCanvas> cacheCanvas_;
    std::unique_ptr<SkCanvas> skCanvas_;
#else
    RSBitmap bitmap_;
    RSRecordingPath path_;
    RSRecordingPath path2d_;
    RSBrush imageBrush_;
    RSBrush cacheBrush_;
    RSBitmap cacheBitmap_;
    std::unique_ptr<RSCanvas> cacheCanvas_;
    std::unique_ptr<RSCanvas> canvas_;
#endif
    std::map<std::string, setColorFunc> filterFunc_;
    ImageSourceInfo loadingSource_;
    ImageSourceInfo currentSource_;
    ImageObjSuccessCallback imageObjSuccessCallback_;
    UploadSuccessCallback uploadSuccessCallback_;
    FailedCallback failedCallback_;
    OnPostBackgroundTask onPostBackgroundTask_;
    sk_sp<SkSVGDOM> skiaDom_ = nullptr;
    CanvasImage canvasImage_;

#ifndef USE_ROSEN_DRAWING
    void UpdatePaintShader(SkPaint& paint, const Gradient& gradient);
    void UpdatePaintShader(const Pattern& pattern, SkPaint& paint);
#else
    void UpdatePaintShader(RSPen* pen, RSBrush* brush, const Gradient& gradient);
    void UpdatePaintShader(const Pattern& pattern, RSPen* pen, RSBrush* brush);
#endif
    void PaintText(const std::string& text, double x, double y, bool isStroke, bool hasShadow = false);
#ifndef USE_GRAPHIC_TEXT_GINE
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph);
    std::unique_ptr<txt::Paragraph> paragraph_;
#else
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<Rosen::Typography>& paragraph);
    std::unique_ptr<Rosen::Typography> paragraph_;
#endif
    bool HasShadow() const;
    bool HasImageShadow() const;
#ifndef USE_GRAPHIC_TEXT_GINE
    void UpdateTextStyleForeground(bool isStroke, txt::TextStyle& style, bool hasShadow);
    double GetAlignOffset(const std::string& text, TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph);
#else
    void UpdateTextStyleForeground(bool isStroke, Rosen::TextStyle& style, bool hasShadow);
    double GetAlignOffset(const std::string& text, TextAlign align, std::unique_ptr<Rosen::Typography>& paragraph);
#endif
    TextDirection GetTextDirection(const std::string& text);
    bool UpdateOffParagraph(const std::string& text, bool isStroke, const PaintState& state, bool hasShadow = false);
#ifndef USE_ROSEN_DRAWING
    void UpdateLineDash(SkPaint& paint);
#else
    void UpdateLineDash(RSPen& pen);
#endif
    void Path2DAddPath(const PathArgs& args);
    void Path2DSetTransform(const PathArgs& args);
    void Path2DMoveTo(const PathArgs& args);
    void Path2DLineTo(const PathArgs& args);
    void Path2DArc(const PathArgs& args);
    void Path2DArcTo(const PathArgs& args);
    void Path2DQuadraticCurveTo(const PathArgs& args);
    void Path2DBezierCurveTo(const PathArgs& args);
    void Path2DEllipse(const PathArgs& args);
    void Path2DRect(const PathArgs& args);
    void Path2DClosePath(const PathArgs& args);
    void Path2DStroke();
    void Path2DFill();
    void Path2DClip();
    void ParsePath2D(const RefPtr<CanvasPath2D>& path);
    void TranspareCmdToPath(const RefPtr<CanvasPath2D>& path);
#ifndef USE_ROSEN_DRAWING
    bool IsPointInPathByColor(double x, double y, SkPath& path, SkColor colorMatch);
#else
    bool IsPointInPathByColor(double x, double y, RSPath& path, RSColorQuad colorMatch);
#endif
    void SetPaintImage();
    void InitFilterFunc();
    bool GetFilterType(std::string& filterType, std::string& filterParam);
    void SetGrayFilter(const std::string& percent);
    void SetSepiaFilter(const std::string& percent);
    void SetInvertFilter(const std::string& percent);
    void SetOpacityFilter(const std::string& percent);
    void SetBrightnessFilter(const std::string& percent);
    void SetContrastFilter(const std::string& percent);
    void SetBlurFilter(const std::string& percent);
    void SetDropShadowFilter(const std::string& percent);
    void SetSaturateFilter(const std::string& percent);
    void SetHueRotateFilter(const std::string& percent);
    double PxStrToDouble(const std::string& str);
    double BlurStrToDouble(const std::string& str);
    bool IsPercentStr(std::string& percentStr);
    void SetColorFilter(float matrix[20]);
    void InitImageCallbacks();
    void ImageObjReady(const RefPtr<ImageObject>& imageObj);
    void ImageObjFailed();
    void DrawSvgImage(const CanvasImage& canvasImage);
};
} // namespace OHOS::Ace

#endif // !FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_OFFSCREEN_CANVAS_H
