/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#include "drawing/engine_adapter/skia_adapter/skia_image_info.h"
#include "include/codec/SkCodec.h"
#include "include/core/SkGraphics.h"

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "core/components_ng/image_provider/adapter/drawing_image_data.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/drawing_image.h"
#include "core/image/image_compressor.h"
#include "core/image/image_loader.h"

namespace OHOS::Ace::NG {
std::shared_mutex ImageDecoder::pixelMapMtx_;
std::unordered_map<std::string, WeakPtr<PixelMap>> ImageDecoder::weakPixelMapCache_;

WeakPtr<PixelMap> ImageDecoder::GetFromPixelMapCache(const ImageSourceInfo& imageSourceInfo, const SizeF& size)
{
    // only support network image
    if (imageSourceInfo.GetSrcType() != SrcType::NETWORK) {
        return nullptr;
    }
    std::shared_lock<std::shared_mutex> lock(pixelMapMtx_);
    auto key = ImageUtils::GenerateImageKey(imageSourceInfo, size);
    // key exists -> task is running
    auto it = weakPixelMapCache_.find(key);
    if (it != weakPixelMapCache_.end()) {
        return it->second;
    }
    return nullptr;
}

void ImageDecoder::RemoveFromPixelMapCache(const ImageSourceInfo& imageSourceInfo, const SizeF& size)
{
    std::unique_lock<std::shared_mutex> lock(pixelMapMtx_);
    auto key = ImageUtils::GenerateImageKey(imageSourceInfo, size);
    weakPixelMapCache_.erase(key);
}

void ImageDecoder::ClearPixelMapCache()
{
    std::unique_lock<std::shared_mutex> lock(pixelMapMtx_);
    weakPixelMapCache_.clear();
}

void ImageDecoder::AddToPixelMapCache(
    const ImageSourceInfo& imageSourceInfo, const SizeF& size, WeakPtr<PixelMap> weakPixelMap)
{
    // only cache network image
    if (imageSourceInfo.GetSrcType() != SrcType::NETWORK) {
        return;
    }
    std::unique_lock<std::shared_mutex> lock(pixelMapMtx_);
    auto key = ImageUtils::GenerateImageKey(imageSourceInfo, size);
    weakPixelMapCache_.emplace(key, weakPixelMap);
}

RefPtr<CanvasImage> ImageDecoder::MakeDrawingImage(
    const RefPtr<ImageObject>& obj, const ImageDecoderConfig& imageDecoderConfig)
{
    CHECK_NULL_RETURN(obj, nullptr);
    ImageProvider::PrepareImageData(obj);
    auto imageData = AceType::DynamicCast<DrawingImageData>(obj->GetData());
    CHECK_NULL_RETURN(imageData, nullptr);
    auto data = imageData->GetRSData();
    CHECK_NULL_RETURN(data, nullptr);
    ACE_SCOPED_TRACE("MakeSkiaImage %s", obj->GetSourceInfo().ToString().c_str());
    // check compressed image cache
    {
        auto image = QueryCompressedCache(obj, data, imageDecoderConfig);
        if (image) {
            return image;
        }
    }

    auto image = ResizeDrawingImage(obj, data, imageDecoderConfig);
    CHECK_NULL_RETURN(image, nullptr);
    auto canvasImage = CanvasImage::Create(&image);

    if (ImageCompressor::GetInstance()->CanCompress()) {
        TryCompress(obj, DynamicCast<DrawingImage>(canvasImage), imageDecoderConfig);
    }
    return canvasImage;
}

RefPtr<CanvasImage> ImageDecoder::MakePixmapImage(
    const RefPtr<ImageObject>& obj, const ImageDecoderConfig& imageDecoderConfig)
{
    CHECK_NULL_RETURN(obj, nullptr);
    ImageProvider::PrepareImageData(obj);
    auto imageData = AceType::DynamicCast<DrawingImageData>(obj->GetData());
    CHECK_NULL_RETURN(imageData, nullptr);
    auto data = imageData->GetRSData();
    CHECK_NULL_RETURN(data, nullptr);
    auto imageDfxConfig = obj->GetImageDfxConfig();
    auto src = imageDfxConfig.imageSrc_;
    auto source = ImageSource::Create(static_cast<const uint8_t*>(data->GetData()), data->GetSize());
    if (!source) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ImageSouce Create Fail, %{private}s-%{public}s.", src.c_str(),
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }

    auto width = static_cast<int32_t>(std::lround(imageDecoderConfig.desiredSize_.Width()));
    auto height = static_cast<int32_t>(std::lround(imageDecoderConfig.desiredSize_.Height()));
    std::pair<int32_t, int32_t> sourceSize = source->GetImageSize();
    // Determine whether to decode the width and height of each other based on the orientation
    SwapDecodeSize(obj, width, height);
    std::string isTrimMemRebuild = "False";
    if (imageDfxConfig.isTrimMemRecycle_) {
        isTrimMemRebuild = "True";
        TAG_LOGI(AceLogTag::ACE_IMAGE, "CreateImagePixelMapRebuild, %{private}s-%{public}s.",
            src.c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
    }
    ACE_SCOPED_TRACE("CreateImagePixelMap %s, sourceSize: [ %d, %d ], targetSize: [ %d, %d ],"
                     "[%d-%d-%d], isTrimMemRebuild: [%s]",
        src.c_str(), sourceSize.first, sourceSize.second, width, height,
        static_cast<int32_t>(imageDecoderConfig.isHdrDecoderNeed_),
        static_cast<int32_t>(imageDecoderConfig.imageQuality_),
        static_cast<int32_t>(imageDecoderConfig.photoDecodeFormat_), isTrimMemRebuild.c_str());

    auto pixmap = source->CreatePixelMap({ width, height }, imageDecoderConfig.imageQuality_,
        imageDecoderConfig.isHdrDecoderNeed_, imageDecoderConfig.photoDecodeFormat_);
    if (!pixmap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "PixelMap Create Fail, src = %{private}s-%{public}s.", src.c_str(),
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }

    auto image = PixelMapImage::Create(pixmap);
    if (SystemProperties::GetDebugPixelMapSaveEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE,
            "Image Decode success, Info:%{public}s-%{public}s-%{public}d x %{public}d-%{public}d-%{public}d",
            imageDfxConfig.ToStringWithSrc().c_str(), imageDecoderConfig.desiredSize_.ToString().c_str(),
            image->GetWidth(), image->GetHeight(), imageDecoderConfig.isHdrDecoderNeed_,
            static_cast<int32_t>(imageDecoderConfig.photoDecodeFormat_));
        pixmap->SavePixelMapToFile(imageDfxConfig.ToStringWithoutSrc() + "_decode_");
    }

    AddToPixelMapCache(obj->GetSourceInfo(), imageDecoderConfig.desiredSize_, image->GetPixelMap());

    return image;
}

void ImageDecoder::SwapDecodeSize(const RefPtr<ImageObject>& obj, int32_t& width, int32_t& height)
{
    if (width == 0 || height == 0 || obj->GetUserOrientation() == ImageRotateOrientation::UP) {
        return;
    }
    auto orientation = obj->GetOrientation();
    if (orientation == ImageRotateOrientation::LEFT || orientation == ImageRotateOrientation::RIGHT) {
        std::swap(width, height);
    }
}

std::shared_ptr<RSImage> ImageDecoder::ForceResizeImage(const std::shared_ptr<RSImage>& image, const RSImageInfo& info)
{
    ACE_FUNCTION_TRACE();
    RSBitmap bitmap;
    bitmap.Build(info);

    auto res = image->ScalePixels(bitmap, RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE), false);

    CHECK_NULL_RETURN(res, image);

    bitmap.SetImmutable();
    auto drImage = std::make_shared<RSImage>();
    drImage->BuildFromBitmap(bitmap);
    return drImage;
}

std::shared_ptr<RSImage> ImageDecoder::ResizeDrawingImage(
    const RefPtr<ImageObject>& obj, std::shared_ptr<RSData> data, const ImageDecoderConfig& imageDecoderConfig)
{
    CHECK_NULL_RETURN(data, nullptr);
    RSDataWrapper* wrapper = new RSDataWrapper{data};
    auto skData =
        SkData::MakeWithProc(data->GetData(), data->GetSize(), RSDataWrapperReleaseProc, wrapper);
    auto encodedImage = std::make_shared<RSImage>();
    if (!encodedImage->MakeFromEncoded(data)) {
        return nullptr;
    }
    CHECK_NULL_RETURN(imageDecoderConfig.desiredSize_.IsPositive(), encodedImage);

    auto width = std::lround(imageDecoderConfig.desiredSize_.Width());
    auto height = std::lround(imageDecoderConfig.desiredSize_.Height());

    auto codec = SkCodec::MakeFromData(skData);
    CHECK_NULL_RETURN(codec, {});
    auto info = codec->getInfo();

    ACE_SCOPED_TRACE("ImageResize %s, sourceSize: [ %d, %d ], targetSize: [ %d, %d ]",
        obj->GetSourceInfo().ToString().c_str(), info.width(), info.height(), static_cast<int32_t>(width),
        static_cast<int32_t>(height));

    // sourceSize is set by developer, then we will force scaling to [TargetSize] using SkImage::scalePixels,
    // this method would succeed even if the codec doesn't support that size.
    if (imageDecoderConfig.forceResize_) {
        info = info.makeWH(width, height);
        auto imageInfo = Rosen::Drawing::SkiaImageInfo::ConvertToRSImageInfo(info);
        return ForceResizeImage(encodedImage, imageInfo);
    }

    if ((info.width() > width && info.height() > height)) {
        // If the image is larger than the target size, we will scale it down to the target size.
        // DesiredSize might not be compatible with the codec, so we find the closest size supported by the codec
        auto scale = std::max(static_cast<float>(width) / info.width(), static_cast<float>(height) / info.height());
        auto idealSize = codec->getScaledDimensions(scale);
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_IMAGE, "desiredSize = %{public}s, codec idealSize: %{public}dx%{public}d",
                imageDecoderConfig.desiredSize_.ToString().c_str(), idealSize.width(), idealSize.height());
        }

        info = info.makeWH(idealSize.width(), idealSize.height());
        auto imageInfo = Rosen::Drawing::SkiaImageInfo::ConvertToRSImageInfo(info);
        RSBitmap bitmap;
        bitmap.Build(imageInfo);
        auto res = codec->getPixels(info, bitmap.GetPixels(), bitmap.GetRowBytes());
        CHECK_NULL_RETURN(res == SkCodec::kSuccess, encodedImage);
        auto image = std::make_shared<RSImage>();
        image->BuildFromBitmap(bitmap);
        return image;
    }
    return encodedImage;
}

