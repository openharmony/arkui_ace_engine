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

#include "core/components/custom_paint/rosen_render_offscreen_canvas.h"


#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"
#include "unicode/ubidi.h"
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBlendMode.h"
#include "include/core/SkColor.h"
#include "include/core/SkColorFilter.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPoint.h"
#include "include/effects/SkImageFilters.h"
#endif
#include "include/encode/SkJpegEncoder.h"
#include "include/encode/SkPngEncoder.h"
#include "include/encode/SkWebpEncoder.h"
#ifdef USE_NEW_SKIA
#include "src/base/SkBase64.h"
#else
#include "include/utils/SkBase64.h"
#endif

#include "base/i18n/localization.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing.h"
#endif
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
namespace {
constexpr double HANGING_PERCENT = 0.8;
#ifndef USE_ROSEN_DRAWING
template<typename T, typename N>
N ConvertEnumToSkEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}
#else
template<typename T, typename N>
N ConvertEnumToDrawingEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}
#endif

constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;

// If args is empty or invalid format, use default: image/png
std::string GetMimeType(const std::string& args)
{
    std::string type = args;
    for (size_t i = 0; i < type.size(); ++i) {
        type[i] = static_cast<uint8_t>(tolower(type[i]));
    }
    return type;
}

// Quality need between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args, const double quality)
{
    std::string type = args;
    auto mimeType = GetMimeType(type);
    if (mimeType != IMAGE_JPEG && mimeType != IMAGE_WEBP) {
        return DEFAULT_QUALITY;
    }
    if (quality < 0.0 || quality > 1.0) {
        return DEFAULT_QUALITY;
    }
    return quality;
}

#ifndef USE_ROSEN_DRAWING
const LinearEnumMapNode<CompositeOperation, SkBlendMode> SK_BLEND_MODE_TABLE[] = {
    { CompositeOperation::SOURCE_OVER, SkBlendMode::kSrcOver },
    { CompositeOperation::SOURCE_ATOP, SkBlendMode::kSrcATop },
    { CompositeOperation::SOURCE_IN, SkBlendMode::kSrcIn },
    { CompositeOperation::SOURCE_OUT, SkBlendMode::kSrcOut },
    { CompositeOperation::DESTINATION_OVER, SkBlendMode::kDstOver },
    { CompositeOperation::DESTINATION_ATOP, SkBlendMode::kDstATop },
    { CompositeOperation::DESTINATION_IN, SkBlendMode::kDstIn },
    { CompositeOperation::DESTINATION_OUT, SkBlendMode::kDstOut },
    { CompositeOperation::LIGHTER, SkBlendMode::kLighten },
    { CompositeOperation::COPY, SkBlendMode::kSrc },
    { CompositeOperation::XOR, SkBlendMode::kXor },
};
constexpr size_t BLEND_MODE_SIZE = ArraySize(SK_BLEND_MODE_TABLE);
#else
const LinearEnumMapNode<CompositeOperation, RSBlendMode> DRAWING_BLEND_MODE_TABLE[] = {
    { CompositeOperation::SOURCE_OVER, RSBlendMode::SRC_OVER },
    { CompositeOperation::SOURCE_ATOP, RSBlendMode::SRC_ATOP },
    { CompositeOperation::SOURCE_IN, RSBlendMode::SRC_IN },
    { CompositeOperation::SOURCE_OUT, RSBlendMode::SRC_OUT },
    { CompositeOperation::DESTINATION_OVER, RSBlendMode::DST_OVER },
    { CompositeOperation::DESTINATION_ATOP, RSBlendMode::DST_ATOP },
    { CompositeOperation::DESTINATION_IN, RSBlendMode::DST_IN },
    { CompositeOperation::DESTINATION_OUT, RSBlendMode::DST_OUT },
    { CompositeOperation::LIGHTER, RSBlendMode::LIGHTEN },
    { CompositeOperation::COPY, RSBlendMode::SRC },
    { CompositeOperation::XOR, RSBlendMode::XOR },
};
constexpr size_t BLEND_MODE_SIZE = ArraySize(DRAWING_BLEND_MODE_TABLE);
#endif
} // namespace

RosenRenderOffscreenCanvas::RosenRenderOffscreenCanvas(
    const WeakPtr<PipelineBase>& context, int32_t width, int32_t height)
{
    pipelineContext_ = context;
    width_ = width;
    height_ = height;
#ifndef USE_ROSEN_DRAWING
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    skBitmap_.allocPixels(imageInfo);
    cacheBitmap_.allocPixels(imageInfo);
    skBitmap_.eraseColor(SK_ColorTRANSPARENT);
    cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    skCanvas_ = std::make_unique<SkCanvas>(skBitmap_);
    cacheCanvas_ = std::make_unique<SkCanvas>(cacheBitmap_);
#else
    RSBitmapFormat format { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap_.Build(width, height, format);
    cacheBitmap_.Build(width, height, format);
    bitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    canvas_ = std::make_unique<RSCanvas>();
    canvas_->Bind(bitmap_);
    cacheCanvas_ = std::make_unique<RSCanvas>();
    cacheCanvas_->Bind(cacheBitmap_);
#endif
    InitFilterFunc();
    InitImageCallbacks();
}
void RosenRenderOffscreenCanvas::AddRect(const Rect& rect)
{
#ifndef USE_ROSEN_DRAWING
    SkRect skRect = SkRect::MakeLTRB(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    skPath_.addRect(skRect);
#else
    RSRect drawingRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    path_.AddRect(drawingRect);
#endif
}

void RosenRenderOffscreenCanvas::SetFillRuleForPath(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
#ifndef USE_ROSEN_DRAWING

        skPath_.setFillType(SkPathFillType::kWinding);
    } else if (rule == CanvasFillRule::EVENODD) {
        skPath_.setFillType(SkPathFillType::kEvenOdd);
#else
        if (rule == CanvasFillRule::NONZERO) {
            path_.SetFillStyle(RSPathFillType::WINDING);
        } else if (rule == CanvasFillRule::EVENODD) {
            path_.SetFillStyle(RSPathFillType::EVENTODD);
        }
#endif
    }
}

void RosenRenderOffscreenCanvas::SetFillRuleForPath2D(const CanvasFillRule& rule)
{
#ifndef USE_ROSEN_DRAWING
    if (rule == CanvasFillRule::NONZERO) {
        skPath2d_.setFillType(SkPathFillType::kWinding);
    } else if (rule == CanvasFillRule::EVENODD) {
        skPath2d_.setFillType(SkPathFillType::kEvenOdd);
    }
#else
    if (rule == CanvasFillRule::NONZERO) {
        path2d_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        path2d_.SetFillStyle(RSPathFillType::EVENTODD);
    }
#endif
}

void RosenRenderOffscreenCanvas::ParsePath2D(const RefPtr<CanvasPath2D>& path)
{
    for (const auto& [cmd, args] : path->GetCaches()) {
        switch (cmd) {
            case PathCmd::CMDS: {
                Path2DAddPath(args);
                break;
            }
            case PathCmd::TRANSFORM: {
                Path2DSetTransform(args);
                break;
            }
            case PathCmd::MOVE_TO: {
                Path2DMoveTo(args);
                break;
            }
            case PathCmd::LINE_TO: {
                Path2DLineTo(args);
                break;
            }
            case PathCmd::ARC: {
                Path2DArc(args);
                break;
            }
            case PathCmd::ARC_TO: {
                Path2DArcTo(args);
                break;
            }
            case PathCmd::QUADRATIC_CURVE_TO: {
                Path2DQuadraticCurveTo(args);
                break;
            }
            case PathCmd::BEZIER_CURVE_TO: {
                Path2DBezierCurveTo(args);
                break;
            }
            case PathCmd::ELLIPSE: {
                Path2DEllipse(args);
                break;
            }
            case PathCmd::RECT: {
                Path2DRect(args);
                break;
            }
            case PathCmd::CLOSE_PATH: {
                Path2DClosePath(args);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void RosenRenderOffscreenCanvas::Fill()
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawPath(skPath_, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(path_, shadow_, canvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachBrush(brush);
        canvas_->DrawPath(path_);
        canvas_->DetachBrush();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawPath(path_);
        cacheCanvas_->DetachBrush();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::Fill(const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        LOGE("Fill failed in offscreenCanvas, target path is null.");
        return;
    }
    ParsePath2D(path);
    Path2DFill();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    path2d_.Reset();
#endif
}

void RosenRenderOffscreenCanvas::Clip()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->clipPath(skPath_);
#else
    canvas_->ClipPath(path_, RSClipOp::INTERSECT, false);
#endif
}

void RosenRenderOffscreenCanvas::Clip(const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        LOGE("Clip failed in offscreenCanvas, target path is null.");
        return;
    }
    ParsePath2D(path);
    Path2DClip();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    path2d_.Reset();
#endif
}

void RosenRenderOffscreenCanvas::FillRect(Rect rect)
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    SkRect skRect = SkRect::MakeLTRB(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);

        RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha()); // update the global alpha after setting the color
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawRect(skRect, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    RSRect drawingRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(drawingRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, canvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha()); // update the global alpha after setting the color
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachBrush(brush);
        canvas_->DrawRect(drawingRect);
        canvas_->DetachBrush();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawRect(drawingRect);
        cacheCanvas_->DetachBrush();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::PutImageData(const ImageData& imageData)
{
    if (imageData.data.empty()) {
        return;
    }
    uint32_t* data = new (std::nothrow) uint32_t[imageData.data.size()];
    if (data == nullptr) {
        return;
    }

    for (uint32_t i = 0; i < imageData.data.size(); ++i) {
        data[i] = imageData.data[i];
    }
#ifndef USE_ROSEN_DRAWING
    SkBitmap skBitmap;
    auto imageInfo = SkImageInfo::Make(imageData.dirtyWidth, imageData.dirtyHeight, SkColorType::kBGRA_8888_SkColorType,
        SkAlphaType::kOpaque_SkAlphaType);
    skBitmap.allocPixels(imageInfo);
    skBitmap.setPixels(data);

    skCanvas_->drawImage(skBitmap.asImage(), imageData.x, imageData.y, SkSamplingOptions());
#else
    RSBitmap bitmap;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
    bitmap.SetPixels(data);
    canvas_->DrawBitmap(bitmap, imageData.x, imageData.y);
#endif
    delete[] data;
}

void RosenRenderOffscreenCanvas::SetPaintImage()
{
    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
#ifndef USE_ROSEN_DRAWING

    imagePaint_.setColorFilter(SkColorFilters::Matrix(matrix));

    imagePaint_.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, 0));

    imagePaint_.setImageFilter(SkImageFilters::Blur(0, 0, nullptr));
#else
    auto filter = imageBrush_.GetFilter();
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, 0));
    filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(0, 0, RSTileMode::DECAL, nullptr));
    imageBrush_.SetFilter(filter);
