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

#include <regex>

#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/utils/SkBase64.h"

#include "base/network/download_manager.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/string_utils.h"
#include "core/common/ace_engine.h"
#include "core/event/ace_event_helper.h"
#include "core/image/flutter_image_cache.h"

namespace OHOS::Ace {
namespace {

constexpr size_t FILE_HEAD_LENGTH = 7;           // 7 is the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9;         // 9 is the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // 15 is the size of "internal://app/"

#ifdef WINDOWS_PLATFORM
char* realpath(const char* path, char* resolved_path)
{
    if (strcpy_s(resolved_path, PATH_MAX, path) != 0) {
        return nullptr;
    }
    return resolved_path;
}
#endif

} // namespace

std::mutex ImageProvider::loadingImageMutex_;
std::unordered_map<std::string, WeakPtr<ImageProvider>> ImageProvider::loadingImage_;

bool ImageProvider::TrySetLoadingImage(
    const std::string& key,
    const WeakPtr<ImageProvider>& provider)
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

RefPtr<ImageProvider> ImageProvider::Create(const std::string& uri, RefPtr<SharedImageManager> sharedImageManager)
{
    SrcType srcType = ResolveURI(uri);
    switch (srcType) {
        case SrcType::INTERNAL:
        case SrcType::FILE: {
            LOGD("File Image!");
            return MakeRefPtr<FileImageProvider>();
        }
        case SrcType::NETWORK: {
            LOGD("Network Image!");
            return MakeRefPtr<NetworkImageProvider>();
        }
        case SrcType::ASSET: {
            LOGD("Asset Image!");
            return MakeRefPtr<AssetImageProvider>();
        }
        case SrcType::BASE64: {
            LOGD("Base64 Image!");
            return MakeRefPtr<Base64ImageProvider>();
        }
        case SrcType::MEMORY: {
            LOGD("Memory Image!");
            if (!sharedImageManager) {
                LOGE("sharedImageManager is null, uri: %{private}s", uri.c_str());
                return nullptr;
            }
            // check whether the current picName is waiting to be read from shared memory, if found,
            // add to [ProviderMapToReload], and return [memoryImageProvider], waiting for call to load data
            // when image data done added to [SharedImageMap].
            RefPtr<MemoryImageProvider> memoryImageProvider = MakeRefPtr<MemoryImageProvider>();
            RefPtr<ImageProviderLoader> imageLoader = AceType::DynamicCast<ImageProviderLoader>(memoryImageProvider);
            auto nameOfSharedImage = RemovePathHead(uri);
            if (sharedImageManager->AddProviderToReloadMap(nameOfSharedImage, imageLoader)) {
                return memoryImageProvider;
            }
            // this is when current picName is not found in [ProviderMapToReload], indicating that image data of this
            // image may have been written to [SharedImageMap], so return the [MemoryImageProvider] and start loading
            if (sharedImageManager->FindImageInSharedImageMap(nameOfSharedImage, imageLoader)) {
                return memoryImageProvider;
            }
            LOGE("memory image not found in SharedImageMap!, uri is %{private}s", uri.c_str());
            return nullptr;
        }
        default: {
            LOGE("Image source type not supported!");
            return nullptr;
        }
    }
}

SrcType ImageProvider::ResolveURI(const std::string& uri)
{
    if (uri.empty()) {
        return SrcType::OTHER;
    }
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        return SrcType::ASSET;
    }
    std::string head = uri.substr(0, iter);
    std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });
    if (head == "http" or head == "https") {
        return SrcType::NETWORK;
    } else if (head == "file") {
        return SrcType::FILE;
    } else if (head == "internal") {
        return SrcType::INTERNAL;
    } else if (head == "data") {
        static constexpr char BASE64_PATTERN[] = "^data:image/(jpeg|jpg|png|ico|gif|bmp|webp);base64$";
        if (IsValidBase64Head(uri, BASE64_PATTERN)) {
            return SrcType::BASE64;
        }
        return SrcType::OTHER;
    } else if (head == "memory") {
        return SrcType::MEMORY;
    } else {
        return SrcType::OTHER;
    }
}

bool ImageProvider::IsValidBase64Head(const std::string& uri, const std::string& pattern)
{
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos) {
        LOGE("wrong base64 head format.");
        return false;
    }
    std::string base64Head = uri.substr(0, iter);
    std::regex regular(pattern);
    return std::regex_match(base64Head, regular);
}

