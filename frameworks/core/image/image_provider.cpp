/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "experimental/svg/model/SkSVGDOM.h"
#include "third_party/skia/include/core/SkGraphics.h"
#include "third_party/skia/include/core/SkStream.h"

#include "base/thread/background_task_executor.h"
#include "core/components/image/flutter_render_image.h"
#include "core/event/ace_event_helper.h"
#include "core/image/flutter_image_cache.h"
#include "core/image/image_object.h"
namespace OHOS::Ace {
namespace {

constexpr double RESIZE_MAX_PROPORTION = 0.5 * 0.5; // Cache image when resize exceeds 25%
// If a picture is a wide color gamut picture, its area value will be larger than this threshold.
constexpr double SRGB_GAMUT_AREA = 0.104149;

} // namespace

void ImageProvider::FatchImageObject(
    ImageSourceInfo imageInfo,
    ImageObjSuccessCallback successCallback,
    FailedCallback failedCallback,
    const WeakPtr<PipelineContext> context,
    bool syncMode,
    bool useSkiaSvg,
    const std::optional<Color>& color,
    OnPostBackgroundTask onBackgroundTaskPostCallback)
{
    auto task = [ context, imageInfo, successCallback, failedCallback, useSkiaSvg, color] () {
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGE("pipline context has been released.");
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("task executor is null.");
            return;
        }
        auto imageCache = pipelineContext->GetImageCache();
        if (imageCache) {
            auto imgObj = imageCache->GetCacheImgObj(imageInfo.ToString());
            if (imgObj) {
                LOGE("image object got from cache: %{public}s", imageInfo.ToString().c_str());
                taskExecutor->PostTask([successCallback, imageInfo, imgObj]() { successCallback(imageInfo, imgObj); },
                    TaskExecutor::TaskType::UI);
                return;
            }
        }
        auto imageObj = GeneraterAceImageObject(imageInfo, pipelineContext, useSkiaSvg, color);
        if (!imageObj) {
            taskExecutor->PostTask(
                [failedCallback, imageInfo] { failedCallback(imageInfo); }, TaskExecutor::TaskType::UI);
        } else {
            taskExecutor->PostTask([successCallback, imageInfo, imageObj]() { successCallback(imageInfo, imageObj); },
                TaskExecutor::TaskType::UI);
        }
    };
    if (syncMode) {
        task();
    } else {
        CancelableTask cancelableTask(std::move(task));
        if (onBackgroundTaskPostCallback) {
            onBackgroundTaskPostCallback(cancelableTask);
        }
        BackgroundTaskExecutor::GetInstance().PostTask(cancelableTask);
    }
}

RefPtr<ImageObject> ImageProvider::GeneraterAceImageObject(
    const ImageSourceInfo& imageInfo,
    const RefPtr<PipelineContext> context,
    bool useSkiaSvg,
    const std::optional<Color>& color)
{
    auto imageData = LoadImageRawData(imageInfo, context);

    if (!imageData) {
        LOGE("load image data failed.");
        return nullptr;
    }

    return ImageObject::BuildImageObject(imageInfo, context, imageData, useSkiaSvg, color);
}

sk_sp<SkData> ImageProvider::LoadImageRawData(
    const ImageSourceInfo& imageInfo,
    const RefPtr<PipelineContext> context,
    const Size& targetSize)
{
    auto imageCache = context->GetImageCache();
    if (imageCache) {
        // 1. try get data from cache.
        auto cacheData = imageCache->GetCacheImageData(imageInfo.GetSrc());
        if (cacheData) {
            LOGD("sk data from memory cache.");
            return AceType::DynamicCast<SkiaCachedImageData>(cacheData)->imageData;
        }
        // 2 try get data from file cache.
        if (targetSize.IsValid()) {
            LOGD("size valid try load from cache.");
            std::string cacheFilePath =
                ImageCache::GetImageCacheFilePath(ImageObject::GenerateCacheKey(imageInfo.GetSrc(), targetSize));
            LOGD("cache file path: %{public}s", cacheFilePath.c_str());
            if (ImageCache::GetFromCacheFile(cacheFilePath)) {
                LOGD("cache file found: %{public}s", cacheFilePath.c_str());
                auto cacheFileLoader = AceType::MakeRefPtr<FileImageLoader>();
                auto data = cacheFileLoader->LoadImageData(std::string("file:/").append(cacheFilePath));
                if (data) {
                    return data;
                } else {
                    LOGW("load data from cache file failed, try load from raw image file.");
                }
            }
        } else {
            LOGD("target size is not valid, load raw image file.");
        }
    }
    // 3. try load raw image file.
    auto imageLoader = ImageLoader::CreateImageLoader(imageInfo);
    if (!imageLoader) {
        LOGE("imageLoader create failed.");
        return nullptr;
    }
    auto data = imageLoader->LoadImageData(imageInfo.GetSrc(), context);
    if (data && imageCache) {
        // cache sk data.
        imageCache->CacheImageData(imageInfo.GetSrc(), AceType::MakeRefPtr<SkiaCachedImageData>(data));
    }
    return data;
}