#endif

    SetDropShadowFilter("0px 0px 0px black");
    std::string filterType, filterParam;
    if (!GetFilterType(filterType, filterParam)) {
        return;
    }
    if (filterFunc_.find(filterType) != filterFunc_.end()) {
        filterFunc_[filterType](filterParam);
    }
}

void RosenRenderOffscreenCanvas::InitImagePaint()
{
#ifndef USE_ROSEN_DRAWING

    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone);
        } else if (smoothingQuality_ == "medium") {
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
        } else if (smoothingQuality_ == "high") {
            options_ = SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f });
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        options_ = SkSamplingOptions(SkFilterMode::kNearest, SkMipmapMode::kNone);
    }
#else
    auto filter = imageBrush_.GetFilter();
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE);
            filter.SetFilterQuality(RSFilter::FilterQuality::LOW);
            imageBrush_.SetFilter(filter);
        } else if (smoothingQuality_ == "medium") {
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::LINEAR);
            filter.SetFilterQuality(RSFilter::FilterQuality::MEDIUM);
            imageBrush_.SetFilter(filter);
        } else if (smoothingQuality_ == "high") {
            options_ = RSSamplingOptions(RSCubicResampler::Mitchell());
            filter.SetFilterQuality(RSFilter::FilterQuality::HIGH);
            imageBrush_.SetFilter(filter);
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        options_ = RSSamplingOptions(RSFilterMode::NEAREST, RSMipmapMode::NONE);
        filter.SetFilterQuality(RSFilter::FilterQuality::NONE);
        imageBrush_.SetFilter(filter);
    }
#endif
    SetPaintImage();
}

void RosenRenderOffscreenCanvas::InitImageCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<ImageObject>& imageObj) {
        auto render = weak.Upgrade();
        if (render->loadingSource_ == info) {
            render->ImageObjReady(imageObj);
            return;
        } else {
            LOGE("image sourceInfo_ check error, : %{public}s vs %{public}s", render->loadingSource_.ToString().c_str(),
                info.ToString().c_str());
        }
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg = "") {
        auto render = weak.Upgrade();
        LOGE("failedCallback_");
        render->ImageObjFailed();
    };
    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const RefPtr<NG::CanvasImage>& image) {};

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {};
}

void RosenRenderOffscreenCanvas::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    if (imageObj->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj)->GetSkiaDom();
        currentSource_ = loadingSource_;
    } else {
        LOGE("image is not svg");
    }
}

void RosenRenderOffscreenCanvas::ImageObjFailed()
{
    loadingSource_.SetSrc("");
    currentSource_.SetSrc("");
    skiaDom_ = nullptr;
}

void RosenRenderOffscreenCanvas::DrawSvgImage(const CanvasImage& canvasImage)
{
#ifndef USE_ROSEN_DRAWING
    const auto skCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
#else
    const auto drawingCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? canvas_.get() : cacheCanvas_.get();
#endif

    // Make the ImageSourceInfo
    canvasImage_ = canvasImage;
    loadingSource_ = ImageSourceInfo(canvasImage.src);
    // get the ImageObject
    if (currentSource_ != loadingSource_) {
        ImageProvider::FetchImageObject(loadingSource_, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, pipelineContext_, true, true, true, onPostBackgroundTask_);
    }

    // draw the svg
#ifndef USE_ROSEN_DRAWING
    if (skiaDom_) {
        SkRect srcRect;
        SkRect dstRect;
        Offset startPoint;
        double scaleX = 1.0f;
        double scaleY = 1.0f;
        switch (canvasImage.flag) {
            case 0:
                srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width(),
                    skiaDom_->containerSize().height());
                break;
            case 1: {
                srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
                break;
            }
            case 2: {
                srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
                break;
            }
            default:
                break;
        }
        scaleX = dstRect.width() / srcRect.width();
        scaleY = dstRect.height() / srcRect.height();
        startPoint = Offset(dstRect.left(), dstRect.top()) - Offset(srcRect.left() * scaleX, srcRect.top() * scaleY);

        skCanvas->save();
        skCanvas->clipRect(dstRect);
        skCanvas->translate(startPoint.GetX(), startPoint.GetY());
        skCanvas->scale(scaleX, scaleY);
        skiaDom_->render(skCanvas);
        skCanvas->restore();
    }
#else
    if (skiaDom_) {
        RSRect srcRect;
        RSRect dstRect;
        Offset startPoint;
        double scaleX = 1.0f;
        double scaleY = 1.0f;
        switch (canvasImage.flag) {
            case 0:
                srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width() + canvasImage.dx,
                    skiaDom_->containerSize().height() + canvasImage.dy);
                break;
            case 1: {
                srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                    canvasImage.dHeight + canvasImage.dy);
                break;
            }
            case 2: {
                srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                    canvasImage.sHeight + canvasImage.sy);
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                    canvasImage.dHeight + canvasImage.dy);
                break;
            }
            default:
                break;
        }
        scaleX = dstRect.GetWidth() / srcRect.GetWidth();
        scaleY = dstRect.GetHeight() / srcRect.GetHeight();
        startPoint =
            Offset(dstRect.GetLeft(), dstRect.GetTop()) - Offset(srcRect.GetLeft() * scaleX, srcRect.GetTop() * scaleY);

        drawingCanvas->Save();
        drawingCanvas->ClipRect(dstRect, RSClipOp::INTERSECT, false);
        drawingCanvas->Translate(startPoint.GetX(), startPoint.GetY());
        drawingCanvas->Scale(scaleX, scaleY);
        drawingCanvas->DrawSVGDOM(skiaDom_);
        drawingCanvas->Restore();
    }
#endif
}

void RosenRenderOffscreenCanvas::DrawImage(const CanvasImage& canvasImage, double width, double height)
{
    auto context = pipelineContext_.Upgrade();
    if (!context) {
        return;
    }

    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(canvasImage);
        return;
    }

