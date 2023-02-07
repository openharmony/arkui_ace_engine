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

#include "core/components_ng/image_provider/adapter/flutter_image_provider.h"

#include <mutex>
#include <utility>

#include "flutter/fml/memory/ref_counted.h"

#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#ifdef NG_BUILD
#include "ace_shell/shell/common/window_manager.h"
#include "flutter/lib/ui/io_manager.h"
#else
#include "flutter/lib/ui/painting/image.h"
#endif
#include "third_party/skia/include/codec/SkCodec.h"
#include "third_party/skia/include/core/SkGraphics.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/image_provider/svg_image_object.h"
#include "core/components_ng/render/adapter/skia_canvas_image.h"
#include "core/image/flutter_image_cache.h"
#include "core/image/image_compressor.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifdef NG_BUILD
#include "core/components_ng/render/adapter/flutter_canvas_image.h"
#endif

namespace OHOS::Ace::NG {
namespace {

sk_sp<SkImage> ApplySizeToSkImage(
    const sk_sp<SkImage>& rawImage, int32_t dstWidth, int32_t dstHeight, const std::string& srcKey)
{
    ACE_FUNCTION_TRACE();
    auto scaledImageInfo =
        SkImageInfo::Make(dstWidth, dstHeight, rawImage->colorType(), rawImage->alphaType(), rawImage->refColorSpace());
    SkBitmap scaledBitmap;
    if (!scaledBitmap.tryAllocPixels(scaledImageInfo)) {
        LOGE("Could not allocate bitmap when attempting to scale. srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
        return rawImage;
    }
#ifdef NG_BUILD
    if (!rawImage->scalePixels(
            scaledBitmap.pixmap(), SkSamplingOptions(SkFilterMode::kLinear), SkImage::kDisallow_CachingHint)) {
#else
    if (!rawImage->scalePixels(scaledBitmap.pixmap(), kLow_SkFilterQuality, SkImage::kDisallow_CachingHint)) {
#endif
        LOGE("Could not scale pixels srcKey: %{private}s, destination size: [%{public}d x"
             " %{public}d], raw image size: [%{public}d x %{public}d]",
            srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
        return rawImage;
    }
    // Marking this as immutable makes the MakeFromBitmap call share the pixels instead of copying.
    scaledBitmap.setImmutable();
    auto scaledImage = SkImage::MakeFromBitmap(scaledBitmap);
    CHECK_NULL_RETURN_NOLOG(scaledImage, rawImage);
    return scaledImage;
}

static sk_sp<SkImage> ResizeSkImage(
    const sk_sp<SkImage>& rawImage, const std::string& src, const SizeF& resizeTarget, bool forceResize)
{
    if (!resizeTarget.IsPositive()) {
        LOGE("not valid size! resizeTarget: %{public}s, src: %{public}s", resizeTarget.ToString().c_str(), src.c_str());
        return rawImage;
    }
    int32_t dstWidth = static_cast<int32_t>(resizeTarget.Width() + 0.5);
    int32_t dstHeight = static_cast<int32_t>(resizeTarget.Height() + 0.5);

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
    return ApplySizeToSkImage(rawImage, dstWidth, dstHeight, src);
}

} // namespace

RefPtr<CanvasImage> ImageProvider::QueryCanvasImageFromCache(const ImageSourceInfo& src, const SizeF& targetSize)
{
    // Query [CanvasImage] from cache, if hit, notify load success immediately and returns true
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN_NOLOG(pipelineCtx, nullptr);
    CHECK_NULL_RETURN_NOLOG(pipelineCtx->GetImageCache(), nullptr);
    auto key = ImageUtils::GenerateImageKey(src, targetSize);
    auto cache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto cacheImage = cache->GetCacheImage(key);
    CHECK_NULL_RETURN_NOLOG(cacheImage, nullptr);
#ifdef NG_BUILD
    auto canvasImage = cacheImage->imagePtr;
#else
    auto flutterCanvasImage = cacheImage->imagePtr;
    auto canvasImage = CanvasImage::Create(&flutterCanvasImage);
    auto skiaCanvasImage = DynamicCast<SkiaCanvasImage>(canvasImage);
    CHECK_NULL_RETURN(skiaCanvasImage, nullptr);
    skiaCanvasImage->SetUniqueID(cacheImage->uniqueId);
#endif
    if (canvasImage) {
        LOGD("[ImageCache][CanvasImage] succeed find canvas image from cache: %{public}s", key.c_str());
    }
    return canvasImage;
}

void ImageProvider::MakeCanvasImageHelper(const WeakPtr<ImageObject>& objWp, const SizeF& targetSize,
    const RefPtr<RenderTaskHolder>& renderTaskHolder, bool forceResize, bool sync)
{
    auto obj = objWp.Upgrade();
    CHECK_NULL_VOID(obj && renderTaskHolder);
    auto flutterRenderTaskHolder = DynamicCast<FlutterRenderTaskHolder>(renderTaskHolder);
    CHECK_NULL_VOID(flutterRenderTaskHolder);
    CHECK_NULL_VOID_NOLOG(ImageProvider::PrepareImageData(obj));
    // resize image
    auto skiaImageData = DynamicCast<SkiaImageData>(obj->GetData());
    CHECK_NULL_VOID(skiaImageData && skiaImageData->GetSkData());
    auto rawImage = SkImage::MakeFromEncoded(skiaImageData->GetSkData());
    auto key = ImageUtils::GenerateImageKey(obj->GetSourceInfo(), targetSize);
    if (!rawImage) {
        std::string errorMessage(
            "Static image MakeFromEncoded fail! The image format is not supported, please check image format.");
        ImageProvider::FailCallback(key, errorMessage, sync);
        return;
    }
    // get compressed image for file cache
    sk_sp<SkImage> image = rawImage;
    auto compressFileData = ImageLoader::LoadImageDataFromFileCache(key, ".astc");
    if (!compressFileData) {
        image = ResizeSkImage(rawImage, obj->GetSourceInfo().GetSrc(), targetSize, forceResize);
    }
    CHECK_NULL_VOID(image);
    // create gpu object
    flutter::SkiaGPUObject<SkImage> skiaGpuObjSkImage({ image, flutterRenderTaskHolder->unrefQueue });
#ifdef NG_BUILD
    auto canvasImage = CanvasImage::Create();
    auto flutterImage = AceType::DynamicCast<NG::FlutterCanvasImage>(canvasImage);
    if (flutterImage) {
        flutterImage->SetImage(std::move(skiaGpuObjSkImage));
    }
#else
    // create canvas image
    auto flutterCanvasImage = flutter::CanvasImage::Create();
    flutterCanvasImage->set_image(std::move(skiaGpuObjSkImage));
    auto canvasImage = CanvasImage::Create(&flutterCanvasImage);
    CHECK_NULL_VOID(canvasImage);
    ImageProvider::CacheCanvasImage(canvasImage, key);
#endif
    // upload
    auto uploadTask = [key, sync](const RefPtr<CanvasImage>& canvasImage) {
        ImageProvider::SuccessCallback(canvasImage, key, sync);
    };
    ImageProvider::UploadImageToGPUForRender(
        canvasImage, std::move(uploadTask), renderTaskHolder, key, targetSize, compressFileData, sync);
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

    auto renderTaskHolder = CreateRenderTaskHolder();
    CHECK_NULL_VOID(renderTaskHolder);
    if (sync) {
        ImageProvider::MakeCanvasImageHelper(obj, targetSize, renderTaskHolder, forceResize, true);
    } else {
        std::scoped_lock<std::mutex> lock(taskMtx_);
        // wrap with [CancelableCallback] and record in [tasks_] map
        CancelableCallback<void()> task;
        task.Reset([objWp, targetSize, renderTaskHolder, forceResize] {
            MakeCanvasImageHelper(objWp, targetSize, renderTaskHolder, forceResize);
        });
        tasks_[key].bgTask_ = task;
        ImageUtils::PostToBg(task);
    }
}

RefPtr<RenderTaskHolder> ImageProvider::CreateRenderTaskHolder()
{
    CHECK_NULL_RETURN(CheckThread(TaskExecutor::TaskType::UI), nullptr);
#ifdef NG_BUILD
    int32_t id = Container::CurrentId();
    auto currentState = flutter::ace::WindowManager::GetWindow(id);
#else
    auto* currentState = flutter::UIDartState::Current();
#endif
    CHECK_NULL_RETURN(currentState, nullptr);
    return MakeRefPtr<FlutterRenderTaskHolder>(currentState->GetSkiaUnrefQueue(), currentState->GetIOManager(),
        currentState->GetTaskRunners().GetIOTaskRunner());
}

void ImageProvider::UploadImageToGPUForRender(const RefPtr<CanvasImage>& canvasImage,
    std::function<void(RefPtr<CanvasImage>)>&& callback, const RefPtr<RenderTaskHolder>& renderTaskHolder,
    const std::string& key, const SizeF& resizeTarget, const RefPtr<ImageData>& data, bool syncLoad)
{
    CHECK_NULL_VOID(renderTaskHolder);
    auto flutterRenderTaskHolder = DynamicCast<FlutterRenderTaskHolder>(renderTaskHolder);
    CHECK_NULL_VOID(flutterRenderTaskHolder);
#ifdef UPLOAD_GPU_DISABLED
    // If want to dump draw command or gpu disabled, should use CPU image.
    callback(canvasImage);
#else
    auto skiaCanvasImage = DynamicCast<SkiaCanvasImage>(canvasImage);
    CHECK_NULL_VOID(skiaCanvasImage);
    // load compress cache
    if (data) {
        int32_t dstWidth = static_cast<int32_t>(resizeTarget.Width() + 0.5);
        int32_t dstHeight = static_cast<int32_t>(resizeTarget.Height() + 0.5);

        auto skiaImageData = DynamicCast<SkiaImageData>(data);
        CHECK_NULL_VOID(skiaImageData);
        auto skdata = skiaImageData->GetSkData();
        auto stripped = ImageCompressor::StripFileHeader(skdata);
        LOGI("use astc cache %{public}s %{public}d×%{public}d", key.c_str(), dstWidth, dstHeight);
        skiaCanvasImage->SetCompressData(stripped, dstWidth, dstHeight);
        skiaCanvasImage->ReplaceSkImage({ nullptr, flutterRenderTaskHolder->unrefQueue });
        callback(skiaCanvasImage);
        return;
    }
    if (!ImageCompressor::GetInstance()->CanCompress()) {
        callback(skiaCanvasImage);
        return;
    }

    auto task = [callback, flutterRenderTaskHolder, skiaCanvasImage, id = Container::CurrentId(), src = key] {
        ContainerScope scope(id);
        CHECK_NULL_VOID(flutterRenderTaskHolder);
        auto skImage = skiaCanvasImage->GetCanvasImage();
        CHECK_NULL_VOID(skImage);
        auto rasterizedImage = skImage->makeRasterImage();
        if (!rasterizedImage) {
            LOGW("Rasterize image failed. callback.");
            callback(skiaCanvasImage);
            return;
        }
        ACE_DCHECK(!rasterizedImage->isTextureBacked());
        SkPixmap pixmap;
        if (!rasterizedImage->peekPixels(&pixmap)) {
            LOGW("Could not peek pixels of image for texture upload.");
            callback(skiaCanvasImage);
            return;
        }
        int32_t width = static_cast<int32_t>(pixmap.width());
        int32_t height = static_cast<int32_t>(pixmap.height());
        if (ImageCompressor::GetInstance()->CanCompress()) {
            auto compressData = ImageCompressor::GetInstance()->GpuCompress(src, pixmap, width, height);
            ImageCompressor::GetInstance()->WriteToFile(src, compressData, { width, height });
            if (compressData) {
                // replace skImage of [CanvasImage] with [rasterizedImage]
                skiaCanvasImage->SetCompressData(compressData, width, height);
                skiaCanvasImage->ReplaceSkImage({ nullptr, flutterRenderTaskHolder->unrefQueue });
            } else {
                skiaCanvasImage->ReplaceSkImage({ rasterizedImage, flutterRenderTaskHolder->unrefQueue });
            }
            auto releaseTask = ImageCompressor::GetInstance()->ScheduleReleaseTask();
            if (flutterRenderTaskHolder->ioTaskRunner) {
                flutterRenderTaskHolder->ioTaskRunner->PostDelayedTask(
                    releaseTask, fml::TimeDelta::FromMilliseconds(ImageCompressor::releaseTimeMs));
            } else {
                ImageUtils::PostToBg(std::move(releaseTask));
            }
        }
        callback(skiaCanvasImage);
        // Trigger purge cpu bitmap resource, after image upload to gpu.
        SkGraphics::PurgeResourceCache();
    };
    if (syncLoad) {
        task();
    } else {
        ImageUtils::PostToBg(std::move(task));
    }
#endif
}

void ImageProvider::CacheCanvasImage(const RefPtr<CanvasImage>& canvasImage, const std::string& key)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineCtx);
    CHECK_NULL_VOID(pipelineCtx->GetImageCache());
#ifdef NG_BUILD
    pipelineCtx->GetImageCache()->CacheImage(key, std::make_shared<CachedImage>(canvasImage));
#else
    auto skiaCanvasImage = AceType::DynamicCast<SkiaCanvasImage>(canvasImage);
    CHECK_NULL_VOID_NOLOG(skiaCanvasImage);
    auto cached = std::make_shared<Ace::CachedImage>(skiaCanvasImage->GetFlutterCanvasImage());
    cached->uniqueId = skiaCanvasImage->GetUniqueID();
    pipelineCtx->GetImageCache()->CacheImage(key, cached);
#endif
}

} // namespace OHOS::Ace::NG