void ImageProvider::GetSVGImageDOMAsyncFromSrc(
    const std::string& src,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback,
    std::function<void()> failedCallback,
    const WeakPtr<PipelineContext> context,
    uint64_t svgThemeColor,
    OnPostBackgroundTask onBackgroundTaskPostCallback)
{
    auto task = [ src, successCallback, failedCallback, context, svgThemeColor ] {
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGW("render image or pipeline has been released.");
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        auto imageLoader = ImageLoader::CreateImageLoader(ImageSourceInfo(src));
        if (!imageLoader) {
            LOGE("load image failed when create image loader.");
            return;
        }
        auto imageData = imageLoader->LoadImageData(src, context);
        if (imageData) {
            const auto svgStream = std::make_unique<SkMemoryStream>(std::move(imageData));
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

void ImageProvider::GetSVGImageDOMAsyncFromData(
    const sk_sp<SkData>& skData,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback,
    std::function<void()> failedCallback,
    const WeakPtr<PipelineContext> context,
    uint64_t svgThemeColor,
    OnPostBackgroundTask onBackgroundTaskPostCallback)
{
    auto task = [ skData, successCallback, failedCallback, context, svgThemeColor ] {
        auto pipelineContext = context.Upgrade();
        if (!pipelineContext) {
            LOGW("render image or pipeline has been released.");
            return;
        }
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        const auto svgStream = std::make_unique<SkMemoryStream>(skData);
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

void ImageProvider::UploadImageToGPUForRender(
    const sk_sp<SkImage>& image,
    const std::function<void(flutter::SkiaGPUObject<SkImage>)>&& callback,
    const RefPtr<FlutterRenderTaskHolder>& renderTaskHolder)
{
#if defined(DUMP_DRAW_CMD) || defined(GPU_DISABLED)
    // If want to dump draw command or gpu disabled, should use CPU image.
    callback({ image, renderTaskHolder->unrefQueue });
#else
    // TODO: software render not upload to gpu

    auto rasterizedImage = image->makeRasterImage();
    if (!rasterizedImage) {
        LOGW("Rasterize image failed. callback.");
        callback({ image, renderTaskHolder->unrefQueue });
        return;
    }
    if (renderTaskHolder->IsValid()) {
        auto task = [rasterizedImage, callback, renderTaskHolder] () {
            if (!renderTaskHolder->ioManager) {
                // Shell is closing.
                callback({ rasterizedImage, renderTaskHolder->unrefQueue });
                return;
            }
            ACE_DCHECK(!rasterizedImage->isTextureBacked());
            auto resContext = renderTaskHolder->ioManager->GetResourceContext();
            if (!resContext) {
                callback({ rasterizedImage, renderTaskHolder->unrefQueue });
                return;
            }
            SkPixmap pixmap;
            if (!rasterizedImage->peekPixels(&pixmap)) {
                LOGW("Could not peek pixels of image for texture upload.");
                callback({ rasterizedImage, renderTaskHolder->unrefQueue });
                return;
            }
            auto textureImage =
                SkImage::MakeCrossContextFromPixmap(resContext.get(), pixmap, true, pixmap.colorSpace(), true);
            callback({ textureImage ? textureImage : rasterizedImage, renderTaskHolder->unrefQueue });

            // Trigger purge cpu bitmap resource, after image upload to gpu.
            SkGraphics::PurgeResourceCache();
        };
        renderTaskHolder->ioTaskRunner->PostTask(std::move(task));
    } else {
        callback({ rasterizedImage, renderTaskHolder->unrefQueue });
    }
#endif
}

sk_sp<SkImage> ImageProvider::ResizeSkImage(
    const sk_sp<SkImage>& rawImage,
    const std::string& src,
    Size imageSize,
    bool forceResize)
{
    if (!imageSize.IsValid()) {
        LOGE("not valid size!, imageSize: %{private}s", imageSize.ToString().c_str());
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
        rawImage,
        dstWidth,
        dstHeight,
        ImageObject::GenerateCacheKey(src, imageSize));
}

sk_sp<SkImage> ImageProvider::ApplySizeToSkImage(
    const sk_sp<SkImage>& rawImage,
    int32_t dstWidth,
    int32_t dstHeight,
    const std::string& srcKey)
{
    auto scaledImageInfo =
        SkImageInfo::Make(dstWidth, dstHeight, rawImage->colorType(), rawImage->alphaType(), rawImage->refColorSpace());
    SkBitmap scaledBitmap;
    if (!scaledBitmap.tryAllocPixels(scaledImageInfo)) {
        LOGE("Could not allocate bitmap when attempting to scale.");
        return rawImage;
    }
    if (!rawImage->scalePixels(scaledBitmap.pixmap(), kLow_SkFilterQuality, SkImage::kDisallow_CachingHint)) {
        LOGE("Could not scale pixels");
        return rawImage;
    }
    // Marking this as immutable makes the MakeFromBitmap call share the pixels instead of copying.
    scaledBitmap.setImmutable();
    auto scaledImage = SkImage::MakeFromBitmap(scaledBitmap);
    if (scaledImage) {
        bool needCacheResizedImageFile =
            (1.0 * dstWidth * dstHeight) / (rawImage->width() * rawImage->height()) < RESIZE_MAX_PROPORTION;
        if (needCacheResizedImageFile && !srcKey.empty()) {
            auto data = scaledImage->encodeToData(SkEncodedImageFormat::kPNG, 100);
            if (data) {
                LOGD("write cache file: %{private}s", srcKey.c_str());
                ImageCache::WriteCacheFile(srcKey, data->data(), data->size());
            }
        }
        return scaledImage;
    }
    LOGE("Could not create a scaled image from a scaled bitmap.");
    return rawImage;
}

sk_sp<SkImage> ImageProvider::GetSkImage(
    const std::string& src,
    const WeakPtr<PipelineContext> context,
    Size targetSize)
{
    auto imageLoader = ImageLoader::CreateImageLoader(ImageSourceInfo(src));
    auto imageSkData = imageLoader->LoadImageData(src, context);
    if (!imageSkData) {
        LOGE("fetch data failed");
        return nullptr;
    }
    auto rawImage = SkImage::MakeFromEncoded(imageSkData);
    if (!rawImage) {
        LOGE("MakeFromEncoded failed!");
        return nullptr;
    }
    auto image = ResizeSkImage(rawImage, src, targetSize);
    return image;
}

void ImageProvider::CanLoadImage(
    const RefPtr<PipelineContext>& context,
    const std::string& src,
    const std::map<std::string, EventMarker>& callbacks)
{
    if (callbacks.find("success") == callbacks.end() || callbacks.find("fail") == callbacks.end()) {
        return;
    }
    auto onSuccess = AceAsyncEvent<void()>::Create(callbacks.at("success"), context);
    auto onFail = AceAsyncEvent<void()>::Create(callbacks.at("fail"), context);
    BackgroundTaskExecutor::GetInstance().PostTask([src, onSuccess, onFail, context]() {
        auto taskExecutor = context->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        auto image = ImageProvider::GetSkImage(src, context);
        if (image) {
            taskExecutor->PostTask(
                [onSuccess] {
                    onSuccess();
                },
                TaskExecutor::TaskType::UI);
            return;
        }
        taskExecutor->PostTask(
            [onFail] {
                onFail();
            },
            TaskExecutor::TaskType::UI);
    });
}

bool ImageProvider::IsWideGamut(const sk_sp<SkColorSpace>& colorSpace)
{
    skcms_ICCProfile encodedProfile;
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
        red.GetX() * blue.GetY() - blue.GetX() * green.GetY() - green.GetX() * red.GetY()) / 2.0;
    return GreatNotEqual(areaOfPoint, SRGB_GAMUT_AREA);
}

} // namespace OHOS::Ace