#ifndef USE_ROSEN_DRAWING
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetSkImage(canvasImage.src, context, Size(width, height))
                     : ImageProvider::GetSkImage(canvasImage.src, context);
    if (!image) {
        LOGE("image is null");
        return;
    }
    InitCachePaint();
    const auto skCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    if (HasImageShadow()) {
        SkRect skRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
        SkPath path;
        path.addRect(skRect);

        RosenDecorationPainter::PaintShadow(path, imageShadow_, skCanvas);
    }
    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);

            skCanvas->drawImageRect(image, rect, options_, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);

            skCanvas->drawImageRect(image, srcRect, dstRect, options_, &imagePaint_, SkCanvas::kFast_SrcRectConstraint);
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetDrawingImage(canvasImage.src, context, Size(width, height))
                     : ImageProvider::GetDrawingImage(canvasImage.src, context);
    if (!image) {
        LOGE("image is null");
        return;
    }
    InitCachePaint();
    const auto canvas = globalState_.GetType() == CompositeOperation::SOURCE_OVER ? canvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    if (HasImageShadow()) {
        RSRect drawingRect = RSRect(
            canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
        RSRecordingPath path;
        path.AddRect(drawingRect);
        RosenDecorationPainter::PaintShadow(path, imageShadow_, canvas);
    }

    switch (canvasImage.flag) {
        case 0:
            canvas->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            canvas->AttachBrush(imageBrush_);
            canvas->DrawImageRect(*image, rect, options_);
            canvas->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                canvasImage.sHeight + canvasImage.sy);
            canvas->AttachBrush(imageBrush_);
            canvas->DrawImageRect(*image, srcRect, dstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
            canvas->DetachBrush();
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::DrawPixelMap(RefPtr<PixelMap> pixelMap, const CanvasImage& canvasImage)
{
    auto context = pipelineContext_.Upgrade();
    if (!context) {
        return;
    }

#ifndef USE_ROSEN_DRAWING
    // get skImage form pixelMap
    auto imageInfo = ImageProvider::MakeSkImageInfoFromPixelMap(pixelMap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixelMap->GetPixels()), pixelMap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> image;

    image = SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(pixelMap));
    if (!image) {
        LOGE("image is null");
        return;
    }

    InitCachePaint();
    const auto skCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);

            skCanvas->drawImageRect(image, rect, options_, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);

            skCanvas->drawImageRect(image, srcRect, dstRect, options_, &imagePaint_, SkCanvas::kFast_SrcRectConstraint);
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    // get Image form pixelMap
    auto rsBitmapFormat = ImageProvider::MakeRSBitmapFormatFromPixelMap(pixelMap);
    auto rsBitmap = std::make_shared<RSBitmap>();
    rsBitmap->Build(pixelMap->GetWidth(), pixelMap->GetHeight(), rsBitmapFormat);
    rsBitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixelMap->GetPixels())));

    // Step2: Create Image and draw it, using gpu or cpu
    auto image = std::make_shared<RSImage>();
    if (!image->BuildFromBitmap(*rsBitmap)) {
        LOGE("image is null");
        return;
    }

    InitCachePaint();
    const auto drawingCanvas =
        globalState_.GetType() == CompositeOperation::SOURCE_OVER ? canvas_.get() : cacheCanvas_.get();
    InitImagePaint();
    switch (canvasImage.flag) {
        case 0:
            drawingCanvas->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            drawingCanvas->AttachBrush(imageBrush_);
            drawingCanvas->DrawImageRect(*image, rect, options_);
            drawingCanvas->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                canvasImage.sHeight + canvasImage.sy);
            drawingCanvas->AttachBrush(imageBrush_);
            drawingCanvas->DrawImageRect(
                *image, srcRect, dstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
            drawingCanvas->DetachBrush();
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

std::unique_ptr<ImageData> RosenRenderOffscreenCanvas::GetImageData(
    double left, double top, double width, double height)
{
    double viewScale = 1.0;
    auto pipeline = pipelineContext_.Upgrade();
    if (pipeline) {
        viewScale = pipeline->GetViewScale();
    }
    // copy the bitmap to tempCanvas
#ifndef USE_ROSEN_DRAWING
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, width * viewScale, height * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);
    SkCanvas tempCanvas(tempCache);
    tempCanvas.drawImageRect(
        skBitmap_.asImage(), srcRect, dstRect, options_, nullptr, SkCanvas::kFast_SrcRectConstraint);

    // write color
    std::unique_ptr<uint8_t[]> pixels = std::make_unique<uint8_t[]>(size * 4);
    tempCanvas.readPixels(imageInfo, pixels.get(), dirtyWidth * imageInfo.bytesPerPixel(), 0, 0);
#else
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect = RSRect(scaledLeft, scaledTop, width * viewScale + scaledLeft, height * viewScale + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    RSBitmap tempCache;
    tempCache.Build(width, height, format);
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    RSImage rsImage;
    rsImage.BuildFromBitmap(bitmap_);
    tempCanvas.DrawImageRect(rsImage, srcRect, dstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    // write color
    uint8_t* pixels = static_cast<uint8_t*>(tempCache.GetPixels());
#endif
    std::unique_ptr<ImageData> imageData = std::make_unique<ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data blue, green, red, alpha
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
    }
    return imageData;
}

void RosenRenderOffscreenCanvas::Save()
{
    SaveStates();
#ifndef USE_ROSEN_DRAWING
    skCanvas_->save();
#else
    canvas_->Save();
#endif
}

void RosenRenderOffscreenCanvas::Restore()
{
    RestoreStates();
#ifndef USE_ROSEN_DRAWING
    skCanvas_->restore();
#else
    canvas_->Restore();
#endif
}

std::string RosenRenderOffscreenCanvas::ToDataURL(const std::string& type, const double quality)
{
    auto pipeline = pipelineContext_.Upgrade();
    if (!pipeline) {
        return UNSUPPORTED;
    }
    std::string mimeType = GetMimeType(type);
    double qua = GetQuality(type, quality);
#ifndef USE_ROSEN_DRAWING
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width_, height_, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));
    SkCanvas tempCanvas(tempCache);
    double viewScale = pipeline->GetViewScale();
    tempCanvas.clear(SK_ColorTRANSPARENT);
    tempCanvas.scale(1.0 / viewScale, 1.0 / viewScale);
    // The return value of the dual framework interface has no alpha
    tempCanvas.drawImage(skBitmap_.asImage(), 0.0f, 0.0f);

    SkPixmap src;
    bool success = tempCache.peekPixels(&src);
#else
    RSBitmap tempCache;
    tempCache.Build(width_, height_,
        { RSColorType::COLORTYPE_BGRA_8888,
            (mimeType == IMAGE_JPEG) ? RSAlphaType::ALPHATYPE_OPAQUE : RSAlphaType::ALPHATYPE_UNPREMUL });
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    double viewScale = pipeline->GetViewScale();
    tempCanvas.Clear(RSColor::COLOR_TRANSPARENT);
    tempCanvas.Scale(1.0 / viewScale, 1.0 / viewScale);
    tempCanvas.DrawBitmap(bitmap_, 0.0f, 0.0f);

    auto skiaBitmap = tempCache.GetImpl<Rosen::Drawing::SkiaBitmap>();
    CHECK_NULL_RETURN(skiaBitmap, UNSUPPORTED);
    auto& skBitmap = skiaBitmap->ExportSkiaBitmap();
    SkPixmap src;
    bool success = skBitmap.peekPixels(&src);
#endif
    if (!success) {
        LOGE("ToDataURL failed,the bitmap does not have access to pixel data");
        return UNSUPPORTED;
    }
    SkDynamicMemoryWStream dst;
    if (mimeType == IMAGE_JPEG) {
        SkJpegEncoder::Options options;
        options.fQuality = qua;
        success = SkJpegEncoder::Encode(&dst, src, options);
    } else if (mimeType == IMAGE_WEBP) {
        SkWebpEncoder::Options options;
        options.fQuality = qua * 100.0;
        success = SkWebpEncoder::Encode(&dst, src, options);
    } else {
        mimeType = IMAGE_PNG;
        SkPngEncoder::Options options;
        success = SkPngEncoder::Encode(&dst, src, options);
    }
    if (!success) {
        LOGE("ToDataURL failed,image encoding failed");
        return UNSUPPORTED;
    }
    auto result = dst.detachAsData();
    if (result == nullptr) {
        LOGE("DetachAsData failed when ToDataURL.");
        return UNSUPPORTED;
    }
    size_t len = SkBase64::Encode(result->data(), result->size(), nullptr);
    if (len > MAX_LENGTH) {
        LOGE("ToDataURL failed,The resolution of the image is greater than the maximum allowed resolution");
        return UNSUPPORTED;
    }
    SkString info(len);
#ifdef USE_NEW_SKIA
    SkBase64::Encode(result->data(), result->size(), info.data());
