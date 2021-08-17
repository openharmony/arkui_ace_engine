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

#include "third_party/skia/include/core/SkGraphics.h"
#include "third_party/skia/include/core/SkStream.h"

#include "base/thread/background_task_executor.h"
#include "core/event/ace_event_helper.h"
#include "core/image/flutter_image_cache.h"

namespace OHOS::Ace {
namespace {

constexpr double RESIZE_MAX_PROPORTION = 0.5 * 0.5; // Cache image when resize exceeds 25%
RefPtr<ImageProvider> g_imageProvider = nullptr;
// If a picture is a wide color gamut picture, its area value will be larger than this threshold.
constexpr double SRGB_GAMUT_AREA = 0.104149;

} // namespace

std::mutex ImageProvider::loadingImageMutex_;
std::unordered_map<std::string, WeakPtr<ImageProvider>> ImageProvider::loadingImage_;

bool ImageProvider::TrySetLoadingImage(const std::string& key, const WeakPtr<ImageProvider>& provider)
{
    std::lock_guard lock(loadingImageMutex_);
    if (key.empty()) {
        return false;
    }
    auto result = loadingImage_.emplace(key, provider);
    if (result.second) {
        return true;
    }
    auto loadingProvider = loadingImage_[key].Upgrade();
    auto nowProvider = provider.Upgrade();
    if (loadingProvider && nowProvider) {
        if (loadingProvider == nowProvider) {
            return false;
        }
        LOGD("send listeners to some other provider callback");
        std::scoped_lock listenersLock(nowProvider->listenersMutex_, loadingProvider->listenersMutex_);
        for (auto iter = nowProvider->listeners_.begin(); iter != nowProvider->listeners_.end(); iter++) {
            auto listener = iter->Upgrade();
            if (listener) {
                loadingProvider->listeners_.insert(listener);
                listener->OnChangeProvider(loadingProvider);
            }
        }
    }
    return false;
}

void ImageProvider::RemoveLoadingImage(const std::string& key)
{
    std::lock_guard<std::mutex> lock(loadingImageMutex_);
    loadingImage_.erase(key);
}

ImageProvider::ImageProvider(const std::string& uri, RefPtr<SharedImageManager> sharedImageManager)
{
    SrcType srcType = ImageLoader::ResolveURI(uri);
    switch (srcType) {
        case SrcType::INTERNAL:
        case SrcType::FILE: {
            imageLoader_ = MakeRefPtr<FileImageLoader>();
            break;
        }
        case SrcType::NETWORK: {
            imageLoader_ = MakeRefPtr<NetworkImageLoader>();
            break;
        }
        case SrcType::ASSET: {
            imageLoader_ = MakeRefPtr<AssetImageLoader>(false);
            break;
        }
        case SrcType::RESOLUTIONASSETS: {
            imageLoader_ = MakeRefPtr<AssetImageLoader>(true);
            break;
        }
        case SrcType::BASE64: {
            imageLoader_ = MakeRefPtr<Base64ImageLoader>();
            break;
        }
        case SrcType::MEMORY: {
            if (!sharedImageManager) {
                LOGE("sharedImageManager is null, uri: %{private}s", uri.c_str());
                break;
            }
            // check whether the current picName is waiting to be read from shared memory, if found,
            // add to [ProviderMapToReload], and return [memoryImageProvider], waiting for call to load data
            // when image data done added to [SharedImageMap].

            auto imageLoader = MakeRefPtr<MemoryImageLoader>(
                [weakPtr = WeakClaim(this)](const std::string& uri) {
                    auto provider = weakPtr.Upgrade();
                    if (provider) {
                        provider->loadingUri_ = uri;
                    }
                },
                [weakPtr = WeakClaim(this)](const std::string& uri) {
                    auto provider = weakPtr.Upgrade();
                    if (!provider) {
                        return;
                    }
                    std::lock_guard<std::mutex> lock(provider->listenersMutex_);
                    for (const auto& weak : provider->listeners_) {
                        auto listener = weak.Upgrade();
                        if (listener) {
                            listener->MarkNeedReload();
                        }
                    }
                    provider->GetImageSize(false, nullptr, uri);
                });
            imageLoader_ = imageLoader;
            auto nameOfSharedImage = ImageLoader::RemovePathHead(uri);
            if (sharedImageManager->AddProviderToReloadMap(nameOfSharedImage, imageLoader)) {
                break;
            }
            // this is when current picName is not found in [ProviderMapToReload], indicating that image data of this
            // image may have been written to [SharedImageMap], so return the [MemoryImageProvider] and start loading
            if (sharedImageManager->FindImageInSharedImageMap(nameOfSharedImage, imageLoader)) {
                break;
            }
            imageLoader_ = nullptr;
            LOGE("memory image not found in SharedImageMap!, uri is %{private}s", uri.c_str());
            break;
        }
        case SrcType::RESOURCE: {
            imageLoader_ = MakeRefPtr<ResourceImageLoader>();
            break;
        }
        case SrcType::DATA_ABILITY: {
            imageLoader_ = MakeRefPtr<DataProviderImageLoader>();
            break;
        }
        default: {
            LOGE("Image source type not supported!");
            break;
        }
    }
}

ImageProvider::ImageProvider(InternalResource::ResourceId resourceId)
{
    imageLoader_ = MakeRefPtr<InternalImageLoader>(resourceId);
}

void ImageProvider::LoadImage(
    const WeakPtr<PipelineContext> context, const std::string& src, Size imageSize, bool forceResize)
{
    auto currentDartState = flutter::UIDartState::Current();
    if (!currentDartState) {
        return;
    }
    unrefQueue_ = currentDartState->GetSkiaUnrefQueue();
    ioManager_ = currentDartState->GetIOManager();
    ioTaskRunner_ = currentDartState->GetTaskRunners().GetIOTaskRunner();

    // set image uri now loading!
    loadingUri_ = src;
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, weak = AceType::WeakClaim(this), context, imageSize, forceResize] {
        auto provider = weak.Upgrade();
        if (!provider || provider->Invalid()) {
            return;
        }
        auto piplineContext = context.Upgrade();
        if (!piplineContext) {
            return;
        }
        // 1. load from real src.
        provider->LoadFromRealSrc(src, imageSize, piplineContext, nullptr, forceResize);
        return;
    });
}