RefPtr<CanvasImage> ImageDecoder::QueryCompressedCache(
    const RefPtr<ImageObject>& obj, std::shared_ptr<RSData> data, const ImageDecoderConfig& imageDecoderConfig)
{
    auto key = ImageUtils::GenerateImageKey(obj->GetSourceInfo(), imageDecoderConfig.desiredSize_);
    auto cachedData = ImageLoader::LoadImageDataFromFileCache(key, ".astc");
    CHECK_NULL_RETURN(cachedData, {});

    auto rosenImageData = AceType::DynamicCast<DrawingImageData>(cachedData);
    CHECK_NULL_RETURN(rosenImageData, {});
    auto stripped = ImageCompressor::StripFileHeader(rosenImageData->GetRSData());
    TAG_LOGI(AceLogTag::ACE_IMAGE, "use astc cache %{private}s", key.c_str());

    // create encoded SkImage to use its uniqueId
    CHECK_NULL_RETURN(data, {});
    auto image = std::make_shared<RSImage>();
    if (!image->MakeFromEncoded(data)) {
        return nullptr;
    }
    auto canvasImage = AceType::DynamicCast<DrawingImage>(CanvasImage::Create(&image));
    // round width and height to nearest int
    int32_t dstWidth = std::lround(imageDecoderConfig.desiredSize_.Width());
    int32_t dstHeight = std::lround(imageDecoderConfig.desiredSize_.Height());
    canvasImage->SetCompressData(stripped, dstWidth, dstHeight);
    canvasImage->ReplaceRSImage(nullptr);
    return canvasImage;
}

void ImageDecoder::TryCompress(
    const RefPtr<ImageObject>& obj, const RefPtr<DrawingImage>& image, const ImageDecoderConfig& imageDecoderConfig)
{
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    return;
#else
    // decode image to texture if not decoded
    auto rsImage = image->GetImage();
    CHECK_NULL_VOID(rsImage);
    RSBitmapFormat rsBitmapFormat { rsImage->GetColorType(), rsImage->GetAlphaType() };
    RSBitmap rsBitmap;
    if (!rsBitmap.Build(rsImage->GetWidth(), rsImage->GetHeight(), rsBitmapFormat)) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "rsBitmap build fail.");
        return;
    }
    CHECK_NULL_VOID(rsImage->ReadPixels(rsBitmap, 0, 0));
    auto width = rsBitmap.GetWidth();
    auto height = rsBitmap.GetHeight();
    // try compress image
    if (ImageCompressor::GetInstance()->CanCompress()) {
        auto key = ImageUtils::GenerateImageKey(obj->GetSourceInfo(), imageDecoderConfig.desiredSize_);
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
        auto taskExecutor = Container::CurrentTaskExecutor();
        auto releaseTask = ImageCompressor::GetInstance()->ScheduleReleaseTask();
        if (taskExecutor) {
            taskExecutor->PostDelayedTask(releaseTask, TaskExecutor::TaskType::UI, ImageCompressor::releaseTimeMs,
                "ArkUIImageCompressorScheduleRelease");
        } else {
            ImageUtils::PostToBg(std::move(releaseTask), "ArkUIImageCompressorScheduleRelease");
        }
    }
    SkGraphics::PurgeResourceCache();
#endif
}
} // namespace OHOS::Ace::NG