#else
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
#endif
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderOffscreenCanvas::UpdatePaintShader(SkPaint& paint, const Gradient& gradient)
{
    SkPoint beginPoint = SkPoint::Make(
        SkDoubleToScalar(gradient.GetBeginOffset().GetX()), SkDoubleToScalar(gradient.GetBeginOffset().GetY()));
    SkPoint endPoint = SkPoint::Make(
        SkDoubleToScalar(gradient.GetEndOffset().GetX()), SkDoubleToScalar(gradient.GetEndOffset().GetY()));
    SkPoint pts[2] = { beginPoint, endPoint };
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    std::stable_sort(gradientColors.begin(), gradientColors.end(),
        [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
    uint32_t colorsSize = gradientColors.size();
    SkColor colors[gradientColors.size()];
    float pos[gradientColors.size()];
    for (uint32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
        pos[i] = gradientColor.GetDimension().Value();
    }

    auto mode = SkTileMode::kClamp;

    sk_sp<SkShader> skShader = nullptr;
    if (gradient.GetType() == GradientType::LINEAR) {
        skShader = SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), mode);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            skShader = SkGradientShader::MakeRadial(
                endPoint, gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        } else {
            skShader = SkGradientShader::MakeTwoPointConical(beginPoint, gradient.GetInnerRadius(), endPoint,
                gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        }
    }
    paint.setShader(skShader);
}
#else
void RosenRenderOffscreenCanvas::UpdatePaintShader(RSPen* pen, RSBrush* brush, const Gradient& gradient)
{
    RSPoint beginPoint = RSPoint(static_cast<RSScalar>(gradient.GetBeginOffset().GetX()),
        static_cast<RSScalar>(gradient.GetBeginOffset().GetY()));
    RSPoint endPoint = RSPoint(
        static_cast<RSScalar>(gradient.GetEndOffset().GetX()), static_cast<RSScalar>(gradient.GetEndOffset().GetY()));
    std::vector<RSPoint> pts = { beginPoint, endPoint };
    auto gradientColors = gradient.GetColors();
    std::stable_sort(gradientColors.begin(), gradientColors.end(),
        [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
    uint32_t colorsSize = gradientColors.size();
    std::vector<RSColorQuad> colors(gradientColors.size(), 0);
    std::vector<RSScalar> pos(gradientColors.size(), 0);
    for (uint32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors.at(i) = gradientColor.GetColor().GetValue();
        pos.at(i) = gradientColor.GetDimension().Value();
    }

    auto mode = RSTileMode::CLAMP;
    std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
    if (gradient.GetType() == GradientType::LINEAR) {
        shaderEffect = RSShaderEffect::CreateLinearGradient(pts.at(0), pts.at(1), colors, pos, mode);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            shaderEffect =
                RSShaderEffect::CreateRadialGradient(pts.at(1), gradient.GetOuterRadius(), colors, pos, mode);
        } else {
            RSMatrix matrix;
            shaderEffect = RSShaderEffect::CreateTwoPointConical(pts.at(0), gradient.GetInnerRadius(), pts.at(1),
                gradient.GetOuterRadius(), colors, pos, mode, &matrix);
        }
    }
    if (pen) {
        pen->SetShaderEffect(shaderEffect);
    }
    if (brush) {
        brush->SetShaderEffect(shaderEffect);
    }
}
#endif

void RosenRenderOffscreenCanvas::BeginPath()
{
#ifndef USE_ROSEN_DRAWING
    skPath_.reset();
#else
    path_.Reset();
#endif
}

void RosenRenderOffscreenCanvas::ResetTransform()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->resetMatrix();
#else
    canvas_->ResetMatrix();
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderOffscreenCanvas::UpdatePaintShader(const Pattern& pattern, SkPaint& paint)
{
    auto context = pipelineContext_.Upgrade();
    if (!context) {
        return;
    }

    auto width = pattern.GetImageWidth();
    auto height = pattern.GetImageHeight();
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetSkImage(pattern.GetImgSrc(), context, Size(width, height))
                     : ImageProvider::GetSkImage(pattern.GetImgSrc(), context);
    if (!image) {
        LOGE("image is null");
        return;
    }
    static const LinearMapNode<void (*)(sk_sp<SkImage>, SkPaint&)> staticPattern[] = {
        { "no-repeat",
            [](sk_sp<SkImage> image, SkPaint& paint) {
                paint.setShader(
                    image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, SkSamplingOptions(), nullptr));
            } },
        { "repeat",
            [](sk_sp<SkImage> image, SkPaint& paint) {
                paint.setShader(
                    image->makeShader(SkTileMode::kRepeat, SkTileMode::kRepeat, SkSamplingOptions(), nullptr));
            } },
        { "repeat-x",
            [](sk_sp<SkImage> image, SkPaint& paint) {
                paint.setShader(
                    image->makeShader(SkTileMode::kRepeat, SkTileMode::kDecal, SkSamplingOptions(), nullptr));
            } },
        { "repeat-y",
            [](sk_sp<SkImage> image, SkPaint& paint) {
                paint.setShader(
                    image->makeShader(SkTileMode::kDecal, SkTileMode::kRepeat, SkSamplingOptions(), nullptr));
            } },
    };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern), pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        staticPattern[operatorIter].value(image, paint);
    }
}
#else
void RosenRenderOffscreenCanvas::UpdatePaintShader(const Pattern& pattern, RSPen* pen, RSBrush* brush)
{
    auto context = pipelineContext_.Upgrade();
    if (!context) {
        return;
    }

    auto width = pattern.GetImageWidth();
    auto height = pattern.GetImageHeight();
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetDrawingImage(pattern.GetImgSrc(), context, Size(width, height))
                     : ImageProvider::GetDrawingImage(pattern.GetImgSrc(), context);
    if (!image) {
        LOGE("image is null");
        return;
    }
    static const LinearMapNode<void (*)(std::shared_ptr<RSImage>&, std::shared_ptr<RSShaderEffect>&)>
        staticPattern[] = {
            { "no-repeat",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::DECAL, RSTileMode::DECAL, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::REPEAT, RSTileMode::REPEAT, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat-x",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::REPEAT, RSTileMode::DECAL, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat-y",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::DECAL, RSTileMode::REPEAT, RSSamplingOptions(), RSMatrix());
                } },
        };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern), pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
        staticPattern[operatorIter].value(image, shaderEffect);
        if (pen) {
            pen->SetShaderEffect(shaderEffect);
        }
        if (brush) {
            brush->SetShaderEffect(shaderEffect);
        }
    }
}
#endif

void RosenRenderOffscreenCanvas::Arc(const ArcParam& param)
{
    double left = param.x - param.radius;
    double top = param.y - param.radius;
    double right = param.x + param.radius;
    double bottom = param.y + param.radius;
    double startAngle = param.startAngle * HALF_CIRCLE_ANGLE / ACE_PI;
    double endAngle = param.endAngle * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + startAngle), SkDoubleToScalar(half), false);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + half + startAngle), SkDoubleToScalar(sweepAngle), false);
    } else {
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(sweepAngle), false);
    }
#else
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        path_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        path_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        path_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        path_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        path_.ArcTo(point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        path_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
#endif
}

void RosenRenderOffscreenCanvas::ClearRect(Rect rect)
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setBlendMode(SkBlendMode::kClear);
    auto skRect = SkRect::MakeLTRB(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    skCanvas_->drawRect(skRect, paint);
#else
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetBlendMode(RSBlendMode::CLEAR);
    auto drawingRect = RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    canvas_->AttachBrush(brush);
    canvas_->DrawRect(drawingRect);
    canvas_->DetachBrush();
#endif
}

void RosenRenderOffscreenCanvas::StrokeRect(Rect rect)
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    SkRect skRect = SkRect::MakeLTRB(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);

        RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawRect(skRect, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    auto pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    RSRect drawingRect = RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(drawingRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, canvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(&pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachPen(pen);
        canvas_->DrawRect(drawingRect);
        canvas_->DetachPen();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawRect(drawingRect);
        cacheCanvas_->DetachPen();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::Stroke()
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawPath(skPath_, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    auto pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(path_, shadow_, canvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(&pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachPen(pen);
        canvas_->DrawPath(path_);
        canvas_->DetachPen();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawPath(path_);
        cacheCanvas_->DetachPen();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::Stroke(const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        return;
    }
    ParsePath2D(path);
    Path2DStroke();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    path2d_.Reset();
#endif
}

#ifndef USE_ROSEN_DRAWING
SkPaint RosenRenderOffscreenCanvas::GetStrokePaint()
{
    static const LinearEnumMapNode<LineJoinStyle, SkPaint::Join> skLineJoinTable[] = {
        { LineJoinStyle::MITER, SkPaint::Join::kMiter_Join },
        { LineJoinStyle::ROUND, SkPaint::Join::kRound_Join },
        { LineJoinStyle::BEVEL, SkPaint::Join::kBevel_Join },
    };
    static const LinearEnumMapNode<LineCapStyle, SkPaint::Cap> skLineCapTable[] = {
        { LineCapStyle::BUTT, SkPaint::Cap::kButt_Cap },
        { LineCapStyle::ROUND, SkPaint::Cap::kRound_Cap },
        { LineCapStyle::SQUARE, SkPaint::Cap::kSquare_Cap },
    };
    SkPaint paint;
    paint.setColor(strokeState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeJoin(ConvertEnumToSkEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), SkPaint::Join::kMiter_Join));
    paint.setStrokeCap(ConvertEnumToSkEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), SkPaint::Cap::kButt_Cap));
    paint.setStrokeWidth(static_cast<SkScalar>(strokeState_.GetLineWidth()));
    paint.setStrokeMiter(static_cast<SkScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(paint);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    return paint;
}
#else
RSPen RosenRenderOffscreenCanvas::GetStrokePaint()
{
    static const LinearEnumMapNode<LineJoinStyle, RSPen::JoinStyle> skLineJoinTable[] = {
        { LineJoinStyle::MITER, RSPen::JoinStyle::MITER_JOIN },
        { LineJoinStyle::ROUND, RSPen::JoinStyle::ROUND_JOIN },
        { LineJoinStyle::BEVEL, RSPen::JoinStyle::BEVEL_JOIN },
    };
    static const LinearEnumMapNode<LineCapStyle, RSPen::CapStyle> skLineCapTable[] = {
        { LineCapStyle::BUTT, RSPen::CapStyle::FLAT_CAP },
        { LineCapStyle::ROUND, RSPen::CapStyle::ROUND_CAP },
        { LineCapStyle::SQUARE, RSPen::CapStyle::SQUARE_CAP },
    };
    RSPen pen;
    pen.SetColor(strokeState_.GetColor().GetValue());
    pen.SetJoinStyle(ConvertEnumToDrawingEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), RSPen::JoinStyle::MITER_JOIN));
    pen.SetCapStyle(ConvertEnumToDrawingEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), RSPen::CapStyle::FLAT_CAP));
    pen.SetWidth(static_cast<RSScalar>(strokeState_.GetLineWidth()));
    pen.SetMiterLimit(static_cast<RSScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(pen);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        pen.SetAlphaF(globalState_.GetAlpha());
    }
    return pen;
}
#endif

