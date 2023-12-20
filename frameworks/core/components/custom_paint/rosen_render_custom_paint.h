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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_CUSTOM_PAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_CUSTOM_PAINT_H

#include "modules/svg/include/SkSVGDOM.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph.h"
#else
#include "rosen_text/text_style.h"
#include "rosen_text/typography.h"
#endif
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#endif

#include "base/utils/measure_util.h"
#include "core/components/custom_paint/offscreen_canvas.h"
#include "core/components/custom_paint/render_custom_paint.h"
#include "core/image/image_object.h"
#include "core/image/image_provider.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {
class RosenRenderCustomPaint : public RenderCustomPaint {
    DECLARE_ACE_TYPE(RosenRenderCustomPaint, RenderCustomPaint);

public:
    RosenRenderCustomPaint();
    ~RosenRenderCustomPaint() override;

    void Paint(RenderContext& context, const Offset& offset) override;

    void TransferFromImageBitmap(const RefPtr<OffscreenCanvas>& offscreenCanvas) override;
    void DrawBitmapMesh(const RefPtr<OffscreenCanvas>& offscreenCanvas,
        const std::vector<double>& mesh, int32_t column, int32_t row) override;
#ifndef USE_ROSEN_DRAWING
    void Mesh(SkBitmap& bitmap, int column, int row,
        const float* vertices, const int* colors, const SkPaint* paint);
#else
    void Mesh(RSBitmap& bitmap, int column, int row,
        const float* vertices, const int* colors, const RSBrush* brush);
#endif
    std::string ToDataURL(const std::string& args) override;
    void SetAntiAlias(bool isEnabled) override;
    void FillRect(const Offset& offset, const Rect& rect) override;
    void StrokeRect(const Offset& offset, const Rect& rect) override;
    void ClearRect(const Offset& offset, const Rect& rect) override;
    void FillText(const Offset& offset, const std::string& text, double x, double y) override;
    void StrokeText(const Offset& offset, const std::string& text, double x, double y) override;
    static double MeasureTextInner(const MeasureContext& context);
    static Size MeasureTextSizeInner(const MeasureContext& context);
    double MeasureText(const std::string& text, const PaintState& state) override;
    double MeasureTextHeight(const std::string& text, const PaintState& state) override;
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state) override;
    void MoveTo(const Offset& offset, double x, double y) override;
    void LineTo(const Offset& offset, double x, double y) override;
    void BezierCurveTo(const Offset& offset, const BezierCurveParam& param) override;
    void QuadraticCurveTo(const Offset& offset, const QuadraticCurveParam& param) override;
    void Arc(const Offset& offset, const ArcParam& param) override;
    void ArcTo(const Offset& offset, const ArcToParam& param) override;
    void Ellipse(const Offset& offset, const EllipseParam& param) override;
    void AddRect(const Offset& offset, const Rect& rect) override;
    void Fill(const Offset& offset) override;
    void Fill(const Offset& offset, const RefPtr<CanvasPath2D>& path) override;
    void Stroke(const Offset& offset) override;
    void Stroke(const Offset& offset, const RefPtr<CanvasPath2D>& path) override;
    void Clip() override;
    void Clip(const RefPtr<CanvasPath2D>& path) override;
    void BeginPath() override;
    void ClosePath() override;
    void ResetTransform() override;
    void Restore() override;
    void Save() override;
    void Rotate(double angle) override;
    void Scale(double x, double y) override;
    void SetTransform(const TransformParam& param) override;
    void Transform(const TransformParam& param) override;
    void Translate(double x, double y) override;
    void DrawImage(const Offset& offset, const CanvasImage& canvasImage, double width, double height) override;
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const CanvasImage& canvasImage) override;
    void PutImageData(const Offset& offset, const ImageData& imageData) override;
    std::unique_ptr<ImageData> GetImageData(double left, double top, double width, double height) override;
    std::string GetJsonData(const std::string& path) override;

    void WebGLInit(CanvasRenderContextBase* context) override;
    void WebGLUpdate() override;

    void SetFillRuleForPath(const CanvasFillRule& rule) override;
    void SetFillRuleForPath2D(const CanvasFillRule& rule) override;
    static bool IsApplyIndent(const MeasureContext& context, double& indent);
    static void ApplyLineHeightInNumUnit(const MeasureContext& context, Rosen::TextStyle& txtStyle);

    bool IsRepaintBoundary() const override
    {
        return RenderNode::IsRepaintBoundary();
    }

private:
    void InitImagePaint();
#ifndef USE_ROSEN_DRAWING
    void InitPaintBlend(SkPaint& paint);
#else
    void InitPaintBlend(RSBrush& brush);
#endif
    bool UpdateParagraph(const Offset& offset, const std::string& text, bool isStroke, bool hasShadow = false);
    void PaintText(const Offset& offset, double x, double y, bool isStroke, bool hasShadow = false);
