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

#include "experimental/svg/model/SkSVGDOM.h"
#include "flutter/third_party/txt/src/txt/paragraph.h"
#include "third_party/skia/include/core/SkPath.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/image/image_loader.h"
#include "core/image/image_object.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class CustomPaintPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CustomPaintPaintMethod, NodePaintMethod)
public:
    ~CustomPaintPaintMethod() override = default;

    void SetFillColor(const Color& color)
    {
        fillState_.SetColor(color);
        fillState_.SetTextColor(color);
    }

    const LineDashParam& GetLineDash() const
    {
        return strokeState_.GetLineDash();
    }

    void SetLineDash(const std::vector<double>& segments)
    {
        strokeState_.SetLineDash(segments);
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

    void SetFillRuleForPath(const CanvasFillRule& rule);
    void SetFillRuleForPath2D(const CanvasFillRule& rule);

    void FillRect(PaintWrapper* paintWrapper, const Rect& rect);
    void StrokeRect(PaintWrapper* paintWrapper, const Rect& rect);
    void ClearRect(PaintWrapper* paintWrapper, const Rect& rect);
    void Fill(PaintWrapper* paintWrapper);
    void Fill(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path);
    void Stroke(PaintWrapper* paintWrapper);
    void Stroke(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path);
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

    void DrawImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    virtual std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height) = 0;
    void PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    void SetTransform(const TransformParam& param);
    void Transform(const TransformParam& param);
    void Translate(double x, double y);

protected:
    bool HasShadow() const;
    void UpdateLineDash(SkPaint& paint);
    void UpdatePaintShader(const OffsetF& offset, SkPaint& paint, const Ace::Gradient& gradient);
    void UpdatePaintShader(const Ace::Pattern& pattern, SkPaint& paint);
    void InitPaintBlend(SkPaint& paint);
    SkPaint GetStrokePaint();

    void Path2DFill(const OffsetF& offset);
    void Path2DStroke(const OffsetF& offset);
    void ParsePath2D(const OffsetF& offset, const RefPtr<CanvasPath2D>& path);
    void Path2DAddPath(const OffsetF& offset, const PathArgs& args);
    void Path2DClosePath(const OffsetF& offset, const PathArgs& args);
    void Path2DMoveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DLineTo(const OffsetF& offset, const PathArgs& args);
    void Path2DArc(const OffsetF& offset, const PathArgs& args);
    void Path2DArcTo(const OffsetF& offset, const PathArgs& args);
    void Path2DRect(const OffsetF& offset, const PathArgs& args);
    void Path2DEllipse(const OffsetF& offset, const PathArgs& args);
    void Path2DBezierCurveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DQuadraticCurveTo(const OffsetF& offset, const PathArgs& args);
    void Path2DSetTransform(const OffsetF& offset, const PathArgs& args);

    void InitImagePaint();
    void InitImageCallbacks();
    virtual void ImageObjReady(const RefPtr<ImageObject>& imageObj) = 0;
    virtual void ImageObjFailed() = 0;
    virtual sk_sp<SkImage> GetImage(const std::string& src) = 0;
    void DrawSvgImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage);

    PaintState fillState_;
    StrokePaintState strokeState_;

    // save alpha and compositeType in GlobalPaintState
    GlobalPaintState globalState_;

    // PaintHolder includes fillState, strokeState, globalState and shadow for save
    std::stack<PaintHolder> saveStates_;

    bool smoothingEnabled_ = true;
    std::string smoothingQuality_ = "low";
    bool antiAlias_ = false;
    Shadow shadow_;
    bool isOffscreen_ = false;
    std::unique_ptr<txt::Paragraph> paragraph_;

    RefPtr<PipelineContext> context_;

    SkPath skPath_;
    SkPath skPath2d_;
    SkPaint imagePaint_;
    SkPaint cachePaint_;
    SkBitmap cacheBitmap_;
    SkBitmap canvasCache_;
    std::unique_ptr<SkCanvas> skCanvas_;
    std::unique_ptr<SkCanvas> cacheCanvas_;

    RefPtr<FlutterRenderTaskHolder> renderTaskHolder_;

    sk_sp<SkSVGDOM> skiaDom_ = nullptr;
    Ace::CanvasImage canvasImage_;

    ImageSourceInfo currentSource_;
    ImageSourceInfo loadingSource_;
    ImageObjSuccessCallback imageObjSuccessCallback_;
    UploadSuccessCallback uploadSuccessCallback_;
    OnPostBackgroundTask onPostBackgroundTask_;
    FailedCallback failedCallback_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