void RosenRenderOffscreenCanvas::SetAntiAlias(bool isEnabled)
{
    antiAlias_ = isEnabled;
}
bool RosenRenderOffscreenCanvas::HasShadow() const
{
    return !(NearZero(shadow_.GetOffset().GetX()) && NearZero(shadow_.GetOffset().GetY()) &&
             NearZero(shadow_.GetBlurRadius()));
}

bool RosenRenderOffscreenCanvas::HasImageShadow() const
{
    return !(NearZero(imageShadow_.GetOffset().GetX()) && NearZero(imageShadow_.GetOffset().GetY()) &&
             NearZero(imageShadow_.GetBlurRadius()));
}

void RosenRenderOffscreenCanvas::Path2DAddPath(const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    SkPath out;
    SkParsePath::FromSVGString(args.cmds.c_str(), &out);
    skPath2d_.addPath(out);
#else
    RSRecordingPath out;
    out.BuildFromSVGString(args.cmds.c_str());
    path2d_.AddPath(out);
#endif
}

void RosenRenderOffscreenCanvas::Path2DSetTransform(const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
    skMatrix.setAll(scaleX, skewY, translateX, skewX, scaleY, translateY, 0, 0, 1);
    skPath2d_.transform(skMatrix);
#else
    RSMatrix matrix;
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
    matrix.SetMatrix(scaleX, skewY, translateX, skewX, scaleY, translateY, 0, 0, 1);
    path2d_.Transform(matrix);
#endif
}

void RosenRenderOffscreenCanvas::Path2DMoveTo(const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.moveTo(x, y);
#else
    path2d_.MoveTo(x, y);
#endif
}

void RosenRenderOffscreenCanvas::Path2DLineTo(const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.lineTo(x, y);
#else
    path2d_.LineTo(x, y);
#endif
}

void RosenRenderOffscreenCanvas::Path2DArc(const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
    double r = args.para3;
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(x - r, y - r, x + r, y + r);
    double startAngle = args.para4 * HALF_CIRCLE_ANGLE / ACE_PI;
    double endAngle = args.para5 * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (!NearZero(args.para6)) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE + HALF_CIRCLE_ANGLE, sweepAngle, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
#else
    RSPoint point1(x - r, y - r);
    RSPoint point2(x + r, y + r);
    double startAngle = args.para4 * HALF_CIRCLE_ANGLE / ACE_PI;
    double endAngle = args.para5 * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (!NearZero(args.para6)) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        path2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        path2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        path2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        path2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
        path2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE + HALF_CIRCLE_ANGLE, sweepAngle);
    } else {
        path2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
#endif
}

void RosenRenderOffscreenCanvas::Path2DArcTo(const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    double x1 = args.para1;
    double y1 = args.para2;
    double x2 = args.para3;
    double y2 = args.para4;
    double r = args.para5;
    skPath2d_.arcTo(x1, y1, x2, y2, r);
#else
    LOGE("Drawing is not supported");
#endif
}

void RosenRenderOffscreenCanvas::Path2DQuadraticCurveTo(const PathArgs& args)
{
    double cpx = args.para1;
    double cpy = args.para2;
    double x = args.para3;
    double y = args.para4;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.quadTo(cpx, cpy, x, y);
#else
    path2d_.QuadTo(cpx, cpy, x, y);
#endif
}

void RosenRenderOffscreenCanvas::Path2DBezierCurveTo(const PathArgs& args)
{
    double cp1x = args.para1;
    double cp1y = args.para2;
    double cp2x = args.para3;
    double cp2y = args.para4;
    double x = args.para5;
    double y = args.para6;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.cubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
#else
    path2d_.CubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
#endif
}

void RosenRenderOffscreenCanvas::Path2DEllipse(const PathArgs& args)
{
    if (NearEqual(args.para6, args.para7)) {
        return; // Just return when startAngle is same as endAngle.
    }

    double x = args.para1;
    double y = args.para2;
    double rx = args.para3;
    double ry = args.para4;
    double rotation = args.para5 * HALF_CIRCLE_ANGLE / ACE_PI;
    double startAngle = std::fmod(args.para6, ACE_PI * 2.0);
    double endAngle = std::fmod(args.para7, ACE_PI * 2.0);
    bool anticlockwise = NearZero(args.para8) ? false : true;
    startAngle = (startAngle < 0.0 ? startAngle + ACE_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    endAngle = (endAngle < 0.0 ? endAngle + ACE_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(x - rx, y - ry, x + rx, y + ry);

    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, x, y);
        skPath2d_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, x, y);
        skPath2d_.transform(matrix);
    }
#else
    RSPoint point1(x - rx, y - ry);
    RSPoint point2(x + rx, y + ry);

    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, x, y);
        path2d_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        path2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        path2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        path2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, x, y);
        path2d_.Transform(matrix);
    }
#endif
}

void RosenRenderOffscreenCanvas::Path2DRect(const PathArgs& args)
{
    double left = args.para1;
    double top = args.para2;
    double right = args.para3 + args.para1;
    double bottom = args.para4 + args.para2;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.addRect(SkRect::MakeLTRB(left, top, right, bottom));
#else
    path2d_.AddRect(RSRect(left, top, right, bottom));
#endif
}

void RosenRenderOffscreenCanvas::Path2DClosePath(const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    skPath2d_.close();
#else
    path2d_.Close();
#endif
}

void RosenRenderOffscreenCanvas::Path2DStroke()
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawPath(skPath2d_, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    RSPen pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(path2d_, shadow_, canvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(&pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachPen(pen);
        canvas_->DrawPath(path2d_);
        canvas_->DetachPen();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawPath(path2d_);
        cacheCanvas_->DetachPen();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::Path2DFill()
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        InitCachePaint();
        cacheCanvas_->drawPath(skPath2d_, paint);

        skCanvas_->drawImage(cacheBitmap_.asImage(), 0, 0, SkSamplingOptions(), &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
#else
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(path2d_, shadow_, canvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        canvas_->AttachBrush(brush);
        canvas_->DrawPath(path2d_);
        canvas_->DetachBrush();
    } else {
        InitCachePaint();
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawPath(path2d_);
        cacheCanvas_->DetachBrush();
        canvas_->AttachBrush(cacheBrush_);
        canvas_->DrawBitmap(cacheBitmap_, 0, 0);
        canvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
#endif
}

void RosenRenderOffscreenCanvas::Path2DClip()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->clipPath(skPath2d_);
#else
    canvas_->ClipPath(path2d_, RSClipOp::INTERSECT);
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderOffscreenCanvas::UpdateLineDash(SkPaint& paint)
{
    if (!strokeState_.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState_.GetLineDash().lineDash;
        SkScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = SkDoubleToScalar(lineDashState[i]);
        }
        SkScalar phase = SkDoubleToScalar(strokeState_.GetLineDash().dashOffset);
        paint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
    }
}
#else
void RosenRenderOffscreenCanvas::UpdateLineDash(RSPen& pen)
{
    if (!strokeState_.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState_.GetLineDash().lineDash;
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(strokeState_.GetLineDash().dashOffset);
        pen.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }
}
#endif

void RosenRenderOffscreenCanvas::ArcTo(const ArcToParam& param)
{
#ifndef USE_ROSEN_DRAWING
    double x1 = param.x1;
    double y1 = param.y1;
    double x2 = param.x2;
    double y2 = param.y2;
    double radius = param.radius;
    skPath_.arcTo(SkDoubleToScalar(x1), SkDoubleToScalar(y1), SkDoubleToScalar(x2), SkDoubleToScalar(y2),
        SkDoubleToScalar(radius));
#else
    LOGE("Drawing is not supported");
#endif
}
void RosenRenderOffscreenCanvas::MoveTo(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skPath_.moveTo(SkDoubleToScalar(x), SkDoubleToScalar(y));
#else
    path_.MoveTo(static_cast<RSScalar>(x), static_cast<RSScalar>(y));
#endif
}
void RosenRenderOffscreenCanvas::ClosePath()
{
#ifndef USE_ROSEN_DRAWING
    skPath_.close();
#else
    path_.Close();
#endif
}

void RosenRenderOffscreenCanvas::Rotate(double angle)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->rotate(angle * 180 / ACE_PI);
#else
    canvas_->Rotate(angle * 180 / ACE_PI);
#endif
}
void RosenRenderOffscreenCanvas::Scale(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->scale(x, y);
#else
    canvas_->Scale(x, y);
#endif
}

void RosenRenderOffscreenCanvas::FillText(const std::string& text, double x, double y, const PaintState& state)
{
    if (!UpdateOffParagraph(text, false, state, HasShadow())) {
        return;
    }
    PaintText(text, x, y, false, HasShadow());
}

void RosenRenderOffscreenCanvas::StrokeText(const std::string& text, double x, double y, const PaintState& state)
{
    if (HasShadow()) {
        if (!UpdateOffParagraph(text, true, state, true)) {
            return;
        }
        PaintText(text, x, y, true, true);
    }

    if (!UpdateOffParagraph(text, true, state)) {
        return;
    }
    PaintText(text, x, y, true);
}

double RosenRenderOffscreenCanvas::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#ifndef USE_ROSEN_DRAWING

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), pipelineContext_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetMaxIntrinsicWidth();
}