void ImageProvider::GetSVGImageDOMAsync(const std::string& src,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback, std::function<void()> failedCallback,
    const WeakPtr<PipelineContext> context, uint64_t svgThemeColor)
{
    if (Invalid()) {
        LOGE("image provide invalid");
        return;
    }
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, weakProvider = AceType::WeakClaim(this), context, successCallback, failedCallback, svgThemeColor] {
            auto pipelineContext = context.Upgrade();
            auto provider = weakProvider.Upgrade();
            if (!pipelineContext || !provider) {
                return;
            }
            auto taskExecutor = pipelineContext->GetTaskExecutor();
            if (!taskExecutor) {
                return;
            }
            auto imageData = provider->imageLoader_->LoadImageData(src, pipelineContext);
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
            LOGE("imageData is null! image source is %{private}s", src.c_str());
            taskExecutor->PostTask([failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI);
        });
}

void ImageProvider::GetSVGImageDOMAsyncCustom(const std::string& src,
    std::function<void(const RefPtr<SvgDom>&)> successCallback, std::function<void()> failedCallback,
    const WeakPtr<PipelineContext> context, const std::optional<Color>& svgThemeColor)
{
    if (Invalid()) {
        LOGE("image provide invalid");
        return;
    }
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, weakProvider = AceType::WeakClaim(this), context, successCallback, failedCallback, svgThemeColor] {
            auto pipelineContext = context.Upgrade();
            auto provider = weakProvider.Upgrade();
            if (!pipelineContext || !provider) {
                return;
            }
            auto taskExecutor = pipelineContext->GetTaskExecutor();
            if (!taskExecutor) {
                return;
            }
            auto imageData = provider->imageLoader_->LoadImageData(src, pipelineContext);
            if (imageData) {
                const auto svgStream = std::make_unique<SkMemoryStream>(std::move(imageData));
                if (svgStream) {
                    auto svgDom = SvgDom::CreateSvgDom(*svgStream, pipelineContext, svgThemeColor);
                    if (svgDom) {
                        taskExecutor->PostTask(
                            [successCallback, svgDom] { successCallback(svgDom); }, TaskExecutor::TaskType::UI);
                        return;
                    }
                }
            }
            LOGE("imageData is null! image source is %{private}s", src.c_str());
            taskExecutor->PostTask([failedCallback] { failedCallback(); }, TaskExecutor::TaskType::UI);
        });
}

