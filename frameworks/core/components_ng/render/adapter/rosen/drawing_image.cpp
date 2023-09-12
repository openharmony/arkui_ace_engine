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

#include <utility>

#include "base/image/pixel_map.h"
#include "frameworks/core/components_ng/render/adapter/image_painter_utils.h"
#include "frameworks/core/image/sk_image_cache.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "pipeline/rs_recording_canvas.h"
#endif

namespace OHOS::Ace::NG {
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
    bitmap->Build(pixmap->GetWidth(), pixmap->GetHeight(), bitmapFormat);
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
    CHECK_NULL_RETURN_NOLOG(cacheImage, nullptr);
    LOGD("rsImage found in cache: %{public}s", key.c_str());

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
    rsBitmap.Build(rsImage->GetWidth(), rsImage->GetHeight(), rsBitmapFormat);
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
        DrawWithRecordingCanvas(canvas, radiusXY);
    }
}

bool DrawingImage::DrawWithRecordingCanvas(RSCanvas& canvas, const BorderRadiusArray& radiusXY)
{
#ifdef ENABLE_ROSEN_BACKEND
    RSBrush brush;
    auto config = GetPaintConfig();
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    auto recordingCanvas = static_cast<RSRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radiusXY[ii].GetX(), radiusXY[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo =
        {static_cast<int32_t>(config.imageFit_), static_cast<int32_t>(config.imageRepeat_),
         {pointRadius[0], pointRadius[1], pointRadius[2], pointRadius[3]}, 1.0, GetUniqueID(),
        GetCompressWidth(), GetCompressHeight()};
    auto data = GetCompressData();
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImage(GetImage(), std::move(data), rsImageInfo, options);
    recordingCanvas.DetachBrush();
    return true;
#else // !ENABLE_ROSEN_BACKEND
    return false;
#endif
}
} // namespace OHOS::Ace::NG