#ifndef USE_GRAPHIC_TEXT_GINE
    double GetAlignOffset(TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph);
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph);
#else
    double GetAlignOffset(TextAlign align, std::unique_ptr<Rosen::Typography>& paragraph);
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<Rosen::Typography>& paragraph);
#endif
#ifndef USE_ROSEN_DRAWING
    SkPaint GetStrokePaint();
#else
    RSPen GetStrokePaint();
#endif
    bool HasShadow() const;
#ifndef USE_ROSEN_DRAWING
    void UpdatePaintShader(const Offset& offset, SkPaint& paint, const Gradient& gradient);
    void UpdatePaintShader(const Pattern& pattern, SkPaint& paint);
    void UpdateLineDash(SkPaint& paint);
#else
    void UpdatePaintShader(const Offset& offset, RSPen* pen, RSBrush* brush, const Gradient& gradient);
    void UpdatePaintShader(const Pattern& pattern, RSPen* pen, RSBrush* brush);
    void UpdateLineDash(RSPen& paint);
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
    void UpdateTextStyleForeground(const Offset& offset, bool isStroke, txt::TextStyle& style, bool hasShadow);
#else
    void UpdateTextStyleForeground(const Offset& offset, bool isStroke, Rosen::TextStyle& style, bool hasShadow);
#endif

    void Path2DAddPath(const Offset& offset, const PathArgs& args);
    void Path2DSetTransform(const Offset& offset, const PathArgs& args);
    void Path2DMoveTo(const Offset& offset, const PathArgs& args);
    void Path2DLineTo(const Offset& offset, const PathArgs& args);
    void Path2DArc(const Offset& offset, const PathArgs& args);
    void Path2DArcTo(const Offset& offset, const PathArgs& args);
    void Path2DQuadraticCurveTo(const Offset& offset, const PathArgs& args);
    void Path2DBezierCurveTo(const Offset& offset, const PathArgs& args);
    void Path2DEllipse(const Offset& offset, const PathArgs& args);
    void Path2DRect(const Offset& offset, const PathArgs& args);
    void Path2DClosePath(const Offset& offset, const PathArgs& args);
    void Path2DStroke(const Offset& offset);
    void Path2DFill(const Offset& offset);
    void Path2DClip();
    void ParsePath2D(const Offset& offset, const RefPtr<CanvasPath2D>& path);
    void InitImageCallbacks();
    void ImageObjReady(const RefPtr<ImageObject>& imageObj);
    void ImageObjFailed();
    void DrawSvgImage(const Offset& offset, const CanvasImage& canvasImage);
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkImage> GetImage(const std::string& src);
#else
    std::shared_ptr<RSImage> GetImage(const std::string& src);
#endif
    void CreateBitmap(double viewScale);
    bool CreateSurface(double viewScale);

    bool antiAlias_ = false;
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::Paragraph> paragraph_;
#else
    std::unique_ptr<Rosen::Typography> paragraph_;
#endif
#ifndef USE_ROSEN_DRAWING
    SkPath skPath_;
    // Specifically refers to the class Path2D in canvas.d.ts
    SkPath skPath2d_;
    SkPaint imagePaint_;
    SkPaint cachePaint_;
    SkSamplingOptions options_;
    SkBitmap cacheBitmap_;
    SkBitmap canvasCache_;
    SkBitmap webglBitmap_;
    std::unique_ptr<SkCanvas> skCanvas_;
    std::unique_ptr<SkCanvas> cacheCanvas_;
#else
    RSRecordingPath drawingPath_;
    // Specifically refers to the class Path2D in canvas.d.ts
    RSRecordingPath drawingPath2d_;
    RSBrush imageBrush_;
    RSBrush cacheBrush_;
    RSSamplingOptions options_;
    RSBitmap cacheBitmap_;
    RSBitmap canvasCache_;
    RSBitmap webglBitmap_;
    std::unique_ptr<RSCanvas> drawingCanvas_;
    std::unique_ptr<RSCanvas> cacheCanvas_;
#endif
    ImageSourceInfo loadingSource_;
    ImageSourceInfo currentSource_;
    ImageObjSuccessCallback imageObjSuccessCallback_;
    UploadSuccessCallback uploadSuccessCallback_;
    FailedCallback failedCallback_;
    OnPostBackgroundTask onPostBackgroundTask_;
    RefPtr<ImageObject> imageObj_ = nullptr;
    sk_sp<SkSVGDOM> skiaDom_ = nullptr;
    CanvasImage canvasImage_;
    Size lastLayoutSize_;
    RefPtr<ImageCache> imageCache_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CUSTOM_PAINT_ROSEN_RENDER_CUSTOM_PAINT_H