void ImageProvider::GetImageSize(bool syncMode, const WeakPtr<PipelineContext> context, const std::string& src)
{
    if (Invalid()) {
        LOGE("image provide invalid");
        return;
    }
    // set image uri now loading!
    loadingUri_ = src;
    auto task = [src, weakProvider = AceType::WeakClaim(this), syncMode, context] {
        auto provider = weakProvider.Upgrade();
        if (provider == nullptr) {
            LOGE("GetImageSize::provider is null!");
            return;
        }
        std::lock_guard<std::mutex> imageSkDataLock(provider->imageSkDataMutex_);
        provider->imageSkData_ = provider->imageLoader_->LoadImageData(src, context);
        if (!provider->imageSkData_) {
            LOGE("GetImageSize call, fetch data failed, src: %{private}s", src.c_str());
            provider->OnImageFailed();
            return;
        }
        auto codec = provider->GetCodec(provider->imageSkData_);
        if (codec) {
            auto resizedImageSize = provider->imageLoader_->CalculateOriImageMatchedResolutionSize(src,
                codec->dimensions().fHeight, codec->dimensions().fWidth);
            provider->totalFrames_ = codec->getFrameCount();
            Size imageSize(codec->dimensions().fWidth, codec->dimensions().fHeight);
            if (!resizedImageSize.IsEmpty()) {
                provider->currentResolutionTargetSize_ = resizedImageSize;
                provider->OnImageSizeReady(resizedImageSize, src, syncMode);
            } else {
                provider->currentResolutionTargetSize_ = Size(0.0, 0.0);
                provider->OnImageSizeReady(imageSize, src, syncMode);
            }
        } else {
            LOGE("decode image failed, src: %{private}s", src.c_str());
            provider->OnImageFailed();
        }
    };

    if (syncMode) {
        task();
    } else {
        BackgroundTaskExecutor::GetInstance().PostTask(task);
    }
}

void ImageProvider::UploadToGPUForRender(
    const sk_sp<SkImage>& image, const std::function<void(flutter::SkiaGPUObject<SkImage>)>& callback)
{
    // If want to dump draw command, should use CPU image.
    callback({ image, unrefQueue_ });
}

void ImageProvider::LoadFromRealSrc(const std::string& src, Size imageSize,
    const WeakPtr<PipelineContext> context, const RefPtr<ImageLoader> imageLoader, bool forceResize)
{
    auto loader = imageLoader ? imageLoader : imageLoader_;
    if (!imageSkData_ && loader) {
        imageSkData_ = loader->LoadImageData(src, context);
        if (!imageSkData_) {
            LOGE("LoadFromRealSrc call, fetch data failed, src: %{private}s", src.c_str());
            ImageProvider::RemoveLoadingImage(loader->GenerateKey(src, imageSize));
            OnImageFailed();
            return;
        }
    }
    ConstructCanvasImageForRender(loader->GenerateKey(src, imageSize), std::move(imageSkData_), imageSize, forceResize);
    imageSkData_ = nullptr;
}

std::unique_ptr<SkCodec> ImageProvider::GetCodec(const sk_sp<SkData>& data)
{
    return SkCodec::MakeFromData(data);
}

void ImageProvider::ConstructCanvasImageForRender(
    const std::string& key, sk_sp<SkData> data, Size imageSize, bool forceResize)
{
    auto codec = GetCodec(data);
    if (!codec) {
        LOGE("Decode the image failed! Missing codec.");
        ImageProvider::RemoveLoadingImage(key);
        OnImageFailed();
        return;
    }
    totalFrames_ = codec->getFrameCount();
    if (totalFrames_ > 1) {
        LOGD("Animate image! Frame count: %{public}d", totalFrames_);
        ImageProvider::RemoveLoadingImage(key);
        OnAnimateImageReady(std::move(codec), forceResize);
    } else {
        LOGD("Static image! Frame count: %{public}d", totalFrames_);
        ConstructSingleCanvasImage(key, data, imageSize, forceResize);
    }
}

void ImageProvider::ConstructSingleCanvasImage(
    const std::string& key, const sk_sp<SkData>& data, Size imageSize, bool forceResize)
{
    auto rawImage = SkImage::MakeFromEncoded(data);
    if (!rawImage) {
        LOGE("MakeFromEncoded fail! uri is %{private}s", loadingUri_.c_str());
        ImageProvider::RemoveLoadingImage(key);
        OnImageFailed();
        return;
    }

    auto image = ResizeSkImage(rawImage, imageSize, forceResize);

    auto callback = [provider = Claim(this), key](flutter::SkiaGPUObject<SkImage> image) {
        auto canvasImage = flutter::CanvasImage::Create();
        canvasImage->set_image(std::move(image));
        ImageProvider::RemoveLoadingImage(key);
        provider->OnImageReady(canvasImage);
    };
    UploadToGPUForRender(image, callback);

    if (needCacheResizedImage && imageLoader_) {
        imageLoader_->CacheResizedImage(image, key);
    }
    if (ioTaskRunner_) {
        ioTaskRunner_->PostTask([]() { SkGraphics::PurgeResourceCache(); });
    }
}

