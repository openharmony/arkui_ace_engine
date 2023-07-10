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

#include "image_decoder.h"

#include <mutex>
#include <utility>

#include "include/codec/SkCodec.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkGraphics.h"
#ifdef USE_ROSEN_DRAWING
#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#endif

#include "base/image/image_source.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#endif
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#endif
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_compressor.h"
#include "core/image/image_loader.h"

namespace OHOS::Ace::NG {
ImageDecoder::ImageDecoder(const RefPtr<ImageObject>& obj, const SizeF& size, bool forceResize)
    : obj_(obj), desiredSize_(size), forceResize_(forceResize)
{
    CHECK_NULL_VOID(obj_);
    CHECK_NULL_VOID(ImageProvider::PrepareImageData(obj_));

#ifndef USE_ROSEN_DRAWING
    auto data = AceType::DynamicCast<SkiaImageData>(obj_->GetData());
    CHECK_NULL_VOID(data);
    data_ = data->GetSkData();
#else
    auto data = AceType::DynamicCast<DrawingImageData>(obj_->GetData());
    CHECK_NULL_VOID(data);
    data_ = data->GetRSData();
#endif
}

#ifndef USE_ROSEN_DRAWING
RefPtr<CanvasImage> ImageDecoder::MakeSkiaImage()
#else
RefPtr<CanvasImage> ImageDecoder::MakeDrawingImage()
#endif
{
    CHECK_NULL_RETURN(obj_ && data_, nullptr);
    ACE_SCOPED_TRACE("MakeSkiaImage %s", obj_->GetSourceInfo().ToString().c_str());
    // check compressed image cache
    {
        auto image = QueryCompressedCache();
        if (image) {
            LOGD("QueryCompressedCache hit: %{public}s", obj_->GetSourceInfo().ToString().c_str());
            return image;
        }
    }

#ifndef USE_ROSEN_DRAWING
    auto image = ResizeSkImage();
    CHECK_NULL_RETURN(image, nullptr);
#else
    auto skImage = ResizeSkImage();
    CHECK_NULL_RETURN(skImage, nullptr);
    auto image = std::make_shared<RSImage>(&skImage);
#endif
    auto canvasImage = CanvasImage::Create(&image);

    if (ImageCompressor::GetInstance()->CanCompress()) {
#ifndef USE_ROSEN_DRAWING
        TryCompress(DynamicCast<SkiaImage>(canvasImage));
#else
        TryCompress(DynamicCast<DrawingImage>(canvasImage));
#endif
    }
    return canvasImage;
}

RefPtr<CanvasImage> ImageDecoder::MakePixmapImage()
{
    CHECK_NULL_RETURN(obj_ && data_, nullptr);
    ACE_SCOPED_TRACE("MakePixmapImage %s", obj_->GetSourceInfo().ToString().c_str());

#ifndef USE_ROSEN_DRAWING
    auto source = ImageSource::Create(data_->bytes(), data_->size());
#else
    auto source = ImageSource::Create(static_cast<const uint8_t*>(data_->GetData()), data_->GetSize());
#endif
    CHECK_NULL_RETURN(source, nullptr);

    auto width = std::lround(desiredSize_.Width());
    auto height = std::lround(desiredSize_.Height());
    auto pixmap = source->CreatePixelMap(width, height);
    CHECK_NULL_RETURN(pixmap, nullptr);
    auto image = PixelMapImage::Create(pixmap);
    LOGD("decode to pixmap, desiredSize = %{public}s, pixmap size = %{public}d x %{public}d",
        desiredSize_.ToString().c_str(), image->GetWidth(), image->GetHeight());

    return image;
}

sk_sp<SkImage> ImageDecoder::ForceResizeImage(const sk_sp<SkImage>& image, const SkImageInfo& info)
{
    ACE_FUNCTION_TRACE();
    SkBitmap bitmap;
    bitmap.allocPixels(info);

#ifdef NEW_SKIA
    auto res = image->scalePixels(
        bitmap.pixmap(), SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone), SkImage::kDisallow_CachingHint);
#else
    auto res = image->scalePixels(bitmap.pixmap(), kLow_SkFilterQuality, SkImage::kDisallow_CachingHint);
#endif
    CHECK_NULL_RETURN(res, image);