std::string ImageProvider::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        LOGE("No scheme, not a File or Memory path!");
        return std::string();
    }
    std::string head = uri.substr(0, iter);
    if ((head == "file" && uri.size() > FILE_HEAD_LENGTH) || (head == "memory" && uri.size() > MEMORY_HEAD_LENGTH) ||
        (head == "internal" && uri.size() > INTERNAL_FILE_HEAD_LENGTH)) {
        // the file uri format is like "file:///data/data...",
        // the memory uri format is like "memory://imagename.png" for example,
        // iter + 3 to get the absolutely file path substring : "/data/data..." or the image name: "imagename.png"
        return uri.substr(iter + 3);
    }
    LOGE("Wrong scheme, not a File!");
    return std::string();
}

// if do not override, return null string.
std::string ImageProvider::GenerateKey(const std::string& src, Size targetSize) const
{
    return std::string();
}

void ImageProvider::LoadImage(
    const RefPtr<PipelineContext>& piplineContext,
    const std::string& src,
    Size imageSize)
{
    // set image uri now loading!
    loadingUri_ = src;
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, weak = AceType::WeakClaim(this), piplineContext, imageSize] {
            auto provider = weak.Upgrade();
            if (!provider) {
                return;
            }
            // 1. if some other thread has loading the same url, get it from cache.
            fml::RefPtr<flutter::CanvasImage> cachedFlutterImage;
            auto imageCache = piplineContext->GetImageCache();
            if (imageCache) {
                auto cachedImage = imageCache->GetCacheImage(provider->GenerateKey(src, imageSize));
                if (cachedImage) {
                    cachedFlutterImage = cachedImage->imagePtr;
                }
            }
            if (cachedFlutterImage) {
                LOGD("find the image in cache successful.");
                provider->OnGPUImageReady(cachedFlutterImage);
                if (provider->imageSkData_) {
                    provider->imageSkData_ = nullptr;
                }
                return;
            } else {
                // 2. load from real src.
                provider->LoadFromRealSrc(src, imageSize, piplineContext);
                return;
            }
        });
}

void ImageProvider::GetSVGImageDOMAsync(
    const std::string& src,
    std::function<void(const sk_sp<SkSVGDOM>&)> successCallback,
    std::function<void()> failedCallback,
    RefPtr<TaskExecutor>& taskExecutor,
    const RefPtr<AssetManager> assetManager,
    uint64_t svgThemeColor)
{
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, provider = Claim(this), taskExecutor, assetManager, successCallback, failedCallback, svgThemeColor] {
            auto imageData = provider->LoadImageData(src, assetManager);
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

void ImageProvider::GetImageSize(bool syncMode, const RefPtr<AssetManager> assetManager, const std::string& src)
{
    // set image uri now loading!
    loadingUri_ = src;
    auto task = [src, provider = Claim(this), syncMode, assetManager] {
        provider->imageSkData_ = provider->LoadImageData(src, assetManager);
        if (!provider->imageSkData_) {
            LOGE("GetImageSize call, fetch data failed, src: %{private}s", src.c_str());
            provider->OnImageFailed();
            return;
        }
        auto codec = provider->GetCodec(provider->imageSkData_);
        if (codec) {
            provider->totalFrames_ = codec->getFrameCount();
            Size imageSize(codec->dimensions().fWidth, codec->dimensions().fHeight);
            provider->OnImageSizeReady(imageSize, src, syncMode);
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

void ImageProvider::LoadFromRealSrc(
    const std::string& src,
    Size imageSize,
    const RefPtr<PipelineContext>& piplineContext)
{
    if (!imageSkData_) {
        auto assertManager = piplineContext->GetAssetManager();
        imageSkData_ = LoadImageData(src, assertManager);
        if (!imageSkData_) {
            LOGE("LoadFromRealSrc call, fetch data failed, src: %{private}s", src.c_str());
            ImageProvider::RemoveLoadingImage(GenerateKey(src, imageSize));
            OnImageFailed();
            return;
        }
    }
    ConstructCanvasImageForRender(GenerateKey(src, imageSize), imageSkData_, imageSize);
    imageSkData_ = nullptr;
}

std::unique_ptr<SkCodec> ImageProvider::GetCodec(const sk_sp<SkData>& data)
{
    return SkCodec::MakeFromData(data);
}

void ImageProvider::ConstructCanvasImageForRender(
    const std::string& key,
    const sk_sp<SkData>& data,
    Size imageSize)
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
        OnAnimateImageReady(std::move(codec));
    } else {
        LOGD("Static image! Frame count: %{public}d", totalFrames_);
        ConstructSingleCanvasImage(key, data, imageSize);
    }
}

void ImageProvider::ConstructSingleCanvasImage(
    const std::string& key,
    const sk_sp<SkData>& data,
    Size imageSize)
{
    auto rawImage = SkImage::MakeFromEncoded(data);
    if (!rawImage) {
        LOGE("MakeFromEncoded fail! uri is %{private}s", loadingUri_.c_str());
        ImageProvider::RemoveLoadingImage(key);
        OnImageFailed();
        return;
    }
    auto image = ResizeSkImage(rawImage, imageSize);
    OnImageReady(image, key);
}

sk_sp<SkImage> ImageProvider::ResizeSkImage(const sk_sp<SkImage>& rawImage, Size imageSize)
{
    if (!imageSize.IsValid()) {
        LOGE("not valid size!, imageSize: %{private}s", imageSize.ToString().c_str());
        return rawImage;
    }
    int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + 0.5);
    int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + 0.5);

    bool needResize = false;
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

    if (needResize) {
        const auto scaledImageInfo =
            SkImageInfo::Make(dstWidth, dstHeight, rawImage->colorType(), rawImage->alphaType());
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
        if (!scaledImage) {
            LOGE("Could not create a scaled image from a scaled bitmap.");
            return rawImage;
        }
        return scaledImage;
    } else {
        return rawImage;
    }
}

