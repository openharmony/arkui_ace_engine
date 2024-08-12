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

#include "core/components_ng/render/adapter/rosen/drawing_image.h"

#include "include/core/SkGraphics.h"
#include "core/components_ng/property/measure_utils.h"
#include "frameworks/core/components_ng/render/adapter/image_painter_utils.h"
#include "frameworks/core/image/sk_image_cache.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "pipeline/rs_recording_canvas.h"
#endif

namespace OHOS::Ace::NG {
namespace {
// The [GRAY_COLOR_MATRIX] is of dimension [4 x 5], which transforms a RGB source color (R, G, B, A) to the
// destination color (R', G', B', A').
//
// A classic color image to grayscale conversion formula is [Gray = R * 0.3 + G * 0.59 + B * 0.11].
// Hence we get the following conversion:
//
// | M11 M12 M13 M14 M15 |   | R |   | R' |
// | M21 M22 M23 M24 M25 |   | G |   | G' |
// | M31 M32 M33 M34 M35 | x | B | = | B' |
// | M41 M42 M43 M44 M45 |   | A |   | A' |
//                           | 1 |
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency

void PrintDrawingLatticeConfig(const Rosen::Drawing::Lattice& lattice)
{
    std::string drawingConfigStr;
    drawingConfigStr.append("fXCount = " + std::to_string(lattice.fXCount));
    drawingConfigStr.append("fXDivs = [");
    for (int32_t idx = 0; idx < lattice.fXCount; ++idx) {
        drawingConfigStr.append(std::to_string(lattice.fXDivs[idx]) + " ");
    }
    drawingConfigStr.append("] ");
    drawingConfigStr.append("fYCount = " + std::to_string(lattice.fYCount));
    drawingConfigStr.append("fYDivs = [");
    for (int32_t idx = 0; idx < lattice.fYCount; ++idx) {
        drawingConfigStr.append(std::to_string(lattice.fYDivs[idx]) + " ");
    }
    drawingConfigStr.append("] ");
    TAG_LOGD(AceLogTag::ACE_IMAGE, "Begin to draw iamge with lattice : %{public}s", drawingConfigStr.c_str());
}

bool ConvertSlice(const ImagePaintConfig& config, RectF& result, float rawImageWidth, float rawImageHeight)
{
    const auto& slice = config.resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    TAG_LOGD(AceLogTag::ACE_IMAGE, "Draw image with slice = %{public}s.", slice.ToString().c_str());
    result.SetLeft(ConvertToPx(slice.left, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f));
    result.SetTop(ConvertToPx(slice.top, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f));
    auto rightSliceValue = ConvertToPx(slice.right, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f);
    auto bottomSliceValue =
        ConvertToPx(slice.bottom, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f);
    // illegal case if left position if larger than right, then rect has negative width
    if (GreatNotEqual(rawImageWidth - rightSliceValue - result.GetX(), 0.0f)) {
        result.SetWidth(rawImageWidth - rightSliceValue - result.GetX());
    } else {
        return false;
    }
    // same illegal case for height
    if (GreatNotEqual(rawImageHeight - bottomSliceValue - result.GetY(), 0.0f)) {
        result.SetHeight(rawImageHeight - bottomSliceValue - result.GetY());
    } else {
        return false;
    }
    return true;
}

#ifndef USE_ROSEN_DRAWING
void UpdateSKFilter(const ImagePaintConfig& config, SKPaint& paint)
{
    if (config.colorFilter_.colorFilterMatrix_) {
        paint.setColorFilter(SkColorFilters::Matrix(config.colorFilter_.colorFilterMatrix_->data()));
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
    }
}
#else
void UpdateRSFilter(const ImagePaintConfig& config, RSFilter& filter)
{
    if (config.colorFilter_.colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(config.colorFilter_.colorFilterMatrix_->data());
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    } else if (config.colorFilter_.colorFilterDrawing_) {
        auto colorFilterSptrAddr = static_cast<std::shared_ptr<RSColorFilter>*>(
            config.colorFilter_.colorFilterDrawing_->GetDrawingColorFilterSptrAddr());
        if (colorFilterSptrAddr && (*colorFilterSptrAddr)) {
            filter.SetColorFilter(*colorFilterSptrAddr);
        }
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    }
}
#endif
} // namespace

RefPtr<CanvasImage> CanvasImage::Create(void* rawImage)
{
    auto* rsImagePtr = reinterpret_cast<std::shared_ptr<RSImage>*>(rawImage);
    return AceType::MakeRefPtr<DrawingImage>(*rsImagePtr);
}

RefPtr<CanvasImage> CanvasImage::Create()
{
    return AceType::MakeRefPtr<DrawingImage>();
}

std::shared_ptr<RSImage> DrawingImage::MakeRSImageFromPixmap(const RefPtr<PixelMap>& pixmap)
{
    RSColorType colorType = PixelFormatToRSColorType(pixmap);
    RSAlphaType alphaType = AlphaTypeToRSAlphaType(pixmap);
    RSBitmapFormat bitmapFormat = { colorType, alphaType };
    auto bitmap = std::make_shared<RSBitmap>();
    bitmap->Build(pixmap->GetWidth(), pixmap->GetHeight(), bitmapFormat, pixmap->GetRowStride());
    bitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixmap->GetPixels())));

    auto image = std::make_shared<RSImage>();
    image->BuildFromBitmap(*bitmap);
    return image;
}