sk_sp<SkImage> ImageProvider::ResizeSkImage(const sk_sp<SkImage>& rawImage, Size imageSize, bool forceResize)
{
    if (!imageSize.IsValid()) {
        LOGE("not valid size!, imageSize: %{private}s", imageSize.ToString().c_str());
        return rawImage;
    }
    int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + 0.5);
    int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + 0.5);

    bool needResize = false;

    if (!forceResize) {
        if (currentResolutionTargetSize_.IsEmpty()) {
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
        } else {
            if ((currentResolutionTargetSize_.Width() != dstWidth) ||
                (currentResolutionTargetSize_.Height() != dstHeight) ||
                (rawImage->width() != dstWidth) || (rawImage->height() != dstHeight)) {
                needResize = true;
            }
        }
    }

    if (!needResize && !forceResize) {
        return rawImage;
    }

    if (1.0 * dstWidth * dstHeight / (rawImage->width() * rawImage->height()) < RESIZE_MAX_PROPORTION) {
        needCacheResizedImage = true;
    }
    if (!currentResolutionTargetSize_.IsEmpty() &&
        (1.0 * dstWidth * dstHeight) / (rawImage->width() * rawImage->height()) > (1 + RESIZE_MAX_PROPORTION)) {
            needCacheResizedImage = true;
    }
    return ApplySizeToSkImage(rawImage, dstWidth, dstHeight);
}

sk_sp<SkImage> ImageProvider::ApplySizeToSkImage(const sk_sp<SkImage>& rawImage, int32_t dstWidth, int32_t dstHeight)
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
        return scaledImage;
    }
    LOGE("Could not create a scaled image from a scaled bitmap.");
    return rawImage;
}

void ImageProvider::OnImageSizeReady(Size rawImageSize, const std::string& imageSrc, bool syncMode)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadImageSize(rawImageSize, imageSrc, Claim(this), syncMode);
        }
    }
}

void ImageProvider::OnImageReady(const fml::RefPtr<flutter::CanvasImage>& image)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadSuccess(image, Claim(this));
        }
    }
}

void ImageProvider::OnAnimateImageReady(std::unique_ptr<SkCodec> codec, bool forceResize)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnAnimateImageSuccess(Claim(this), std::move(codec), forceResize);
        }
    }
}

void ImageProvider::OnImageFailed()
{
    LOGE("Image Load Failed!");
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadFail(Claim(this));
        }
    }
}

void ImageProvider::AddListener(const WeakPtr<LoadImageCallback>& listener)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    listeners_.insert(listener);
}

void ImageProvider::RemoveListener(const WeakPtr<LoadImageCallback>& listener)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    listeners_.erase(listener);
}

int32_t ImageProvider::GetTotalFrames() const
{
    return totalFrames_;
}

sk_sp<SkImage> ImageProvider::GetSkImage(const std::string& src, const WeakPtr<PipelineContext> context,
    Size targetSize)
{
    if (Invalid()) {
        LOGE("image provide invalid");
        return nullptr;
    }

    imageSkData_ = imageLoader_->LoadImageData(src, context);
    if (!imageSkData_) {
        LOGE("fetch data failed");
        return nullptr;
    }
    auto rawImage = SkImage::MakeFromEncoded(imageSkData_);
    if (!rawImage) {
        LOGE("MakeFromEncoded failed!");
        return nullptr;
    }
    auto image = ResizeSkImage(rawImage, targetSize);
    return image;
}

void RenderImageProvider::CanLoadImage(
    const RefPtr<PipelineContext>& context, const std::string& src, const std::map<std::string, EventMarker>& callbacks)
{
    if (callbacks.find("success") == callbacks.end() || callbacks.find("fail") == callbacks.end()) {
        return;
    }
    auto onSuccess = AceAsyncEvent<void()>::Create(callbacks.at("success"), context);
    auto onFail = AceAsyncEvent<void()>::Create(callbacks.at("fail"), context);
    g_imageProvider = AceType::MakeRefPtr<ImageProvider>(src, nullptr);
    if (!g_imageProvider->Invalid()) {
        auto weakProvider = AceType::WeakClaim(AceType::RawPtr(g_imageProvider));
        BackgroundTaskExecutor::GetInstance().PostTask([src, weakProvider, onSuccess, onFail, context]() {
            auto imageProvider = weakProvider.Upgrade();
            if (imageProvider == nullptr) {
                LOGE("CanLoadImage::imageProvider is null!");
                return;
            }
            auto image = imageProvider->GetSkImage(src, context);
            if (image) {
                onSuccess();
                return;
            }
            onFail();
        });
    }
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