void ImageProvider::OnImageSizeReady(
    Size rawImageSize,
    const std::string& imageSrc,
    bool syncMode)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadImageSize(rawImageSize, imageSrc, Claim(this), syncMode);
        }
    }
}

void ImageProvider::OnImageReady(const sk_sp<SkImage>& image, const std::string& key)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadSuccess(image, Claim(this), key);
        }
    }
}

void ImageProvider::OnGPUImageReady(const fml::RefPtr<flutter::CanvasImage>& image)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnLoadGPUImageSuccess(image, Claim(this));
        }
    }
}

void ImageProvider::OnAnimateImageReady(std::unique_ptr<SkCodec> codec)
{
    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnAnimateImageSuccess(Claim(this), std::move(codec));
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

sk_sp<SkImage> ImageProvider::GetSkImage(
    const std::string& src,
    const RefPtr<AssetManager> assetManager,
    Size targetSize)
{
    imageSkData_ = LoadImageData(src, assetManager);
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
    auto imageProvider = ImageProvider::Create(src, nullptr);
    if (imageProvider) {
        auto assetManager = context->GetAssetManager();
        BackgroundTaskExecutor::GetInstance().PostTask(
            [src, imageProvider, onSuccess, onFail, assetManager]() {
                auto image = imageProvider->GetSkImage(src, assetManager);
                if (image) {
                    onSuccess();
                    return;
                }
                onFail();
            });
    }
}

std::string FileImageProvider::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> FileImageProvider::LoadImageData(const std::string& src, const RefPtr<AssetManager> assetManager)
{
    LOGD("File Image!");
    bool isInternal = (ResolveURI(src) == SrcType::INTERNAL);
    std::string filePath = RemovePathHead(src);
    if (isInternal) {
        // the internal source uri format is like "internal://app/imagename.png", the absolute path of which is like
        // "/data/data/{bundleName}/files/imagename.png"
        auto bundleName = AceEngine::Get().GetPackageName();
        if (bundleName.empty()) {
            LOGE("bundleName is empty, LoadImageData for internal source fail!");
            return nullptr;
        }
        if (!StringUtils::StartWith(filePath, "app/")) { // "app/" is infix of internal path
            LOGE("internal path format is wrong. path is %{private}s", src.c_str());
            return nullptr;
        }
        filePath = std::string("/data/data/") // head of absolute path
                       .append(bundleName)
                       .append("/files/") // infix of absolute path
                       .append(filePath.substr(4)); // 4 is the length of "app/" from "internal://app/"
    }
    if (filePath.length() > PATH_MAX) {
        LOGE("src path is too long");
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(filePath.c_str(), realPath) == nullptr) {
        LOGE("realpath fail! filePath: %{private}s, fail reason: %{public}s", filePath.c_str(), strerror(errno));
        return nullptr;
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (!file) {
        LOGE("open file failed, filePath: %{private}s, fail reason: %{public}s", filePath.c_str(), strerror(errno));
        return nullptr;
    }
    return SkData::MakeFromFILE(file.get());
}

std::string AssetImageProvider::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> AssetImageProvider::LoadImageData(const std::string& src, const RefPtr<AssetManager> assetManager)
{
    if (src.empty()) {
        return nullptr;
    }
    std::string assetSrc(src);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    auto assetData = assetManager->GetAsset(assetSrc);
    if (!assetData) {
        LOGE("No asset data!");
        return nullptr;
    }
    const uint8_t* data = assetData->GetData();
    const size_t dataSize = assetData->GetSize();
    return SkData::MakeWithCopy(data, dataSize);
}

std::string NetworkImageProvider::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> NetworkImageProvider::LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager)
{
    // 1. find in cache file path.
    LOGD("Network Image!");
    std::string cacheFilePath = ImageCache::GetNetworkImageCacheFilePath(url);
    if (cacheFilePath.length() > PATH_MAX) {
        LOGE("cache file path is too long");
        return nullptr;
    }
    bool cacheFileFound = ImageCache::GetFromCacheFile(cacheFilePath);
    if (cacheFileFound) {
        char realPath[PATH_MAX] = { 0x00 };
        if (realpath(cacheFilePath.c_str(), realPath) == nullptr) {
            LOGE("realpath fail! cacheFilePath: %{private}s, fail reason: %{public}s", cacheFilePath.c_str(),
                strerror(errno));
            return nullptr;
        }
        std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
        if (file) {
            LOGD("find network image in file cache!");
            return SkData::MakeFromFILE(file.get());
        }
    }
    // 2. if not found. download it.
    std::vector<uint8_t> imageData;
    if (!DownloadManager::GetInstance().Download(url, imageData) || imageData.empty()) {
        LOGE("Download image %{private}s failed!", url.c_str());
        return nullptr;
    }
    // 3. write it into file cache.
    ImageCache::WriteCacheFile(url, imageData);
    return SkData::MakeWithCopy(imageData.data(), imageData.size());
}

sk_sp<SkData> MemoryImageProvider::LoadImageData(const std::string& uri, const RefPtr<AssetManager> assetManager)
{
    loadingUri_ = uri;
    return skData_;
}

void MemoryImageProvider::UpdateData(const std::string& uri, const std::vector<uint8_t>& memData)
{
    if (memData.empty()) {
        LOGE("image data is null, uri: %{private}s", uri.c_str());
        skData_ = nullptr;
        return;
    }
    skData_ = SkData::MakeWithCopy(memData.data(), memData.size());

    std::lock_guard<std::mutex> lock(listenersMutex_);
    for (const auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->MarkNeedReload();
        }
    }
    GetImageSize(false, nullptr, uri);
}