RSAlphaType DrawingImage::AlphaTypeToRSAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return RSAlphaType::ALPHATYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return RSAlphaType::ALPHATYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return RSAlphaType::ALPHATYPE_UNPREMUL;
        default:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
    }
}

RSColorType DrawingImage::PixelFormatToRSColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return RSColorType::COLORTYPE_RGB_565;
        case PixelFormat::RGBA_8888:
            return RSColorType::COLORTYPE_RGBA_8888;
        case PixelFormat::BGRA_8888:
            return RSColorType::COLORTYPE_BGRA_8888;
        case PixelFormat::ALPHA_8:
            return RSColorType::COLORTYPE_ALPHA_8;
        case PixelFormat::RGBA_F16:
            return RSColorType::COLORTYPE_RGBA_F16;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return RSColorType::COLORTYPE_UNKNOWN;
    }
}

void DrawingImage::ReplaceRSImage(std::shared_ptr<RSImage> image)
{
    image_ = std::move(image);
}

int32_t DrawingImage::GetWidth() const
{
    return image_ ? image_->GetWidth() : compressWidth_;
}

int32_t DrawingImage::GetHeight() const
{
    return image_ ? image_->GetHeight() : compressHeight_;
}

RefPtr<CanvasImage> DrawingImage::Clone()
{
    auto clone = MakeRefPtr<DrawingImage>(image_);
    clone->uniqueId_ = uniqueId_;
    clone->compressData_ = std::move(compressData_);
    clone->compressWidth_ = compressWidth_;
    clone->compressHeight_ = compressHeight_;
    return clone;
}

void DrawingImage::Cache(const std::string& key)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineCtx);
    auto cache = pipelineCtx->GetImageCache();
    CHECK_NULL_VOID(cache);

    auto cached = std::make_shared<CachedImage>(GetImage());
    cached->uniqueId = GetUniqueID();
    pipelineCtx->GetImageCache()->CacheImage(key, cached);
}

RefPtr<CanvasImage> DrawingImage::QueryFromCache(const std::string& key)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto cache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto cacheImage = cache->GetCacheImage(key);
    CHECK_NULL_RETURN(cacheImage, nullptr);

    auto rosenImage = MakeRefPtr<DrawingImage>(cacheImage->imagePtr);
    rosenImage->SetUniqueID(cacheImage->uniqueId);

    return rosenImage;
}

RefPtr<PixelMap> DrawingImage::GetPixelMap() const
{
    CHECK_NULL_RETURN(GetImage(), nullptr);
    auto rsImage = GetImage();
    RSBitmapFormat rsBitmapFormat = { RSColorType::COLORTYPE_BGRA_8888, rsImage->GetAlphaType() };
    RSBitmap rsBitmap;
    if (!rsBitmap.Build(rsImage->GetWidth(), rsImage->GetHeight(), rsBitmapFormat)) {
        LOGW("rsBitmap build fail.");
        return nullptr;
    }
    CHECK_NULL_RETURN(rsImage->ReadPixels(rsBitmap, 0, 0), nullptr);
    const auto* addr = static_cast<uint32_t*>(rsBitmap.GetPixels());
    auto width = static_cast<int32_t>(rsBitmap.GetWidth());
    auto height = static_cast<int32_t>(rsBitmap.GetHeight());
    int32_t length = width * height;
    return PixelMap::ConvertSkImageToPixmap(addr, length, width, height);
}

void DrawingImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto image = GetImage();
    CHECK_NULL_VOID(image || GetCompressData());
    if (isDrawAnimate_) {
        RSSamplingOptions options;
        ImagePainterUtils::ClipRRect(canvas, dstRect, radiusXY);
        canvas.DrawImageRect(*image, srcRect, dstRect, options);
    } else {
        const auto& config = GetPaintConfig();
        if (config.resizableLattice_ && DrawImageLattice(canvas, srcRect, dstRect, radiusXY)) {
            return;
        }
        if (config.resizableSlice_.Valid() && DrawImageNine(canvas, srcRect, dstRect, radiusXY)) {
            return;
        }
        DrawWithRecordingCanvas(canvas, radiusXY);
    }
}

bool DrawingImage::DrawImageLattice(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    const auto& config = GetPaintConfig();
    const auto& drawingLattice = config.resizableLattice_;
    CHECK_NULL_RETURN(drawingLattice, false);
#ifdef ENABLE_ROSEN_BACKEND
    auto latticeSptrAddr =
        static_cast<std::shared_ptr<Rosen::Drawing::Lattice>*>(drawingLattice->GetDrawingLatticeSptrAddr());
    RSBrush brush;
    auto filterMode = RSFilterMode::NEAREST;
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW:
        case ImageInterpolation::MEDIUM:
            filterMode = RSFilterMode::LINEAR;
            break;
        case ImageInterpolation::HIGH:
        default:
            break;
    }

    auto filter = brush.GetFilter();
    UpdateRSFilter(config, filter);
    brush.SetFilter(filter);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    std::vector<RSPoint> radius;
    for (size_t ii = 0; ii < 4; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[4] = {};
    for (size_t i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    auto lattice = *(*latticeSptrAddr);
    if (SystemProperties::GetDebugEnabled()) {
        PrintDrawingLatticeConfig(lattice);
    }
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageLattice(image_.get(), *(*latticeSptrAddr), dstRect, filterMode);
    recordingCanvas.DetachBrush();
    return true;
#endif
    return false;
}

bool DrawingImage::DrawImageNine(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    const auto& config = GetPaintConfig();
    const auto& slice = GetPaintConfig().resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    RectF centerRect;
    CHECK_NULL_RETURN(ConvertSlice(config, centerRect, GetWidth(), GetHeight()), false);
#ifdef ENABLE_ROSEN_BACKEND
#ifndef USE_ROSEN_DRAWING
    return false;
#endif
    RSBrush brush;
    auto filterMode = RSFilterMode::NEAREST;
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW:
        case ImageInterpolation::MEDIUM:
            filterMode = RSFilterMode::LINEAR;
            break;
        case ImageInterpolation::HIGH:
        default:
            break;
    }

    auto filter = brush.GetFilter();
    UpdateRSFilter(config, filter);
    brush.SetFilter(filter);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    RSRectI rsCenterRect(centerRect.GetX(), centerRect.GetY(), centerRect.GetX() + centerRect.Width(),
        centerRect.GetY() + centerRect.Height());
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageNine(image_.get(), rsCenterRect, dstRect, filterMode, &brush);
    recordingCanvas.DetachBrush();
    return true;
#endif
    return false;
}

bool DrawingImage::DrawWithRecordingCanvas(RSCanvas& canvas, const BorderRadiusArray& radiusXY)
{
#ifdef ENABLE_ROSEN_BACKEND
    RSBrush brush;
    auto config = GetPaintConfig();
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo = {
        static_cast<int32_t>(config.imageFit_), static_cast<int32_t>(config.imageRepeat_),
        {pointRadius[0], pointRadius[1], pointRadius[2], pointRadius[3]}, 1.0, GetUniqueID(),
        GetCompressWidth(), GetCompressHeight()
    };
    auto data = GetCompressData();
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageWithParm(GetImage(), std::move(data), rsImageInfo, options);
    recordingCanvas.DetachBrush();
    return true;
#else // !ENABLE_ROSEN_BACKEND
    return false;
#endif
}

void DrawingImage::DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect)
{
#ifdef ENABLE_ROSEN_BACKEND
    auto& recordingCanvas = static_cast<Rosen::Drawing::RecordingCanvas&>(canvas);
    RSBrush brush;
    RSSamplingOptions options;
    RSRect dst = RSRect(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom());
    RSRect src = RSRect(srcRect.GetLeft(), srcRect.GetTop(), srcRect.GetRight(), srcRect.GetBottom());
    recordingCanvas.AttachBrush(brush);
    auto imagePtr = GetImage();
    recordingCanvas.DrawImageRect(*imagePtr, src, dst, options);
    recordingCanvas.DetachBrush();
#else // !ENABLE_ROSEN_BACKEND
#endif
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
void ImageCache::Purge()
{
    SkGraphics::PurgeResourceCache();
}
} // namespace OHOS::Ace::NG
