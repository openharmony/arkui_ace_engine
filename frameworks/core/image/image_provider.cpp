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

#include "core/image/image_provider.h"

#include "image_compressor.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkStream.h"
#include "modules/svg/include/SkSVGDOM.h"

#ifdef USE_ROSEN_DRAWING
#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#include "drawing/engine_adapter/skia_adapter/skia_image.h"
#endif

#include "base/log/ace_trace.h"
#include "base/thread/background_task_executor.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#endif
#include "core/event/ace_event_helper.h"
#include "core/image/image_file_cache.h"
#include "core/image/image_object.h"

namespace OHOS::Ace {
namespace {

// If a picture is a wide color gamut picture, its area value will be larger than this threshold.
constexpr double SRGB_GAMUT_AREA = 0.104149;

} // namespace

std::mutex ImageProvider::loadingImageMutex_;
std::unordered_map<std::string, std::vector<LoadCallback>> ImageProvider::loadingImage_;

std::mutex ImageProvider::uploadMutex_;
std::unordered_map<std::string, std::vector<LoadCallback>> ImageProvider::uploadingImage_;

bool ImageProvider::TrySetLoadingImage(const ImageSourceInfo& imageInfo, const ImageObjSuccessCallback& successCallback,
    const UploadSuccessCallback& uploadCallback, const FailedCallback& failedCallback)
{
    std::lock_guard lock(loadingImageMutex_);
    auto key = imageInfo.GetKey();
    auto iter = loadingImage_.find(key);
    if (iter == loadingImage_.end()) {
        std::vector<LoadCallback> callbacks { { successCallback, uploadCallback, failedCallback } };
        loadingImage_.emplace(key, callbacks);
        return true;
    } else {
        LOGI("other thread is loading same image: %{public}s", imageInfo.ToString().c_str());
        iter->second.emplace_back(successCallback, uploadCallback, failedCallback);
        return false;
    }
}

void ImageProvider::ProccessLoadingResult(const RefPtr<TaskExecutor>& taskExecutor, const ImageSourceInfo& imageInfo,
    bool canStartUploadImageObj, const RefPtr<ImageObject>& imageObj, const RefPtr<PipelineBase>& context,
    const std::string& errorMsg)
{
    std::lock_guard lock(loadingImageMutex_);
    std::vector<LoadCallback> callbacks;
    auto key = imageInfo.GetKey();
    auto iter = loadingImage_.find(key);
    if (iter != loadingImage_.end()) {
        std::swap(callbacks, iter->second);
        for (const auto& callback : callbacks) {
            if (imageObj == nullptr) {
                taskExecutor->PostTask(
                    [imageInfo, callback, errorMsg]() {
                        if (callback.failedCallback) {
                            callback.failedCallback(imageInfo, errorMsg);
                        }
                    },
                    TaskExecutor::TaskType::UI);
                return;
            }
            auto obj = imageObj->Clone();
            taskExecutor->PostTask(
                [obj, imageInfo, callback]() {
                    if (callback.successCallback) {
                        callback.successCallback(imageInfo, obj);
                    }
                },
                TaskExecutor::TaskType::UI);
            if (canStartUploadImageObj) {
                bool forceResize = (!obj->IsSvg()) && (imageInfo.IsSourceDimensionValid());
                obj->UploadToGpuForRender(
                    context, callback.uploadCallback, callback.failedCallback, obj->GetImageSize(), forceResize, true);
            }
        }
    } else {
        LOGW("no loading image: %{public}s", imageInfo.ToString().c_str());
    }
    loadingImage_.erase(key);
}

bool ImageProvider::TryUploadingImage(
    const std::string& key, const UploadSuccessCallback& successCallback, const FailedCallback& failedCallback)
{
    std::lock_guard lock(uploadMutex_);
    auto iter = uploadingImage_.find(key);
    if (iter == uploadingImage_.end()) {
        std::vector<LoadCallback> callbacks = { { nullptr, successCallback, failedCallback } };
        uploadingImage_.emplace(key, callbacks);
        return true;
    } else {
        iter->second.emplace_back(nullptr, successCallback, failedCallback);
        return false;
    }
}

void ImageProvider::ProccessUploadResult(const RefPtr<TaskExecutor>& taskExecutor, const ImageSourceInfo& imageInfo,
    const Size& imageSize, const RefPtr<NG::CanvasImage>& canvasImage, const std::string& errorMsg)
{
    std::lock_guard lock(uploadMutex_);
    std::vector<LoadCallback> callbacks;
    auto key = ImageObject::GenerateCacheKey(imageInfo, imageSize);
    auto iter = uploadingImage_.find(key);
    if (iter != uploadingImage_.end()) {
        std::swap(callbacks, iter->second);
        taskExecutor->PostTask(
            [callbacks, imageInfo, canvasImage, errorMsg]() {
                for (auto callback : callbacks) {
                    if (canvasImage) {
                        callback.uploadCallback(imageInfo, canvasImage);
                    } else {
                        callback.failedCallback(imageInfo, errorMsg);
                    }
                }
            },
            TaskExecutor::TaskType::UI);
    } else {
        LOGW("no uploading image: %{public}s", imageInfo.ToString().c_str());
    }
    uploadingImage_.erase(key);
}

void ImageProvider::FetchImageObject(const ImageSourceInfo& imageInfo, const ImageObjSuccessCallback& successCallback,
    const UploadSuccessCallback& uploadSuccessCallback, const FailedCallback& failedCallback,
    const WeakPtr<PipelineBase>& context, bool syncMode, bool useSkiaSvg, bool needAutoResize,
    const OnPostBackgroundTask& onBackgroundTaskPostCallback)
{
    auto task = [context, imageInfo, successCallback, failedCallback, useSkiaSvg, uploadSuccessCallback, needAutoResize,
                    id = Container::CurrentId(), syncMode]() mutable {
        ContainerScope scope(id);
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGE("pipeline context has been released. imageInfo: %{private}s", imageInfo.ToString().c_str());
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("task executor is null. imageInfo: %{private}s", imageInfo.ToString().c_str());
            return;
        }
        if (!syncMode && !TrySetLoadingImage(imageInfo, successCallback, uploadSuccessCallback, failedCallback)) {
            LOGI("same source is loading: %{private}s", imageInfo.ToString().c_str());
            return;
        }
        RefPtr<ImageObject> imageObj = QueryImageObjectFromCache(imageInfo, pipelineContext);
        if (!imageObj) { // if image object is not in cache, generate a new one.
            imageObj = GeneratorAceImageObject(imageInfo, pipelineContext, useSkiaSvg);
        }
        if (!imageObj) { // if it fails to generate an image object, trigger fail callback.
            if (syncMode) {
                failedCallback(
                    imageInfo, "Image data may be broken or absent, please check if image file or image data is valid");
                return;
            }
            ProccessLoadingResult(taskExecutor, imageInfo, false, nullptr, pipelineContext,
                "Image data may be broken or absent, please check if image file or image data is valid.");
            return;
        }
        if (syncMode) {
            successCallback(imageInfo, imageObj);
        } else {
            ProccessLoadingResult(taskExecutor, imageInfo, !needAutoResize && (imageObj->GetFrameCount() == 1),
                imageObj, pipelineContext);
        }
    };
    if (syncMode) {
        task();
        return;
    }
    CancelableTask cancelableTask(std::move(task));
    if (onBackgroundTaskPostCallback) {
        onBackgroundTaskPostCallback(cancelableTask);
    }
    BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
}