double RosenRenderOffscreenCanvas::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#ifndef USE_ROSEN_DRAWING

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), pipelineContext_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetHeight();
}

TextMetrics RosenRenderOffscreenCanvas::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#ifndef USE_ROSEN_DRAWING

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), pipelineContext_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);

    auto textAlign = state.GetTextAlign();
    auto textBaseLine = state.GetTextStyle().GetTextBaseline();

    auto width = paragraph->GetMaxIntrinsicWidth();
    auto height = paragraph->GetHeight();

    auto actualBoundingBoxLeft = -GetAlignOffset(text, textAlign, paragraph);
    auto actualBoundingBoxRight = width - actualBoundingBoxLeft;
    auto actualBoundingBoxAscent = -GetBaselineOffset(textBaseLine, paragraph);
    auto actualBoundingBoxDescent = height - actualBoundingBoxAscent;

    return { width, height, actualBoundingBoxLeft, actualBoundingBoxRight, actualBoundingBoxAscent,
        actualBoundingBoxDescent };
}

void RosenRenderOffscreenCanvas::PaintText(const std::string& text, double x, double y, bool isStroke, bool hasShadow)
{
    paragraph_->Layout(width_);
    if (width_ > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
#ifndef USE_ROSEN_DRAWING
    auto align = isStroke ? strokeState_.GetTextAlign() : fillState_.GetTextAlign();
    double dx = x + GetAlignOffset(text, align, paragraph_);
    auto baseline =
        isStroke ? strokeState_.GetTextStyle().GetTextBaseline() : fillState_.GetTextStyle().GetTextBaseline();
    double dy = y + GetBaselineOffset(baseline, paragraph_);

    if (hasShadow) {
        skCanvas_->save();
        auto shadowOffsetX = shadow_.GetOffset().GetX();
        auto shadowOffsetY = shadow_.GetOffset().GetY();
        paragraph_->Paint(skCanvas_.get(), dx + shadowOffsetX, dy + shadowOffsetY);
        skCanvas_->restore();
        return;
    }
    paragraph_->Paint(skCanvas_.get(), dx, dy);
#else
    if (hasShadow) {
        canvas_->Save();
        LOGE("Drawing is not supported");
        canvas_->Restore();
        return;
    }
    LOGE("Drawing is not supported");
#endif
}

double RosenRenderOffscreenCanvas::GetAlignOffset(
    const std::string& text, TextAlign align, std::unique_ptr<Rosen::Typography>& paragraph)
{
    double x = 0.0;
    switch (align) {
        case TextAlign::LEFT:
            x = 0.0;
            break;
        case TextAlign::START:
            x = (GetTextDirection(text) == TextDirection::LTR) ? 0.0 : -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::RIGHT:
            x = -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::END:
            x = (GetTextDirection(text) == TextDirection::LTR) ? -paragraph->GetMaxIntrinsicWidth() : 0.0;
            break;
        case TextAlign::CENTER:
            x = -paragraph->GetMaxIntrinsicWidth() / 2;
            break;
        default:
            x = 0.0;
            break;
    }
    return x;
}

TextDirection RosenRenderOffscreenCanvas::GetTextDirection(const std::string& text)
{
    auto wstring = StringUtils::ToWstring(text);
    // Find first strong direction char.
    for (const auto& charInStr : wstring) {
        auto direction = u_charDirection(charInStr);
        if (direction == UCharDirection::U_LEFT_TO_RIGHT) {
            return TextDirection::LTR;
        }
        if (direction == UCharDirection::U_RIGHT_TO_LEFT || direction == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
            return TextDirection::RTL;
        }
    }
    return TextDirection::INHERIT;
}

void RosenRenderOffscreenCanvas::InitCachePaint()
{
#ifndef USE_ROSEN_DRAWING
    cachePaint_.setBlendMode(
        ConvertEnumToSkEnum(globalState_.GetType(), SK_BLEND_MODE_TABLE, BLEND_MODE_SIZE, SkBlendMode::kSrcOver));
#else
    cacheBrush_.SetBlendMode(ConvertEnumToDrawingEnum(
        globalState_.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
#endif
}

bool RosenRenderOffscreenCanvas::UpdateOffParagraph(
    const std::string& text, bool isStroke, const PaintState& state, bool hasShadow)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    if (isStroke) {
        style.textAlign = ConvertTxtTextAlign(strokeState_.GetTextAlign());
    } else {
        style.textAlign = ConvertTxtTextAlign(fillState_.GetTextAlign());
    }
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#ifndef USE_ROSEN_DRAWING

    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    if (!fontCollection) {
        return false;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    if (!isStroke && hasShadow) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.SetX(shadow_.GetOffset().GetX());
        txtShadow.offset.SetY(shadow_.GetOffset().GetY());
        txtShadow.blurRadius = shadow_.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateTextStyleForeground(isStroke, txtStyle, hasShadow);
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
    return true;
}

void RosenRenderOffscreenCanvas::UpdateTextStyleForeground(bool isStroke, Rosen::TextStyle& txtStyle, bool hasShadow)
{
    using namespace Constants;
#ifndef USE_ROSEN_DRAWING
    if (!isStroke) {
        txtStyle.color = ConvertSkColor(fillState_.GetColor());
        txtStyle.fontSize = fillState_.GetTextStyle().GetFontSize().Value();
        ConvertTxtStyle(fillState_.GetTextStyle(), pipelineContext_, txtStyle);
        if (fillState_.GetGradient().IsValid()) {
            SkPaint paint;
            paint.setStyle(SkPaint::Style::kFill_Style);
            UpdatePaintShader(paint, fillState_.GetGradient());
            txtStyle.foreground = paint;
        }
        if (globalState_.HasGlobalAlpha()) {
            if (txtStyle.foreground.has_value()) {
                txtStyle.foreground->setColor(fillState_.GetColor().GetValue());
                txtStyle.foreground->setAlphaf(globalState_.GetAlpha()); // set alpha after color
            } else {
                SkPaint paint;
                paint.setColor(fillState_.GetColor().GetValue());
                paint.setAlphaf(globalState_.GetAlpha()); // set alpha after color
                txtStyle.foreground = paint;
            }
        }
    } else {
        // use foreground to draw stroke
        SkPaint paint = GetStrokePaint();
        ConvertTxtStyle(strokeState_.GetTextStyle(), pipelineContext_, txtStyle);
        txtStyle.fontSize = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid()) {
            UpdatePaintShader(paint, strokeState_.GetGradient());
        }
        if (hasShadow) {
            paint.setColor(shadow_.GetColor().GetValue());

            paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle,
                RosenDecorationPainter::ConvertRadiusToSigma(shadow_.GetBlurRadius())));
        }
        txtStyle.foreground = paint;
    }
#else
    LOGE("Drawing is not supported");
#endif
}

