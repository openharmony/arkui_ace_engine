/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <mutex>
#include <utility>

#include "include/codec/SkCodec.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkImage.h"

#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/render/adapter/skia_image.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/flutter_image_cache.h"
#include "core/image/image_compressor.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

sk_sp<SkImage> ForceResizeImage(const sk_sp<SkImage>& image, const SkImageInfo& info)
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

sk_sp<SkImage> ResizeSkImage(const sk_sp<SkData>& data, const SizeF& targetSize, bool forceResize)
{
    auto encodedImage = SkImage::MakeFromEncoded(data);
    CHECK_NULL_RETURN_NOLOG(targetSize.IsPositive(), encodedImage);

    auto width = std::lround(targetSize.Width());
    auto height = std::lround(targetSize.Height());

    auto codec = SkCodec::MakeFromData(data);
    CHECK_NULL_RETURN(codec, {});
    auto info = codec->getInfo();

    // sourceSize is set by developer, then we will force scaling to [TargetSize] using SkImage::scalePixels,
    // this method would succeed even if the codec doesn't support that size.
    if (forceResize) {
        info = info.makeWH(width, height);
        return ForceResizeImage(encodedImage, info);
    }

    if ((info.width() > width && info.height() > height)) {
        // If the image is larger than the target size, we will scale it down to the target size.
        // TargetSize might not be compatible with the codec, so we find the closest size supported by the codec
        auto scale = std::max(static_cast<float>(width) / info.width(), static_cast<float>(height) / info.height());
        auto idealSize = codec->getScaledDimensions(scale);
        LOGD("targetSize = %{public}s, idealSize: %{public}dx%{public}d", targetSize.ToString().c_str(),
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
} // namespace

RefPtr<CanvasImage> ImageProvider::QueryCanvasImageFromCache(const ImageSourceInfo& src, const SizeF& targetSize)
{
    // Query [CanvasImage] from cache, if hit, notify load success immediately and returns true
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto cache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto key = ImageUtils::GenerateImageKey(src, targetSize);
    auto cacheImage = cache->GetCacheImage(key);
    CHECK_NULL_RETURN_NOLOG(cacheImage, nullptr);

    auto rawImage = cacheImage->imagePtr;
    auto canvasImage = CanvasImage::Create(&rawImage);
    auto skiaImage = DynamicCast<SkiaImage>(canvasImage);
    CHECK_NULL_RETURN(skiaImage, nullptr);
    skiaImage->SetUniqueID(cacheImage->uniqueId);

    if (canvasImage) {
        LOGD("[ImageCache][CanvasImage] succeed find canvas image from cache: %{public}s", key.c_str());
    }
    return canvasImage;
}

void ImageProvider::MakeCanvasImage(const WeakPtr<ImageObject>& objWp, const WeakPtr<ImageLoadingContext>& ctxWp,
    const SizeF& targetSize, bool forceResize, bool sync)
{
    auto obj = objWp.Upgrade();
    CHECK_NULL_VOID(obj);
    auto key = ImageUtils::GenerateImageKey(obj->GetSourceInfo(), targetSize);
    // check if same task is already executing
    if (!RegisterTask(key, ctxWp)) {
        return;
    }

    if (sync) {
        if (!MakeCanvasImageHelper(objWp, targetSize, forceResize, true)) {
            FailCallback(key, "Make CanvasImage failed.");
        }
    } else {
        std::scoped_lock<std::mutex> lock(taskMtx_);
        // wrap with [CancelableCallback] and record in [tasks_] map
        CancelableCallback<void()> task;
        task.Reset([key, objWp, targetSize, forceResize] {
            if (!MakeCanvasImageHelper(objWp, targetSize, forceResize)) {
                FailCallback(key, "Make CanvasImage failed.");
            }
        });
        tasks_[key].bgTask_ = task;
        ImageUtils::PostToBg(task);
    }
}

namespace {
RefPtr<CanvasImage> QueryCompressedCache(const sk_sp<SkData>& skData, const std::string& key, const SizeF& imageSize)
{
    // create encoded SkImage to use its uniqueId
    auto image = SkImage::MakeFromEncoded(skData);
    auto canvasImage = AceType::DynamicCast<SkiaImage>(CanvasImage::Create(&image));

    auto cachedData = ImageLoader::LoadImageDataFromFileCache(key, ".astc");
    CHECK_NULL_RETURN_NOLOG(cachedData, {});
    // round width and height to nearest int
    int32_t dstWidth = std::lround(imageSize.Width());
    int32_t dstHeight = std::lround(imageSize.Height());

    auto skiaImageData = AceType::DynamicCast<SkiaImageData>(cachedData);
    CHECK_NULL_RETURN(skiaImageData, {});
    auto stripped = ImageCompressor::StripFileHeader(skiaImageData->GetSkData());
    LOGI("use astc cache %{public}s %{public}d×%{public}d", key.c_str(), dstWidth, dstHeight);
    canvasImage->SetCompressData(stripped, dstWidth, dstHeight);
    canvasImage->ReplaceSkImage(nullptr);
    return canvasImage;
}

void TryCompress(const RefPtr<SkiaImage>& image, const std::string& key)
{
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    return false;
#else
    // decode image to texture if not decoded
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
        auto compressData = ImageCompressor::GetInstance()->GpuCompress(key, pixmap, width, height);
        ImageCompressor::GetInstance()->WriteToFile(key, compressData, { width, height });
        if (compressData) {
            // replace skImage of [CanvasImage] with [rasterizedImage]
            image->SetCompressData(compressData, width, height);
            image->ReplaceSkImage(nullptr);
        } else {
            image->ReplaceSkImage(rasterizedImage);
        }
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
} // namespace

bool ImageProvider::MakeCanvasImageHelper(
    const WeakPtr<ImageObject>& objWp, const SizeF& targetSize, bool forceResize, bool sync)
{
    auto obj = objWp.Upgrade();
    CHECK_NULL_RETURN(obj, false);
    ACE_SCOPED_TRACE("MakeCanvasImage %s", obj->GetSourceInfo().ToString().c_str());
    CHECK_NULL_RETURN(PrepareImageData(obj), false);

    auto data = DynamicCast<SkiaImageData>(obj->GetData());
    CHECK_NULL_RETURN(data, false);
    auto skData = data->GetSkData();
    CHECK_NULL_RETURN(skData, false);

    auto key = ImageUtils::GenerateImageKey(obj->GetSourceInfo(), targetSize);
    // check compressed image cache
    {
        auto image = QueryCompressedCache(skData, key, targetSize);
        if (image) {
            LOGD("QueryCompressedCache hit: %{public}s", obj->GetSourceInfo().ToString().c_str());
            SuccessCallback(image, key, sync);
            return true;
        }
    }

    auto image = ResizeSkImage(skData, targetSize, forceResize);
    CHECK_NULL_RETURN(image, false);
    auto canvasImage = CanvasImage::Create(&image);

    if (ImageCompressor::GetInstance()->CanCompress()) {
        TryCompress(DynamicCast<SkiaImage>(canvasImage), key);
    }
    SuccessCallback(canvasImage, key, sync);
    return true;
}

void ImageProvider::CacheCanvasImage(const RefPtr<CanvasImage>& canvasImage, const std::string& key)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineCtx);
    CHECK_NULL_VOID(pipelineCtx->GetImageCache());

    auto skiaCanvasImage = AceType::DynamicCast<SkiaImage>(canvasImage);
    CHECK_NULL_VOID(skiaCanvasImage);
    auto cached = std::make_shared<Ace::CachedImage>(skiaCanvasImage->GetImage());
    cached->uniqueId = skiaCanvasImage->GetUniqueID();
    pipelineCtx->GetImageCache()->CacheImage(key, cached);
}

} // namespace OHOS::Ace::NG