RefPtr<ImageObject> ImageProvider::QueryImageObjectFromCache(
    const ImageSourceInfo& imageInfo, const RefPtr<PipelineBase>& pipelineContext)
{
    auto imageCache = pipelineContext->GetImageCache();
    if (!imageCache) {
        return nullptr;
    }
    return imageCache->GetCacheImgObj(imageInfo.ToString());
}

RefPtr<ImageObject> ImageProvider::GeneratorAceImageObject(
    const ImageSourceInfo& imageInfo, const RefPtr<PipelineBase> context, bool useSkiaSvg)
{
    auto imageData = LoadImageRawData(imageInfo, context);

    if (!imageData) {
        LOGE("load image data failed. imageInfo: %{private}s", imageInfo.ToString().c_str());
        return nullptr;
    }
    return ImageObject::BuildImageObject(imageInfo, context, imageData, useSkiaSvg);
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkData> ImageProvider::LoadImageRawData(const ImageSourceInfo& imageInfo, const RefPtr<PipelineBase> context)
#else
std::shared_ptr<RSData> ImageProvider::LoadImageRawData(
    const ImageSourceInfo& imageInfo, const RefPtr<PipelineBase> context)
#endif
{
    ACE_FUNCTION_TRACE();
    auto imageCache = context->GetImageCache();
    if (imageCache) {
        // 1. try get data from cache.
        auto cacheData = imageCache->GetCacheImageData(imageInfo.GetSrc());
        if (cacheData) {
#ifndef USE_ROSEN_DRAWING
            LOGD("sk data from memory cache.");
            const auto* skData = reinterpret_cast<const sk_sp<SkData>*>(cacheData->GetDataWrapper());
            return *skData;
#else
            LOGD("drawing data from memory cache.");
            return AceType::DynamicCast<NG::DrawingImageData>(cacheData)->GetRsData();
#endif
        }
    }
    // 2. try load raw image file.
    auto imageLoader = ImageLoader::CreateImageLoader(imageInfo);
    if (!imageLoader) {
        LOGE("imageLoader create failed. imageInfo: %{private}s", imageInfo.ToString().c_str());
        return nullptr;
    }
    auto data = imageLoader->LoadImageData(imageInfo, context);
    if (data && imageCache) {
#ifndef USE_ROSEN_DRAWING
        // cache sk data.
        imageCache->CacheImageData(imageInfo.GetSrc(), NG::ImageData::MakeFromDataWrapper(&data));
#else
        // cache drawing data.
        imageCache->CacheImageData(imageInfo.GetSrc(), AceType::MakeRefPtr<NG::DrawingImageData>(data));
#endif
    }
    return data;
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkData> ImageProvider::LoadImageRawDataFromFileCache(
#else
std::shared_ptr<RSData> ImageProvider::LoadImageRawDataFromFileCache(
#endif
    const RefPtr<PipelineBase> context, const std::string key, const std::string suffix)
{
    ACE_FUNCTION_TRACE();
    std::string cacheFilePath = ImageFileCache::GetInstance().GetImageCacheFilePath(key) + suffix;
    auto data = ImageFileCache::GetInstance().GetDataFromCacheFile(cacheFilePath);
    if (data) {
#ifndef USE_ROSEN_DRAWING
        const auto* skData = reinterpret_cast<const sk_sp<SkData>*>(data->GetDataWrapper());
        return *skData;
#else
        return AceType::DynamicCast<NG::DrawingImageData>(data)->GetRsData();
#endif
    }
    return nullptr;
}

void ImageProvider::GetSVGImageDOMAsyncFromSrc(const std::string& src,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback, std::function<void()> failedCallback,
    const WeakPtr<PipelineBase> context, uint64_t svgThemeColor, OnPostBackgroundTask onBackgroundTaskPostCallback)
{
    auto task = [src, successCallback, failedCallback, context, svgThemeColor, id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGW("render image or pipeline has been released.");
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        ImageSourceInfo info(src);
        auto imageLoader = ImageLoader::CreateImageLoader(info);
        if (!imageLoader) {
            LOGE("load image failed when create image loader.");
            return;
        }
        auto imageData = imageLoader->LoadImageData(info, context);
        if (imageData) {
#ifndef USE_ROSEN_DRAWING
            const auto svgStream = std::make_unique<SkMemoryStream>(std::move(imageData));
#else
            auto skData = imageData->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
            const auto svgStream = std::make_unique<SkMemoryStream>(std::move(skData));
#endif
            if (svgStream) {
                auto skiaDom = SkSVGDOM::MakeFromStream(*svgStream, svgThemeColor);
                if (skiaDom) {
                    taskExecutor->PostTask(
                        [successCallback, skiaDom] { successCallback(skiaDom); }, TaskExecutor::TaskType::UI);
                    return;
                }
            }
        }
        LOGE("svg data wrong!");
        taskExecutor->PostTask([failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI);
    };
    CancelableTask cancelableTask(std::move(task));
    if (onBackgroundTaskPostCallback) {
        onBackgroundTaskPostCallback(cancelableTask);
    }
    BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
}

#ifndef USE_ROSEN_DRAWING
void ImageProvider::GetSVGImageDOMAsyncFromData(const sk_sp<SkData>& skData,
#else
void ImageProvider::GetSVGImageDOMAsyncFromData(const std::shared_ptr<RSData>& data,
#endif
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback, std::function<void()> failedCallback,
    const WeakPtr<PipelineBase> context, uint64_t svgThemeColor, OnPostBackgroundTask onBackgroundTaskPostCallback)
{
#ifndef USE_ROSEN_DRAWING
    auto task = [skData, successCallback, failedCallback, context, svgThemeColor, id = Container::CurrentId()] {
#else
    auto task = [data, successCallback, failedCallback, context, svgThemeColor, id = Container::CurrentId()] {
#endif
        ContainerScope scope(id);
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGW("render image or pipeline has been released.");
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

#ifndef USE_ROSEN_DRAWING
        const auto svgStream = std::make_unique<SkMemoryStream>(skData);
#else
        auto skData = data->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
        const auto svgStream = std::make_unique<SkMemoryStream>(skData);
#endif
        if (svgStream) {
            auto skiaDom = SkSVGDOM::MakeFromStream(*svgStream, svgThemeColor);
            if (skiaDom) {
                taskExecutor->PostTask(
                    [successCallback, skiaDom] { successCallback(skiaDom); }, TaskExecutor::TaskType::UI);
                return;
            }
        }
        LOGE("svg data wrong!");
        taskExecutor->PostTask([failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI);
    };
    CancelableTask cancelableTask(std::move(task));
    if (onBackgroundTaskPostCallback) {
        onBackgroundTaskPostCallback(cancelableTask);
    }
    BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
}

#ifndef USE_ROSEN_DRAWING
void ImageProvider::UploadImageToGPUForRender(const WeakPtr<PipelineBase> context, const sk_sp<SkImage>& image,
    const sk_sp<SkData>& data, const std::function<void(sk_sp<SkImage>, sk_sp<SkData>)>&& callback,
    const std::string src)
{
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    callback(image, nullptr);
#else
    if (data && ImageCompressor::GetInstance()->CanCompress()) {
        LOGI("use astc cache %{public}s %{public}d * %{public}d", src.c_str(), image->width(), image->height());
        callback(image, data);
        return;
    }
    auto task = [context, image, callback, src]() {
        ACE_DCHECK(!image->isTextureBacked());
        bool needRaster = ImageCompressor::GetInstance()->CanCompress();
        if (!needRaster) {
            callback(image, nullptr);
            return;
        } else {
            auto rasterizedImage = image->isLazyGenerated() ? image->makeRasterImage() : image;
            if (!rasterizedImage) {
                LOGW("Rasterize image failed. callback.");
                callback(image, nullptr);
                return;
            }
            SkPixmap pixmap;
            if (!rasterizedImage->peekPixels(&pixmap)) {
                LOGW("Could not peek pixels of image for texture upload.");
                callback(rasterizedImage, nullptr);
                return;
            }
            int32_t width = static_cast<int32_t>(pixmap.width());
            int32_t height = static_cast<int32_t>(pixmap.height());
            sk_sp<SkData> compressData;
            if (ImageCompressor::GetInstance()->CanCompress()) {
                compressData = ImageCompressor::GetInstance()->GpuCompress(src, pixmap, width, height);
                ImageCompressor::GetInstance()->WriteToFile(src, compressData, { width, height });
                auto pipelineContext = context.Upgrade();
                if (pipelineContext && pipelineContext->GetTaskExecutor()) {
                    auto taskExecutor = pipelineContext->GetTaskExecutor();
                    taskExecutor->PostDelayedTask(ImageCompressor::GetInstance()->ScheduleReleaseTask(),
                        TaskExecutor::TaskType::UI, ImageCompressor::releaseTimeMs);
                } else {
                    BackgroundTaskExecutor::GetInstance().PostTask(
                        ImageCompressor::GetInstance()->ScheduleReleaseTask());
                }
            }
            callback(image, compressData);
            // Trigger purge cpu bitmap resource, after image upload to gpu.
            SkGraphics::PurgeResourceCache();
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
#endif
}
#else
void ImageProvider::UploadImageToGPUForRender(const WeakPtr<PipelineBase> context,
    const std::shared_ptr<RSImage>& image, const std::shared_ptr<RSData>& data,
    const std::function<void(std::shared_ptr<RSImage>, std::shared_ptr<RSData>)>&& callback, const std::string src)
{
    LOGE("Drawing is not supported");
    callback(image, nullptr);
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> ImageProvider::ResizeSkImage(
    const sk_sp<SkImage>& rawImage, const std::string& src, Size imageSize, bool forceResize)
{
    if (!imageSize.IsValid()) {
        LOGE("not valid size!, imageSize: %{private}s, src: %{private}s", imageSize.ToString().c_str(), src.c_str());
        return rawImage;
    }
    int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + 0.5);
    int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + 0.5);

    bool needResize = false;

    if (!forceResize) {
        if (rawImage->width() > dstWidth) {
            needResize = true;
        } else {
            dstWidth = rawImage->width();
        }
        if (rawImage->height() > dstHeight) {
            needResize = true;
        } else {
            dstHeight = rawImage->height();
        }
    }

    if (!needResize && !forceResize) {
        return rawImage;
    }
    return ApplySizeToSkImage(
        rawImage, dstWidth, dstHeight, ImageObject::GenerateCacheKey(ImageSourceInfo(src), imageSize));
}
#else
std::shared_ptr<RSImage> ImageProvider::ResizeDrawingImage(
    const std::shared_ptr<RSImage>& rawImage, const std::string& src, Size imageSize, bool forceResize)
{
    if (!imageSize.IsValid()) {
        LOGE("not valid size!, imageSize: %{private}s, src: %{private}s", imageSize.ToString().c_str(), src.c_str());
        return rawImage;
    }
    int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + 0.5);
    int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + 0.5);

    bool needResize = false;

    if (!forceResize) {
        if (rawImage->GetWidth() > dstWidth) {
            needResize = true;
        } else {
            dstWidth = rawImage->GetWidth();
        }
        if (rawImage->GetHeight() > dstHeight) {
            needResize = true;
        } else {
            dstHeight = rawImage->GetHeight();
        }
    }

    if (!needResize && !forceResize) {
        return rawImage;
    }
    return ApplySizeToDrawingImage(
        rawImage, dstWidth, dstHeight, ImageObject::GenerateCacheKey(ImageSourceInfo(src), imageSize));
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> ImageProvider::ApplySizeToSkImage(
    const sk_sp<SkImage>& rawImage, int32_t dstWidth, int32_t dstHeight, const std::string& srcKey)
#else
std::shared_ptr<RSImage> ImageProvider::ApplySizeToDrawingImage(
    const std::shared_ptr<RSImage>& rawRSImage, int32_t dstWidth, int32_t dstHeight, const std::string& srcKey)
#endif
{
    ACE_FUNCTION_TRACE();
#ifdef USE_ROSEN_DRAWING
    auto rawImage = rawRSImage->GetImpl<Rosen::Drawing::SkiaImage>()->GetImage();
#endif
    auto scaledImageInfo =
        SkImageInfo::Make(dstWidth, dstHeight, rawImage->colorType(), rawImage->alphaType(), rawImage->refColorSpace());
    SkBitmap scaledBitmap;
    if (!scaledBitmap.tryAllocPixels(scaledImageInfo)) {
        LOGE("Could not allocate bitmap when attempting to scale. srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
#ifndef USE_ROSEN_DRAWING
        return rawImage;
#else
        return rawRSImage;
#endif
    }
    if (!rawImage->scalePixels(scaledBitmap.pixmap(), SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone),
            SkImage::kDisallow_CachingHint)) {
        LOGE("Could not scale pixels srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
#ifndef USE_ROSEN_DRAWING
        return rawImage;
#else
        return rawRSImage;
#endif
    }
    // Marking this as immutable makes the MakeFromBitmap call share the pixels instead of copying.
    scaledBitmap.setImmutable();
    auto scaledImage = SkImage::MakeFromBitmap(scaledBitmap);
    if (scaledImage) {
        const double RESIZE_MAX_PROPORTION = ImageCompressor::GetInstance()->CanCompress() ? 1.0 : 0.25;
        bool needCacheResizedImageFile =
            (1.0 * dstWidth * dstHeight) / (rawImage->width() * rawImage->height()) < RESIZE_MAX_PROPORTION;
        auto context = PipelineBase::GetCurrentContext();
#ifndef USE_ROSEN_DRAWING
        CHECK_NULL_RETURN(context, scaledImage);
#else
        auto scaledRSImage = std::make_shared<RSImage>(static_cast<void*>(&scaledImage));
        CHECK_NULL_RETURN(context, scaledRSImage);
#endif
        // card doesn't encode and cache image file.
        if (needCacheResizedImageFile && !srcKey.empty() && !context->IsFormRender()) {
            BackgroundTaskExecutor::GetInstance().PostTask(
                [srcKey, scaledImage]() {
                    LOGI("write png cache file: %{private}s", srcKey.c_str());
                    auto data = scaledImage->encodeToData(SkEncodedImageFormat::kPNG, 100);
                    if (!data) {
                        LOGI("encode cache image into cache file failed.");
                        return;
                    }
                    ImageFileCache::GetInstance().WriteCacheFile(srcKey, data->data(), data->size());
                },
                BgTaskPriority::LOW);
        }
#ifndef USE_ROSEN_DRAWING
        return scaledImage;
#else
        return scaledRSImage;
#endif
    }
    LOGE("Could not create a scaled image from a scaled bitmap. srcKey: %{private}s, destination size: [%{public}d x"
         " %{public}d], raw image size: [%{public}d x %{public}d]",
        srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
#ifndef USE_ROSEN_DRAWING
    return rawImage;
#else
    return rawRSImage;
#endif
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> ImageProvider::GetSkImage(const std::string& src, const WeakPtr<PipelineBase> context, Size targetSize)
{
    ImageSourceInfo info(src);
    auto imageLoader = ImageLoader::CreateImageLoader(info);
    if (!imageLoader) {
        LOGE("Invalid src, src is %{public}s", src.c_str());
        return nullptr;
    }
    auto imageSkData = imageLoader->LoadImageData(info, context);
    if (!imageSkData) {
        LOGE("fetch data failed. src: %{private}s", src.c_str());
        return nullptr;
    }
    auto rawImage = SkImage::MakeFromEncoded(imageSkData);
    if (!rawImage) {
        LOGE("MakeFromEncoded failed! src: %{private}s", src.c_str());
        return nullptr;
    }
    auto image = ResizeSkImage(rawImage, src, targetSize);
    return image;
}
#else
std::shared_ptr<RSImage> ImageProvider::GetDrawingImage(
    const std::string& src, const WeakPtr<PipelineBase> context, Size targetSize)
{
    ImageSourceInfo info(src);
    auto imageLoader = ImageLoader::CreateImageLoader(info);
    if (!imageLoader) {
        LOGE("Invalid src, src is %{public}s", src.c_str());
        return nullptr;
    }
    auto imageData = imageLoader->LoadImageData(info, context);
    if (!imageData) {
        LOGE("fetch data failed. src: %{private}s", src.c_str());
        return nullptr;
    }
    auto skImage = SkImage::MakeFromEncoded(imageData->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData());
    if (!skImage) {
        LOGE("MakeFromEncoded failed! src: %{private}s", src.c_str());
        return nullptr;
    }
    auto rawImage = std::make_shared<RSImage>(static_cast<void*>(&skImage));
    auto image = ResizeDrawingImage(rawImage, src, targetSize);
    return image;
}
#endif

void ImageProvider::TryLoadImageInfo(const RefPtr<PipelineBase>& context, const std::string& src,
    std::function<void(bool, int32_t, int32_t)>&& loadCallback)
{
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, callback = std::move(loadCallback), context, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto taskExecutor = context->GetTaskExecutor();
            if (!taskExecutor) {
                return;
            }
#ifndef USE_ROSEN_DRAWING
            auto image = ImageProvider::GetSkImage(src, context);
            if (image) {
                callback(true, image->width(), image->height());
                return;
            }
#else
            auto image = ImageProvider::GetDrawingImage(src, context);
            if (image) {
                callback(true, image->GetWidth(), image->GetHeight());
                return;
            }
#endif
            callback(false, 0, 0);
        });
}

#ifndef USE_ROSEN_DRAWING
bool ImageProvider::IsWideGamut(const sk_sp<SkColorSpace>& colorSpace)
{
#else
bool ImageProvider::IsWideGamut(const std::shared_ptr<RSColorSpace>& rsColorSpace)
{
    if (!rsColorSpace) {
        return false;
    }
    auto colorSpace = rsColorSpace->GetImpl<Rosen::Drawing::SkiaColorSpace>()->GetColorSpace();
#endif
    skcms_ICCProfile encodedProfile;
    if (!colorSpace)
        return false;

    colorSpace->toProfile(&encodedProfile);
    if (!encodedProfile.has_toXYZD50) {
        LOGI("This profile's gamut can not be represented by a 3x3 transform to XYZD50");
        return false;
    }
    // Normalize gamut by 1.
    // rgb[3] represents the point of Red, Green and Blue coordinate in color space diagram.
    Point rgb[3];
    auto xyzGamut = encodedProfile.toXYZD50;
    for (int32_t i = 0; i < 3; i++) {
        auto sum = xyzGamut.vals[i][0] + xyzGamut.vals[i][1] + xyzGamut.vals[i][2];
        rgb[i].SetX(xyzGamut.vals[i][0] / sum);
        rgb[i].SetY(xyzGamut.vals[i][1] / sum);
    }
    // Calculate the area enclosed by the coordinates of the three RGB points
    Point red = rgb[0];
    Point green = rgb[1];
    Point blue = rgb[2];
    // Assuming there is a triangle enclosed by three points: A(x1, y1), B(x2, y2), C(x3, y3),
    // the formula for calculating the area of triangle ABC is as follows:
    // S = (x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2.0
    auto areaOfPoint = std::fabs(red.GetX() * green.GetY() + green.GetX() * blue.GetY() + blue.GetX() * green.GetY() -
                                 red.GetX() * blue.GetY() - blue.GetX() * green.GetY() - green.GetX() * red.GetY()) /
                       2.0;
    return GreatNotEqual(areaOfPoint, SRGB_GAMUT_AREA);
}

#ifndef USE_ROSEN_DRAWING
SkImageInfo ImageProvider::MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    SkColorType ct = PixelFormatToSkColorType(pixmap);
    SkAlphaType at = AlphaTypeToSkAlphaType(pixmap);
    sk_sp<SkColorSpace> cs = ColorSpaceToSkColorSpace(pixmap);
    return SkImageInfo::Make(pixmap->GetWidth(), pixmap->GetHeight(), ct, at, cs);
}
#else
RSBitmapFormat ImageProvider::MakeRSBitmapFormatFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    return { PixelFormatToDrawingColorType(pixmap), AlphaTypeToDrawingAlphaType(pixmap) };
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkColorSpace> ImageProvider::ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return SkColorSpace::MakeSRGB(); // Media::PixelMap has not support wide gamut yet.
}
#else
std::shared_ptr<RSColorSpace> ImageProvider::ColorSpaceToDrawingColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return RSColorSpace::CreateSRGB(); // Media::PixelMap has not support wide gamut yet.
}
#endif

#ifndef USE_ROSEN_DRAWING
SkAlphaType ImageProvider::AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return SkAlphaType::kUnknown_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return SkAlphaType::kOpaque_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return SkAlphaType::kPremul_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return SkAlphaType::kUnpremul_SkAlphaType;
        default:
            return SkAlphaType::kUnknown_SkAlphaType;
    }
}
#else
RSAlphaType ImageProvider::AlphaTypeToDrawingAlphaType(const RefPtr<PixelMap>& pixmap)
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
#endif

#ifndef USE_ROSEN_DRAWING
SkColorType ImageProvider::PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return SkColorType::kRGB_565_SkColorType;
        case PixelFormat::RGBA_8888:
            return SkColorType::kRGBA_8888_SkColorType;
        case PixelFormat::BGRA_8888:
            return SkColorType::kBGRA_8888_SkColorType;
        case PixelFormat::ALPHA_8:
            return SkColorType::kAlpha_8_SkColorType;
        case PixelFormat::RGBA_F16:
            return SkColorType::kRGBA_F16_SkColorType;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return SkColorType::kUnknown_SkColorType;
    }
}
#else
RSColorType ImageProvider::PixelFormatToDrawingColorType(const RefPtr<PixelMap>& pixmap)
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
#endif

} // namespace OHOS::Ace
