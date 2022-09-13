/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <utility>

#include "flutter/fml/memory/ref_counted.h"
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
#include "core/components_ng/render/adapter/skia_canvas_image.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifdef NG_BUILD
#include "core/components_ng/render/adapter/flutter_canvas_image.h"
#endif

namespace OHOS::Ace::NG {
namespace {

struct FlutterRenderTaskHolder : public RenderTaskHolder {
    DECLARE_ACE_TYPE(FlutterRenderTaskHolder, RenderTaskHolder);

public:
    FlutterRenderTaskHolder(fml::RefPtr<flutter::SkiaUnrefQueue> queue, fml::WeakPtr<flutter::IOManager> manager,
        fml::RefPtr<fml::TaskRunner> taskRunner)
        : unrefQueue(queue), ioManager(manager), ioTaskRunner(taskRunner)
    {}
    ~FlutterRenderTaskHolder() override = default;

    fml::RefPtr<flutter::SkiaUnrefQueue> unrefQueue;
    // weak reference of io manager must be check and used on io thread, because io manager is created on io thread.
    fml::WeakPtr<flutter::IOManager> ioManager;
    fml::RefPtr<fml::TaskRunner> ioTaskRunner;
};

static sk_sp<SkImage> ApplySizeToSkImage(
    const sk_sp<SkImage>& rawImage, int32_t dstWidth, int32_t dstHeight, const std::string& srcKey)
{
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
    if (scaledImage) {
        // TODO: cache
        return scaledImage;
    }
    LOGE("Could not create a scaled image from a scaled bitmap. srcKey: %{private}s, destination size: [%{public}d x"
         " %{public}d], raw image size: [%{public}d x %{public}d]",
        srcKey.c_str(), dstWidth, dstHeight, rawImage->width(), rawImage->height());
    return rawImage;
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
    return ApplySizeToSkImage(
        rawImage, dstWidth, dstHeight, ImageObject::GenerateCacheKey(ImageSourceInfo(src), resizeTarget));
}

} // namespace

RefPtr<ImageEncodedInfo> ImageEncodedInfo::CreateImageEncodedInfo(const RefPtr<NG::ImageData>& data)
{
    auto skiaImageData = DynamicCast<SkiaImageData>(data);
    CHECK_NULL_RETURN(skiaImageData, nullptr);
    auto codec = SkCodec::MakeFromData(skiaImageData->GetSkData());
    if (!codec) {
        return nullptr;
    }
    int32_t totalFrames = 1;
    SizeF imageSize;
    totalFrames = codec->getFrameCount();
    switch (codec->getOrigin()) {
        case SkEncodedOrigin::kLeftTop_SkEncodedOrigin:
        case SkEncodedOrigin::kRightTop_SkEncodedOrigin:
        case SkEncodedOrigin::kRightBottom_SkEncodedOrigin:
        case SkEncodedOrigin::kLeftBottom_SkEncodedOrigin:
            imageSize.SetSizeT(SizeF(codec->dimensions().fHeight, codec->dimensions().fWidth));
            break;
        default:
            imageSize.SetSizeT(SizeF(codec->dimensions().fWidth, codec->dimensions().fHeight));
    }
    return MakeRefPtr<ImageEncodedInfo>(imageSize, totalFrames);
}

void ImageProvider::MakeCanvasImage(const WeakPtr<ImageObject>& imageObjWp, const LoadCallbacks& loadCallbacks,
    const SizeF& resizeTarget, const RefPtr<RenderTaskHolder>& renderTaskHolder, bool forceResize)
{
    auto canvasImageMakingTask = [objWp = imageObjWp, loadCallbacks, resizeTarget, renderTaskHolder, forceResize] {
        auto obj = objWp.Upgrade();
        CHECK_NULL_VOID(obj);
        CHECK_NULL_VOID(renderTaskHolder);
        auto flutterRenderTaskHolder = DynamicCast<FlutterRenderTaskHolder>(renderTaskHolder);
        CHECK_NULL_VOID(flutterRenderTaskHolder);
        // TODO: add cache
        // if image object has no skData, reload data.
        std::string errorMessage("");
        if (!obj->GetData()) {
            do {
                auto imageLoader = ImageLoader::CreateImageLoader(obj->GetSourceInfo());
                if (!imageLoader) {
                    LOGE("Fail to create image loader. source info: %{private}s",
                        obj->GetSourceInfo().ToString().c_str());
                    errorMessage = "Image source type is not supported";
                    break;
                }
                auto newLoadedData = imageLoader->GetImageData(
                    obj->GetSourceInfo(), WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));
                if (!newLoadedData) {
                    errorMessage = "Fail to load data, please check if data source is invalid";
                    break;
                }
                obj->SetData(newLoadedData);
            } while (0);
            if (!obj->GetData()) {
                auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo = obj->GetSourceInfo(),
                                              loadCallbacks] {
                    loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::MAKE_CANVAS_IMAGE_FAIL);
                };
                ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
                return;
            }
        }
        // resize image
        auto skiaImageData = DynamicCast<SkiaImageData>(obj->GetData());
        ACE_DCHECK(skiaImageData);
        auto rawImage = SkImage::MakeFromEncoded(skiaImageData->GetSkData());
        if (!rawImage) {
            LOGE(
                "static image MakeFromEncoded fail! source info: %{private}s", obj->GetSourceInfo().ToString().c_str());
            std::string errorMessage("The image format is not supported, please check image format.");
            auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), loadCallbacks,
                                          sourceInfo = obj->GetSourceInfo()] {
                loadCallbacks.loadFailCallback_(sourceInfo, errorMsg, ImageLoadingCommand::MAKE_CANVAS_IMAGE_FAIL);
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
            return;
        }
        // upload to gpu for render
        auto image = ResizeSkImage(rawImage, obj->GetSourceInfo().GetSrc(), resizeTarget, forceResize);
        flutter::SkiaGPUObject<SkImage> skiaGpuObjSkImage({ image, flutterRenderTaskHolder->unrefQueue });