double RosenRenderOffscreenCanvas::GetBaselineOffset(
    TextBaseline baseline, std::unique_ptr<Rosen::Typography>& paragraph)
{
    double y = 0.0;
    switch (baseline) {
        case TextBaseline::ALPHABETIC:
            y = -paragraph->GetAlphabeticBaseline();
            break;
        case TextBaseline::IDEOGRAPHIC:
            y = -paragraph->GetIdeographicBaseline();
            break;
        case TextBaseline::BOTTOM:
            y = -paragraph->GetHeight();
            break;
        case TextBaseline::TOP:
            y = 0.0;
            break;
        case TextBaseline::MIDDLE:
            y = -paragraph->GetHeight() / 2;
            break;
        case TextBaseline::HANGING:
            y = -HANGING_PERCENT * (paragraph->GetHeight() - paragraph->GetAlphabeticBaseline());
            break;
        default:
            y = -paragraph->GetAlphabeticBaseline();
            break;
    }
    return y;
}
void RosenRenderOffscreenCanvas::LineTo(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skPath_.lineTo(SkDoubleToScalar(x), SkDoubleToScalar(y));
#else
    path_.LineTo(static_cast<RSScalar>(x), static_cast<RSScalar>(y));
#endif
}
void RosenRenderOffscreenCanvas::BezierCurveTo(const BezierCurveParam& param)
{
#ifndef USE_ROSEN_DRAWING
    skPath_.cubicTo(SkDoubleToScalar(param.cp1x), SkDoubleToScalar(param.cp1y), SkDoubleToScalar(param.cp2x),
        SkDoubleToScalar(param.cp2y), SkDoubleToScalar(param.x), SkDoubleToScalar(param.y));
#else
    path_.CubicTo(static_cast<RSScalar>(param.cp1x), static_cast<RSScalar>(param.cp1y),
        static_cast<RSScalar>(param.cp2x), static_cast<RSScalar>(param.cp2y), static_cast<RSScalar>(param.x),
        static_cast<RSScalar>(param.y));
#endif
}
void RosenRenderOffscreenCanvas::QuadraticCurveTo(const QuadraticCurveParam& param)
{
#ifndef USE_ROSEN_DRAWING
    skPath_.quadTo(
        SkDoubleToScalar(param.cpx), SkDoubleToScalar(param.cpy), SkDoubleToScalar(param.x), SkDoubleToScalar(param.y));
#else
    path_.QuadTo(static_cast<RSScalar>(param.cpx), static_cast<RSScalar>(param.cpy), static_cast<RSScalar>(param.x),
        static_cast<RSScalar>(param.y));
#endif
}
void RosenRenderOffscreenCanvas::Ellipse(const EllipseParam& param)
{
    // Init the start and end angle, then calculated the sweepAngle.
    double startAngle = std::fmod(param.startAngle, ACE_PI * 2.0);
    double endAngle = std::fmod(param.endAngle, ACE_PI * 2.0);
    startAngle = (startAngle < 0.0 ? startAngle + ACE_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    endAngle = (endAngle < 0.0 ? endAngle + ACE_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    if (NearEqual(param.startAngle, param.endAngle)) {
        return; // Just return when startAngle is same as endAngle.
    }
    double rotation = param.rotation * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }

    // Init the oval Rect(left, top, right, bottom).
    double left = param.x - param.radiusX;
    double top = param.y - param.radiusY;
    double right = param.x + param.radiusX;
    double bottom = param.y + param.radiusY;
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, param.x, param.y);
        skPath_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, param.x, param.y);
        skPath_.transform(matrix);
    }
#else
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, param.x, param.y);
        path_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        path_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        path_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        path_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, param.x, param.y);
        path_.Transform(matrix);
    }
#endif
}
void RosenRenderOffscreenCanvas::SetTransform(const TransformParam& param)
{
    auto pipeline = pipelineContext_.Upgrade();
    if (!pipeline) {
        return;
    }

    // use physical pixel to store bitmap
    double viewScale = pipeline->GetViewScale();

#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX * viewScale, param.skewY * viewScale, param.translateX, param.skewX * viewScale,
        param.scaleY * viewScale, param.translateY, 0, 0, 1);
    skCanvas_->setMatrix(skMatrix);
#else
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX * viewScale, param.skewY * viewScale, param.translateX, param.skewX * viewScale,
        param.scaleY * viewScale, param.translateY, 0, 0, 1);
    canvas_->SetMatrix(matrix);
#endif
}
void RosenRenderOffscreenCanvas::Transform(const TransformParam& param)
{
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    skCanvas_->concat(skMatrix);
#else
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    canvas_->ConcatMatrix(matrix);
#endif
}
void RosenRenderOffscreenCanvas::Translate(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->translate(x, y);
#else
    canvas_->Translate(x, y);
#endif
}

void RosenRenderOffscreenCanvas::TranspareCmdToPath(const RefPtr<CanvasPath2D>& path)
{
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    path2d_.Reset();
#endif
    for (const auto& [cmd, args] : path->GetCaches()) {
        switch (cmd) {
            case PathCmd::CMDS: {
                Path2DAddPath(args);
                break;
            }
            case PathCmd::TRANSFORM: {
                Path2DSetTransform(args);
                break;
            }
            case PathCmd::MOVE_TO: {
                Path2DMoveTo(args);
                break;
            }
            case PathCmd::LINE_TO: {
                Path2DLineTo(args);
                break;
            }
            case PathCmd::ARC: {
                Path2DArc(args);
                break;
            }
            case PathCmd::ARC_TO: {
                Path2DArcTo(args);
                break;
            }
            case PathCmd::QUADRATIC_CURVE_TO: {
                Path2DQuadraticCurveTo(args);
                break;
            }
            case PathCmd::BEZIER_CURVE_TO: {
                Path2DBezierCurveTo(args);
                break;
            }
            case PathCmd::ELLIPSE: {
                Path2DEllipse(args);
                break;
            }
            case PathCmd::RECT: {
                Path2DRect(args);
                break;
            }
            case PathCmd::CLOSE_PATH: {
                Path2DClosePath(args);
                break;
            }
            default: {
                break;
            }
        }
    }
}

#ifndef USE_ROSEN_DRAWING
bool RosenRenderOffscreenCanvas::IsPointInPathByColor(double x, double y, SkPath& path, SkColor colorMatch)
{
    auto imageInfo =
        SkImageInfo::Make(width_, height_, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap skBitmap;
    skBitmap.allocPixels(imageInfo);
    std::unique_ptr<SkCanvas> skCanvas = std::make_unique<SkCanvas>(skBitmap);

    SkPaint paint;
    paint.setColor(SK_ColorRED);
    paint.setStyle(SkPaint::Style::kFill_Style);
    skCanvas->drawPath(path, paint);

    paint.setColor(SK_ColorBLUE);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(static_cast<SkScalar>(strokeState_.GetLineWidth()));
    skCanvas->drawPath(path, paint);

    SkColor color = skBitmap.getColor(x, y);
    if (color == colorMatch) {
        return true;
    }
    return false;
}
#else
bool RosenRenderOffscreenCanvas::IsPointInPathByColor(double x, double y, RSPath& path, RSColorQuad colorMatch)
{
    RSBitmapFormat format { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };

    RSBitmap bitmap;
    bitmap.Build(width_, height_, format);
    std::unique_ptr<RSCanvas> canvas = std::make_unique<RSCanvas>();
    canvas->Bind(bitmap);

    RSBrush brush;
    brush.SetColor(RSColor::COLOR_RED);
    canvas->AttachBrush(brush);
    canvas->DrawPath(path);
    canvas->DetachBrush();

    RSPen pen;
    pen.SetColor(RSColor::COLOR_BLUE);
    pen.SetWidth(static_cast<RSScalar>(strokeState_.GetLineWidth()));
    canvas->AttachPen(pen);
    canvas->DrawPath(path);
    canvas->DetachPen();

    RSColorQuad color = bitmap.GetColor(x, y);
    if (color == colorMatch) {
        return true;
    }
    return false;
}
#endif

bool RosenRenderOffscreenCanvas::IsPointInPath(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    return IsPointInPathByColor(x, y, skPath_, SK_ColorRED);
#else
    return IsPointInPathByColor(x, y, path_, RSColor::COLOR_RED);
#endif
}

bool RosenRenderOffscreenCanvas::IsPointInPath(const RefPtr<CanvasPath2D>& path, double x, double y)
{
    TranspareCmdToPath(path);
#ifndef USE_ROSEN_DRAWING
    return IsPointInPathByColor(x, y, skPath2d_, SK_ColorRED);
#else
    return IsPointInPathByColor(x, y, path2d_, RSColor::COLOR_RED);
#endif
}

bool RosenRenderOffscreenCanvas::IsPointInStroke(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    return IsPointInPathByColor(x, y, skPath_, SK_ColorBLUE);
#else
    return IsPointInPathByColor(x, y, path_, RSColor::COLOR_BLUE);
#endif
}

bool RosenRenderOffscreenCanvas::IsPointInStroke(const RefPtr<CanvasPath2D>& path, double x, double y)
{
    TranspareCmdToPath(path);
#ifndef USE_ROSEN_DRAWING
    return IsPointInPathByColor(x, y, skPath2d_, SK_ColorBLUE);
#else
    return IsPointInPathByColor(x, y, path2d_, RSColor::COLOR_BLUE);
#endif
}

void RosenRenderOffscreenCanvas::InitFilterFunc()
{
    filterFunc_["grayscale"] = [&](const std::string& percentage) { SetGrayFilter(percentage); };
    filterFunc_["sepia"] = [&](const std::string& percentage) { SetSepiaFilter(percentage); };
    filterFunc_["invert"] = [&](const std::string& percentage) { SetInvertFilter(percentage); };
    filterFunc_["opacity"] = [&](const std::string& percentage) { SetOpacityFilter(percentage); };
    filterFunc_["brightness"] = [&](const std::string& percentage) { SetBrightnessFilter(percentage); };
    filterFunc_["contrast"] = [&](const std::string& percentage) { SetContrastFilter(percentage); };
    filterFunc_["blur"] = [&](const std::string& percentage) { SetBlurFilter(percentage); };
    filterFunc_["drop-shadow"] = [&](const std::string& percentage) { SetDropShadowFilter(percentage); };
    filterFunc_["saturate"] = [&](const std::string& percentage) { SetSaturateFilter(percentage); };
    filterFunc_["hue-rotate"] = [&](const std::string& percentage) { SetHueRotateFilter(percentage); };
}

bool RosenRenderOffscreenCanvas::GetFilterType(std::string& filterType, std::string& filterParam)
{
    std::string paramData = filterParam_;
    size_t index = paramData.find("(");
    if (index == std::string::npos) {
        return false;
    }
    filterType = paramData.substr(0, index);
    filterParam = paramData.substr(index + 1);
    size_t endeIndex = filterParam.find(")");
    if (endeIndex == std::string::npos) {
        return false;
    }
    filterParam.erase(endeIndex, 1);
    return true;
}

bool RosenRenderOffscreenCanvas::IsPercentStr(std::string& percent)
{
    if (percent.find("%") != std::string::npos) {
        size_t index = percent.find("%");
        percent = percent.substr(0, index);
        return true;
    }
    return false;
}

double RosenRenderOffscreenCanvas::PxStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        std::istringstream iss(result);
        iss >> ret;
    }
    return ret;
}