    bitmap.setImmutable();
    return SkImage::MakeFromBitmap(bitmap);
}

sk_sp<SkImage> ImageDecoder::ResizeSkImage()
{
#ifndef USE_ROSEN_DRAWING
    auto encodedImage = SkImage::MakeFromEncoded(data_);
#else
    CHECK_NULL_RETURN(data_, nullptr);
    auto skData = data_->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
    auto encodedImage = SkImage::MakeFromEncoded(skData);
#endif
    CHECK_NULL_RETURN_NOLOG(desiredSize_.IsPositive(), encodedImage);

    auto width = std::lround(desiredSize_.Width());
    auto height = std::lround(desiredSize_.Height());

#ifndef USE_ROSEN_DRAWING
    auto codec = SkCodec::MakeFromData(data_);
#else
    auto codec = SkCodec::MakeFromData(skData);
#endif
    CHECK_NULL_RETURN(codec, {});
    auto info = codec->getInfo();

    // sourceSize is set by developer, then we will force scaling to [TargetSize] using SkImage::scalePixels,
    // this method would succeed even if the codec doesn't support that size.
    if (forceResize_) {
        info = info.makeWH(width, height);
        return ForceResizeImage(encodedImage, info);
    }

    if ((info.width() > width && info.height() > height)) {
        // If the image is larger than the target size, we will scale it down to the target size.
        // DesiredSize might not be compatible with the codec, so we find the closest size supported by the codec
        auto scale = std::max(static_cast<float>(width) / info.width(), static_cast<float>(height) / info.height());
        auto idealSize = codec->getScaledDimensions(scale);
        LOGD("desiredSize = %{public}s, codec idealSize: %{public}dx%{public}d", desiredSize_.ToString().c_str(),
            idealSize.width(), idealSize.height());

        info = info.makeWH(idealSize.width(), idealSize.height());
        SkBitmap bitmap;
        bitmap.allocPixels(info);
        auto res = codec->getPixels(info, bitmap.getPixels(), bitmap.rowBytes());
        CHECK_NULL_RETURN(res == SkCodec::kSuccess, encodedImage);
        return SkImage::MakeFromBitmap(bitmap);
    }
    return encodedImage;
}

RefPtr<CanvasImage> ImageDecoder::QueryCompressedCache()
{
    auto key = ImageUtils::GenerateImageKey(obj_->GetSourceInfo(), desiredSize_);
    auto cachedData = ImageLoader::LoadImageDataFromFileCache(key, ".astc");
    CHECK_NULL_RETURN_NOLOG(cachedData, {});

#ifndef USE_ROSEN_DRAWING
    auto skiaImageData = AceType::DynamicCast<SkiaImageData>(cachedData);
    CHECK_NULL_RETURN(skiaImageData, {});
    auto stripped = ImageCompressor::StripFileHeader(skiaImageData->GetSkData());
    LOGI("use astc cache %{public}s", key.c_str());

    // create encoded SkImage to use its uniqueId
    auto image = SkImage::MakeFromEncoded(data_);
    auto canvasImage = AceType::DynamicCast<SkiaImage>(CanvasImage::Create(&image));
#else
    auto rosenImageData = AceType::DynamicCast<DrawingImageData>(cachedData);
    CHECK_NULL_RETURN(rosenImageData, {});
    auto stripped = ImageCompressor::StripFileHeader(rosenImageData->GetRSData());
    LOGI("use astc cache %{public}s", key.c_str());

    // create encoded SkImage to use its uniqueId
    CHECK_NULL_RETURN(data_, {});
    auto skData = data_->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
    auto skImage = SkImage::MakeFromEncoded(skData);
    std::shared_ptr<RSImage> image = nullptr;
    if (skImage) {
        image = std::make_shared<RSImage>(&skImage);
    }
    auto canvasImage = AceType::DynamicCast<DrawingImage>(CanvasImage::Create(&image));
#endif
    // round width and height to nearest int
    int32_t dstWidth = std::lround(desiredSize_.Width());
    int32_t dstHeight = std::lround(desiredSize_.Height());
    canvasImage->SetCompressData(stripped, dstWidth, dstHeight);
#ifndef USE_ROSEN_DRAWING
    canvasImage->ReplaceSkImage(nullptr);
#else
    canvasImage->ReplaceRSImage(nullptr);
#endif
    return canvasImage;
}