#ifdef NG_BUILD
        auto canvasImage = CanvasImage::Create();
        auto flutterImage = AceType::DynamicCast<NG::FlutterCanvasImage>(canvasImage);
        if (flutterImage) {
            flutterImage->SetImage(std::move(skiaGpuObjSkImage));
        }
#else
        auto flutterCanvasImage = flutter::CanvasImage::Create();
        flutterCanvasImage->set_image(std::move(skiaGpuObjSkImage));
        auto canvasImage = CanvasImage::Create(&flutterCanvasImage);
#endif
        auto uploadTask = [objWp, loadCallbacks](RefPtr<CanvasImage> canvasImage) {
            // when upload success, update canvas image to ImageObject and trigger loadSuccessCallback_
            auto obj = objWp.Upgrade();
            CHECK_NULL_VOID(obj);
            auto notifyLoadSuccessTask = [objWp, loadCallbacks, canvasImage] {
                auto obj = objWp.Upgrade();
                CHECK_NULL_VOID(obj);
                obj->SetCanvasImage(canvasImage);
                loadCallbacks.loadSuccessCallback_(obj->GetSourceInfo());
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadSuccessTask));
        };
        ImageProvider::UploadImageToGPUForRender(canvasImage, std::move(uploadTask), renderTaskHolder);
    };
    // TODO: add sync load
    ImageProvider::WrapTaskAndPostToBackground(std::move(canvasImageMakingTask));
}

RefPtr<RenderTaskHolder> ImageProvider::CreateRenderTaskHolder()
{
    if (!CheckThread(TaskExecutor::TaskType::UI)) {
        LOGE("RenderTaskHolder must be initialized on UI thread, please check.");
        return nullptr;
    }
#ifdef NG_BUILD
    int32_t id = Container::CurrentId();
    auto currentState = flutter::ace::WindowManager::GetWindow(id);
#else
    auto currentState = flutter::UIDartState::Current();
#endif
    CHECK_NULL_RETURN(currentState, nullptr);
    return MakeRefPtr<FlutterRenderTaskHolder>(currentState->GetSkiaUnrefQueue(), currentState->GetIOManager(),
        currentState->GetTaskRunners().GetIOTaskRunner());
}

void ImageProvider::UploadImageToGPUForRender(const RefPtr<CanvasImage>& canvasImage,
    std::function<void(RefPtr<CanvasImage>)>&& callback, const RefPtr<RenderTaskHolder>& renderTaskHolder)
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
    auto skImage = skiaCanvasImage->GetCanvasImage();
    CHECK_NULL_VOID(skImage);
    auto rasterizedImage = skImage->makeRasterImage();
    if (!rasterizedImage) {
        LOGW("Rasterize image failed. callback.");
        callback(skiaCanvasImage);
        return;
    }
    // replace skImage of [CanvasImage] with [rasterizedImage]
    skiaCanvasImage->ReplaceSkImage({ rasterizedImage, flutterRenderTaskHolder->unrefQueue });
    auto task = [rasterizedImage, callback, flutterRenderTaskHolder, skiaCanvasImage, id = Container::CurrentId()] {
        ContainerScope scope(id);
        if (!flutterRenderTaskHolder) {
            LOGW("flutterRenderTaskHolder has been released.");
            return;
        }
        // weak reference of io manager must be check and used on io thread, because io manager is created on io thread.
        if (!flutterRenderTaskHolder->ioManager) {
            // Shell is closing.
            callback(skiaCanvasImage);
            return;
        }
        ACE_DCHECK(!rasterizedImage->isTextureBacked());
        auto resContext = flutterRenderTaskHolder->ioManager->GetResourceContext();
        if (!resContext) {
            callback(skiaCanvasImage);
            return;
        }
        SkPixmap pixmap;
        if (!rasterizedImage->peekPixels(&pixmap)) {
            LOGW("Could not peek pixels of image for texture upload.");
            callback(skiaCanvasImage);
            return;
        }
        auto textureImage =
#ifdef NG_BUILD
            SkImage::MakeCrossContextFromPixmap(resContext.get(), pixmap, true, true);
#else
            SkImage::MakeCrossContextFromPixmap(resContext.get(), pixmap, true, pixmap.colorSpace(), true);
#endif
        if (textureImage) {
            skiaCanvasImage->ReplaceSkImage({ textureImage, flutterRenderTaskHolder->unrefQueue });
        }
        callback(skiaCanvasImage);
        // Trigger purge cpu bitmap resource, after image upload to gpu.
        SkGraphics::PurgeResourceCache();
    };
    ImageProvider::WrapTaskAndPostToBackground(std::move(task));
#endif
}

} // namespace OHOS::Ace::NG