std::string MemoryImageProvider::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

std::string InternalImageProvider::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string("InterResource") + std::to_string(static_cast<int32_t>(resourceId_)) +
           std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> InternalImageProvider::LoadImageData(const std::string& uri, const RefPtr<AssetManager> assetManager)
{
    size_t imageSize = 0;
    const uint8_t* internalData = InternalResource::GetInstance().GetResource(resourceId_, imageSize);
    if (internalData == nullptr) {
        LOGE("data null, the resource id may be wrong.");
        return nullptr;
    }
    return SkData::MakeWithCopy(internalData, imageSize);
}

sk_sp<SkData> Base64ImageProvider::LoadImageData(const std::string& url, const RefPtr<AssetManager> assetManager)
{
    SkBase64 base64Decoder;
    size_t imageSize = 0;
    std::string base64Code = GetBase64ImageCode(url, imageSize);
    SkBase64::Error error = base64Decoder.decode(base64Code.c_str(), base64Code.size());
    if (error != SkBase64::kNoError) {
        LOGE("error base64 image code!");
        return nullptr;
    }
    auto base64Data = base64Decoder.getData();
    const uint8_t* imageData = reinterpret_cast<uint8_t*>(base64Data);
    auto resData = SkData::MakeWithCopy(imageData, imageSize);
    // in SkBase64, the fData is not deleted after decoded.
    if (base64Data != nullptr) {
        delete[] base64Data;
        base64Data = nullptr;
    }
    return resData;
}

std::string Base64ImageProvider::GetBase64ImageCode(const std::string& url, size_t& imageSize)
{
    auto iter = url.find_first_of(',');
    if (iter == std::string::npos || iter == url.size() - 1) {
        LOGE("wrong code format!");
        imageSize = 0;
        return std::string();
    }
    // iter + 1 to skip the ","
    std::string code = url.substr(iter + 1);
    imageSize = GetBase64ImageSize(code);
    return code;
}

size_t Base64ImageProvider::GetBase64ImageSize(const std::string& code)
{
    // use base64 code size to calculate image byte size.
    auto iter = code.rbegin();
    int32_t count = 0;
    // skip all '=' in the end.
    while (*iter == '=') {
        count++;
        iter++;
    }
    // get the valid code length.
    size_t codeSize = code.size() - count;
    // compute the image byte size.
    return codeSize - (codeSize / 8) * 2;
}

} // namespace OHOS::Ace