#ifndef USE_ROSEN_DRAWING
void ImageDecoder::TryCompress(const RefPtr<SkiaImage>& image)
#else
void ImageDecoder::TryCompress(const RefPtr<DrawingImage>& image)
#endif
{
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    return;
#else
    // decode image to texture if not decoded
#ifndef USE_ROSEN_DRAWING
    auto skImage = image->GetImage();
    CHECK_NULL_VOID(skImage);
    auto rasterizedImage = skImage->makeRasterImage();
    CHECK_NULL_VOID(rasterizedImage);
    ACE_DCHECK(!rasterizedImage->isTextureBacked());
    SkPixmap pixmap;
    CHECK_NULL_VOID(rasterizedImage->peekPixels(&pixmap));
    auto width = pixmap.width();
    auto height = pixmap.height();
    // try compress image
    if (ImageCompressor::GetInstance()->CanCompress()) {
        auto key = ImageUtils::GenerateImageKey(obj_->GetSourceInfo(), desiredSize_);
        auto compressData = ImageCompressor::GetInstance()->GpuCompress(key, pixmap, width, height);
        ImageCompressor::GetInstance()->WriteToFile(key, compressData, { width, height });
        if (compressData) {
            // replace skImage of [CanvasImage] with [rasterizedImage]
            image->SetCompressData(compressData, width, height);
            image->ReplaceSkImage(nullptr);
        } else {
            image->ReplaceSkImage(rasterizedImage);
        }
#else
    auto rsImage = image->GetImage();
    CHECK_NULL_VOID(rsImage);
    RSBitmapFormat rsBitmapFormat { rsImage->GetColorType(), rsImage->GetAlphaType() };
    RSBitmap rsBitmap;
    rsBitmap.Build(rsImage->GetWidth(), rsImage->GetHeight(), rsBitmapFormat);
    CHECK_NULL_VOID(rsImage->ReadPixels(rsBitmap, 0, 0));
    auto width = rsBitmap.GetWidth();
    auto height = rsBitmap.GetHeight();
    // try compress image
    if (ImageCompressor::GetInstance()->CanCompress()) {
        auto key = ImageUtils::GenerateImageKey(obj_->GetSourceInfo(), desiredSize_);
        auto compressData = ImageCompressor::GetInstance()->GpuCompress(key, rsBitmap, width, height);
        ImageCompressor::GetInstance()->WriteToFile(key, compressData, { width, height });
        if (compressData) {
            // replace rsImage of [CanvasImage] with [rasterizedImage]
            image->SetCompressData(compressData, width, height);
            image->ReplaceRSImage(nullptr);
        } else {
            auto rasterizedImage = std::make_shared<RSImage>();
            rasterizedImage->BuildFromBitmap(rsBitmap);
            image->ReplaceRSImage(rasterizedImage);
        }
#endif
        auto taskExecutor = Container::CurrentTaskExecutor();
        auto releaseTask = ImageCompressor::GetInstance()->ScheduleReleaseTask();
        if (taskExecutor) {
            taskExecutor->PostDelayedTask(releaseTask, TaskExecutor::TaskType::UI, ImageCompressor::releaseTimeMs);
        } else {
            ImageUtils::PostToBg(std::move(releaseTask));
        }
    }
    SkGraphics::PurgeResourceCache();
#endif
}
} // namespace OHOS::Ace::NG