double RosenRenderOffscreenCanvas::BlurStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    size_t index1 = str.find("rem");
    size_t demIndex = std::string::npos;
    if (index != std::string::npos) {
        demIndex = index;
    }
    if (index1 != std::string::npos) {
        demIndex = index1;
    }
    if (demIndex != std::string::npos) {
        std::string result = str.substr(0, demIndex);
        std::istringstream iss(result);
        iss >> ret;
    }
    if (str.find("rem") != std::string::npos) {
        return ret * 15;
    }
    return ret;
}

void RosenRenderOffscreenCanvas::SetGrayFilter(const std::string& percent)
{
    std::string percentage = percent;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    std::istringstream iss(percentage);
    iss >> percentNum;
    if (hasPercent) {
        percentNum = percentNum / 100;
    }
    if (percentNum > 1) {
        percentNum = 1;
    }
    float otherColor = percentNum / 3;
    float primColor = 1 - 2 * otherColor;
    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = primColor;
    matrix[1] = matrix[2] = matrix[5] = matrix[7] = matrix[10] = matrix[11] = otherColor;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetSepiaFilter(const std::string& percent)
{
    std::string percentage = percent;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    std::istringstream iss(percentage);
    iss >> percentNum;
    if (hasPercent) {
        percentNum = percentNum / 100;
    }
    if (percentNum > 1) {
        percentNum = 1;
    }
    float matrix[20] = { 0 };
    matrix[0] = 1.0f - percentNum * 0.6412f;
    matrix[1] = percentNum * 0.7044f;
    matrix[2] = percentNum * 0.1368f;
    matrix[5] = percentNum * 0.2990f;
    matrix[6] = 1.0f - percentNum * 0.4130f;
    matrix[7] = percentNum * 0.1140f;
    matrix[10] = percentNum * 0.2392f;
    matrix[11] = percentNum * 0.4696f;
    matrix[12] = 1.0f - percentNum * 0.9088f;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetInvertFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * percentage;
    matrix[4] = matrix[9] = matrix[14] = percentage;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetOpacityFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = 1.0f;
    matrix[18] = percentage;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetBrightnessFilter(const std::string& percent)
{
    std::string perStr = percent;
    bool hasPercent = IsPercentStr(perStr);
    float percentage = 0.0f;
    std::istringstream iss(perStr);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    if (percentage < 0) {
        return;
    }
    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = percentage;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetContrastFilter(const std::string& percent)
{
    std::string perStr = percent;
    float percentage = 0.0f;
    bool hasPercent = IsPercentStr(perStr);
    std::istringstream iss(perStr);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }

    float matrix[20] = { 0 };
    matrix[0] = matrix[6] = matrix[12] = percentage;
    matrix[4] = matrix[9] = matrix[14] = 0.5f * (1 - percentage);
    matrix[18] = 1;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetBlurFilter(const std::string& percent)
{
#ifndef USE_ROSEN_DRAWING

    imagePaint_.setImageFilter(SkImageFilters::Blur(BlurStrToDouble(percent), BlurStrToDouble(percent), nullptr));
#else
    auto filter = imageBrush_.GetFilter();
    filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(
        BlurStrToDouble(percent), BlurStrToDouble(percent), RSTileMode::DECAL, nullptr));
    imageBrush_.SetFilter(filter);
#endif
}

void RosenRenderOffscreenCanvas::SetDropShadowFilter(const std::string& percent)
{
    std::vector<std::string> offsets;
    StringUtils::StringSplitter(percent, ' ', offsets);
    if (offsets.empty() || offsets.size() != 4) {
        return;
    }
    imageShadow_.SetOffsetX(PxStrToDouble(offsets[0]));
    imageShadow_.SetOffsetY(PxStrToDouble(offsets[1]));
    imageShadow_.SetBlurRadius(PxStrToDouble(offsets[2]));
    imageShadow_.SetColor(Color::FromString(offsets[3]));
}

void RosenRenderOffscreenCanvas::SetSaturateFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    bool hasPercent = IsPercentStr(percent);
    float percentage = 0.0f;
    std::istringstream iss(percent);
    iss >> percentage;
    if (hasPercent) {
        percentage = percentage / 100;
    }
    double N = percentage;
    float matrix[20] = { 0 };
    matrix[0] = 0.3086f * (1 - N) + N;
    matrix[1] = matrix[11] = 0.6094f * (1 - N);
    matrix[2] = matrix[7] = 0.0820f * (1 - N);
    matrix[5] = matrix[10] = 0.3086f * (1 - N);
    matrix[6] = 0.6094f * (1 - N) + N;
    matrix[12] = 0.0820f * (1 - N) + N;
    matrix[18] = 1.0f;
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetHueRotateFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    float degree = 0.0f;
    if (percent.find("deg") != std::string::npos) {
        size_t index = percent.find("deg");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
    }
    if (percent.find("turn") != std::string::npos) {
        size_t index = percent.find("turn");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
        degree = degree * 360;
    }
    if (percent.find("rad") != std::string::npos) {
        size_t index = percent.find("rad");
        percent = percent.substr(0, index);
        std::istringstream iss(percent);
        iss >> degree;
        degree = degree * 180 / 3.142f;
    }

    while (GreatOrEqual(degree, 360)) {
        degree -= 360;
    }

    float matrix[20] = { 0 };
    int32_t type = degree / 120;
    float N = (degree - 120 * type) / 120;
    switch (type) {
        case 0:
            // degree is in 0-120
            matrix[0] = matrix[6] = matrix[12] = 1 - N;
            matrix[2] = matrix[5] = matrix[11] = N;
            matrix[18] = 1.0f;
            break;
        case 1:
            // degree is in 120-240
            matrix[1] = matrix[7] = matrix[10] = N;
            matrix[2] = matrix[5] = matrix[11] = 1 - N;
            matrix[18] = 1.0f;
            break;
        case 2:
            // degree is in 240-360
            matrix[0] = matrix[6] = matrix[11] = N;
            matrix[1] = matrix[7] = matrix[10] = 1 - N;
            matrix[18] = 1.0f;
            break;
        default:
            break;
    }
    SetColorFilter(matrix);
}

void RosenRenderOffscreenCanvas::SetColorFilter(float matrix[20])
{
#ifndef USE_ROSEN_DRAWING

    imagePaint_.setColorFilter(SkColorFilters::Matrix(matrix));
#else
    RSColorMatrix colorMatrix;
    matrix[4] *= 255;
    matrix[9] *= 255;
    matrix[14] *= 255;
    matrix[19] *= 255;
    colorMatrix.SetArray(matrix);
    auto filter = imageBrush_.GetFilter();
    filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
    imageBrush_.SetFilter(filter);
#endif
}
} // namespace OHOS::Ace
