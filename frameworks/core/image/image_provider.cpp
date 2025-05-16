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

#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#include "drawing/engine_adapter/skia_adapter/skia_image.h"
#include "drawing/engine_adapter/skia_adapter/skia_graphics.h"

#include "base/thread/background_task_executor.h"
#include "core/common/container.h"
#include "core/components_ng/image_provider/adapter/drawing_image_data.h"
#include "core/components_ng/render/adapter/drawing_image.h"
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
        LOGI("other thread is loading same image: %{private}s", imageInfo.ToString().c_str());
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
                    TaskExecutor::TaskType::UI, "ArkUIImageProviderLoadFailed");
                return;
            }
            auto obj = imageObj->Clone();
            taskExecutor->PostTask(
                [obj, imageInfo, callback]() {
                    if (callback.successCallback) {
                        callback.successCallback(imageInfo, obj);
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUIImageProviderLoadSuccess");
            if (canStartUploadImageObj) {
                bool forceResize = (!obj->IsSvg()) && (imageInfo.IsSourceDimensionValid());
                obj->UploadToGpuForRender(
                    context, callback.uploadCallback, callback.failedCallback, obj->GetImageSize(), forceResize, true);
            }
        }
    } else {
        LOGW("no loading image: %{private}s", imageInfo.ToString().c_str());
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
            TaskExecutor::TaskType::UI, "ArkUIImageProviderUploadResult");
    } else {
        LOGW("no uploading image: %{private}s", imageInfo.ToString().c_str());
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
    return imageCache->GetCacheImgObj(imageInfo.ToString(false));
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

std::shared_ptr<RSData> ImageProvider::LoadImageRawData(
    const ImageSourceInfo& imageInfo, const RefPtr<PipelineBase> context)
{
    ACE_FUNCTION_TRACE();
    auto imageCache = context->GetImageCache();
    if (imageCache) {
        // 1. try get data from cache.
        auto cacheData = imageCache->GetCacheImageData(imageInfo.GetSrc());
        if (cacheData) {
            return AceType::DynamicCast<NG::DrawingImageData>(cacheData)->GetRSData();
        }
    }
    // 2. try load raw image file.
    auto imageLoader = ImageLoader::CreateImageLoader(imageInfo);
    if (!imageLoader) {
        LOGE("imageLoader create failed. imageInfo: %{private}s", imageInfo.ToString().c_str());
        return nullptr;
    }
    ImageErrorInfo errorInfo;
    auto data = imageLoader->LoadImageData(imageInfo, errorInfo, context);
    if (data && imageCache) {
        // cache drawing data.
        imageCache->CacheImageData(imageInfo.GetSrc(), AceType::MakeRefPtr<NG::DrawingImageData>(data));
    }
    return data;
}

std::shared_ptr<RSData> ImageProvider::LoadImageRawDataFromFileCache(
    const RefPtr<PipelineBase> context, const std::string key, const std::string suffix)
{
    ACE_FUNCTION_TRACE();
    auto data = ImageFileCache::GetInstance().GetDataFromCacheFile(key, suffix);
    if (data) {
        return AceType::DynamicCast<NG::DrawingImageData>(data)->GetRSData();
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
        ImageErrorInfo errorInfo;
        auto imageData = imageLoader->LoadImageData(info, errorInfo, context);
        if (imageData) {
            auto skData = SkData::MakeWithoutCopy(imageData->GetData(), imageData->GetSize());
            const auto svgStream = std::make_unique<SkMemoryStream>(std::move(skData));
            if (svgStream) {
                auto skiaDom = SkSVGDOM::MakeFromStream(*svgStream, svgThemeColor);
                if (skiaDom) {
                    taskExecutor->PostTask(
                        [successCallback, skiaDom] { successCallback(skiaDom); },
                        TaskExecutor::TaskType::UI, "ArkUIImageGetSvgDomFromSrcSuccess");
                    return;
                }
            }
        }
        LOGE("svg data wrong!");
        taskExecutor->PostTask(
            [failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI, "ArkUIImageGetSvgDomFromSrcFailed");
    };
    CancelableTask cancelableTask(std::move(task));
    if (onBackgroundTaskPostCallback) {
        onBackgroundTaskPostCallback(cancelableTask);
    }
    BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
}

void ImageProvider::GetSVGImageDOMAsyncFromData(const std::shared_ptr<RSData>& data,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback, std::function<void()> failedCallback,
    const WeakPtr<PipelineBase> context, uint64_t svgThemeColor, OnPostBackgroundTask onBackgroundTaskPostCallback)
{
    auto task = [data, successCallback, failedCallback, context, svgThemeColor, id = Container::CurrentId()] {
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

        auto skData = SkData::MakeWithoutCopy(data->GetData(), data->GetSize());
        const auto svgStream = std::make_unique<SkMemoryStream>(skData);
        if (svgStream) {
            auto skiaDom = SkSVGDOM::MakeFromStream(*svgStream, svgThemeColor);
            if (skiaDom) {
                taskExecutor->PostTask(
                    [successCallback, skiaDom] { successCallback(skiaDom); },
                    TaskExecutor::TaskType::UI, "ArkUIImageGetSvgDomFromDataSuccess");
                return;
            }
        }
        LOGE("svg data wrong!");
        taskExecutor->PostTask(
            [failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI, "ArkUIImageGetSvgDomFromDataFailed");
    };
    CancelableTask cancelableTask(std::move(task));
    if (onBackgroundTaskPostCallback) {
        onBackgroundTaskPostCallback(cancelableTask);
    }
    BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
}

void ImageProvider::UploadImageToGPUForRender(const WeakPtr<PipelineBase> context,
    const std::shared_ptr<RSImage>& image, const std::shared_ptr<RSData>& data,
    const std::function<void(std::shared_ptr<RSImage>, std::shared_ptr<RSData>)>&& callback, const std::string src)
{
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    callback(image, nullptr);
#else
    if (data && ImageCompressor::GetInstance()->CanCompress()) {
        LOGI("use astc cache %{private}s %{public}d * %{public}d", src.c_str(), image->GetWidth(), image->GetHeight());
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
            auto rasterizedImage = image->IsLazyGenerated() ? image->MakeRasterImage() : image;
            if (!rasterizedImage) {
                LOGW("Rasterize image failed. callback.");
                callback(image, nullptr);
                return;
            }
            if (!rasterizedImage->CanPeekPixels()) {
                LOGW("Could not peek pixels of image for texture upload.");
                callback(rasterizedImage, nullptr);
                return;
            }

            RSBitmap rsBitmap;
            RSBitmapFormat rsBitmapFormat { image->GetColorType(), image->GetAlphaType() };
            rsBitmap.Build(image->GetWidth(), image->GetHeight(), rsBitmapFormat);
            if (!image->ReadPixels(rsBitmap, 0, 0)) {
                callback(image, nullptr);
                return;
            }

            int32_t width = static_cast<int32_t>(rsBitmap.GetWidth());
            int32_t height = static_cast<int32_t>(rsBitmap.GetHeight());
            std::shared_ptr<RSData> compressData;
            if (ImageCompressor::GetInstance()->CanCompress()) {
                compressData = ImageCompressor::GetInstance()->GpuCompress(src, rsBitmap, width, height);
                ImageCompressor::GetInstance()->WriteToFile(src, compressData, { width, height });
                auto pipelineContext = context.Upgrade();
                if (pipelineContext && pipelineContext->GetTaskExecutor()) {
                    auto taskExecutor = pipelineContext->GetTaskExecutor();
                    taskExecutor->PostDelayedTask(ImageCompressor::GetInstance()->ScheduleReleaseTask(),
                        TaskExecutor::TaskType::UI, ImageCompressor::releaseTimeMs,
                        "ArkUIImageCompressorScheduleRelease");
                } else {
                    BackgroundTaskExecutor::GetInstance().PostTask(
                        ImageCompressor::GetInstance()->ScheduleReleaseTask());
                }
            }
            callback(image, compressData);
            // Trigger purge cpu bitmap resource, after image upload to gpu.
            Rosen::Drawing::SkiaGraphics::PurgeResourceCache();
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
#endif
}

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

std::shared_ptr<RSImage> ImageProvider::ApplySizeToDrawingImage(
    const std::shared_ptr<RSImage>& rawRSImage, int32_t dstWidth, int32_t dstHeight, const std::string& srcKey)
{
    ACE_FUNCTION_TRACE();
    RSImageInfo scaledImageInfo { dstWidth, dstHeight,
        rawRSImage->GetColorType(), rawRSImage->GetAlphaType(), rawRSImage->GetColorSpace() };
    RSBitmap scaledBitmap;
    if (!scaledBitmap.TryAllocPixels(scaledImageInfo)) {
        LOGE("Could not allocate bitmap when attempting to scale. srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawRSImage->GetWidth(), rawRSImage->GetHeight());
        return rawRSImage;
    }
    if (!rawRSImage->ScalePixels(scaledBitmap, RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE), false)) {
        LOGE("Could not scale pixels srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawRSImage->GetWidth(), rawRSImage->GetHeight());
        return rawRSImage;
    }
    // Marking this as immutable makes the MakeFromBitmap call share the pixels instead of copying.
    scaledBitmap.SetImmutable();
    std::shared_ptr<RSImage> scaledImage = std::make_shared<RSImage>();
    if (scaledImage->BuildFromBitmap(scaledBitmap)) {
        const double RESIZE_MAX_PROPORTION = ImageCompressor::GetInstance()->CanCompress() ? 1.0 : 0.25;
        bool needCacheResizedImageFile =
            (1.0 * dstWidth * dstHeight) / (rawRSImage->GetWidth() * rawRSImage->GetHeight()) < RESIZE_MAX_PROPORTION;
        auto context = PipelineBase::GetCurrentContext();
        // card doesn't encode and cache image file.
        if (needCacheResizedImageFile && !srcKey.empty() && context && !context->IsFormRender()) {
            BackgroundTaskExecutor::GetInstance().PostTask(
                [srcKey, scaledImage]() {
                    LOGI("write png cache file: %{private}s", srcKey.c_str());
                    auto data = scaledImage->EncodeToData(RSEncodedImageFormat::PNG, 100);
                    if (!data) {
                        return;
                    }
                    RSDataWrapper* wrapper = new RSDataWrapper{data};
                    auto skData = SkData::MakeWithProc(data->GetData(), data->GetSize(),
                        RSDataWrapperReleaseProc, wrapper);
                    if (!skData) {
                        LOGI("encode cache image into cache file failed.");
                        return;
                    }
                    ImageFileCache::GetInstance().WriteCacheFile(srcKey, skData->data(), skData->size());
                },
                BgTaskPriority::LOW);
        }
        return scaledImage;
    }
    LOGE("Could not create a scaled image from a scaled bitmap. srcKey: %{private}s, destination size: [%{public}d x"
         " %{public}d], raw image size: [%{public}d x %{public}d]",
        srcKey.c_str(), dstWidth, dstHeight, rawRSImage->GetWidth(), rawRSImage->GetHeight());
    return rawRSImage;
}

std::shared_ptr<RSImage> ImageProvider::GetDrawingImage(
    const std::string& src, const WeakPtr<PipelineBase> context, Size targetSize)
{
    ImageSourceInfo info(src);
    auto imageLoader = ImageLoader::CreateImageLoader(info);
    if (!imageLoader) {
        LOGE("Invalid src, src is %{private}s", src.c_str());
        return nullptr;
    }
    ImageErrorInfo errorInfo;
    auto imageData = imageLoader->LoadImageData(info, errorInfo, context);
    if (!imageData) {
        LOGE("fetch data failed. src: %{private}s", src.c_str());
        return nullptr;
    }
    std::shared_ptr<RSImage> rawImage = std::make_shared<RSImage>();
    if (!rawImage->MakeFromEncoded(imageData)) {
        LOGE("MakeFromEncoded failed! src: %{private}s", src.c_str());
        return nullptr;
    }
    auto image = ResizeDrawingImage(rawImage, src, targetSize);
    return image;
}

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
            auto image = ImageProvider::GetDrawingImage(src, context);
            if (image) {
                callback(true, image->GetWidth(), image->GetHeight());
                return;
            }
            callback(false, 0, 0);
        });
}

bool ImageProvider::IsWideGamut(const std::shared_ptr<RSColorSpace>& rsColorSpace)
{
    if (!rsColorSpace) {
        return false;
    }
    // Normalize gamut by 1.
    // rgb[3] represents the point of Red, Green and Blue coordinate in color space diagram.
    Point rgb[3];
    bool hasToXYZD50 = true;
    auto xyzGamut = rsColorSpace->ToXYZD50(hasToXYZD50);
    if (!hasToXYZD50) {
        return false;
    }
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

RSBitmapFormat ImageProvider::MakeRSBitmapFormatFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    return { PixelFormatToDrawingColorType(pixmap), AlphaTypeToDrawingAlphaType(pixmap) };
}
RSImageInfo ImageProvider::MakeRSImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    RSColorType ct = PixelFormatToDrawingColorType(pixmap);
    RSAlphaType at = AlphaTypeToDrawingAlphaType(pixmap);
    std::shared_ptr<RSColorSpace> cs = ColorSpaceToDrawingColorSpace(pixmap);
    return { pixmap->GetWidth(), pixmap->GetHeight(), ct, at, cs };
}

std::shared_ptr<RSColorSpace> ImageProvider::ColorSpaceToDrawingColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return RSColorSpace::CreateSRGB(); // Media::PixelMap has not support wide gamut yet.
}

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

RSColorType ImageProvider::PixelFormatToDrawingColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return RSColorType::COLORTYPE_RGB_565;
        case PixelFormat::RGBA_8888:
            return RSColorType::COLORTYPE_RGBA_8888;
        case PixelFormat::RGBA_1010102:
            return RSColorType::COLORTYPE_RGBA_1010102;
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

} // namespace OHOS::Ace
