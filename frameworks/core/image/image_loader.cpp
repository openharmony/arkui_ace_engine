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

#include "core/image/image_loader.h"

#include <condition_variable>
#include <mutex>
#include <ratio>
#include <regex>
#include <string_view>

#include "third_party/skia/include/codec/SkCodec.h"
#include "third_party/skia/include/utils/SkBase64.h"

#include "base/image/image_source.h"
#include "base/log/ace_trace.h"
#include "base/network/download_manager.h"
#include "base/resource/ace_res_config.h"
#include "base/resource/asset_manager.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/thread_checker.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/image/flutter_image_cache.h" // TODO: add adapter layer and use FlutterImageCache there
#include "core/image/image_cache.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

constexpr size_t FILE_HEAD_LENGTH = 7;           // 7 is the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9;         // 9 is the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // 15 is the size of "internal://app/"
// regex for "resource://colormode/xxx.type", colormode can be "light" or "dark", xxx represents system resource id,
// type can be "jpg", "png", "svg" and so on.
const std::regex MEDIA_RES_ID_REGEX(R"(^resource://\w+/([0-9]+)\.\w+$)", std::regex::icase);
const std::regex MEDIA_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");
const std::regex MEDIA_APP_RES_ID_REGEX(R"(^resource://.*/([0-9]+)\.\w+$)", std::regex::icase);
const std::regex MEDIA_RES_NAME_REGEX(R"(^resource://.*/(\w+)\.\w+$)", std::regex::icase);
constexpr uint32_t MEDIA_RESOURCE_MATCH_SIZE = 2;

const std::chrono::duration<int, std::milli> TIMEOUT_DURATION(10000);

#ifdef WINDOWS_PLATFORM
char* realpath(const char* path, char* resolved_path)
{
    if (strcpy_s(resolved_path, PATH_MAX, path) != 0) {
        return nullptr;
    }
    return resolved_path;
}
#endif

#ifdef PIXEL_MAP_SUPPORTED
// return orientation of pixmap for cache key
std::string GetThumbnailOrientation(const ImageSourceInfo& src)
{
    // disabling orientation check
    return "Undefined";
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto dataProvider = pipeline->GetDataProviderManager();
    CHECK_NULL_RETURN(dataProvider, "");

    // get file fd
    // concat to get file path ("datashare://media/xx")
    auto path = src.GetSrc();
    auto pos = path.find("/thumbnail");
    path = path.substr(0, pos);
    int32_t fd = dataProvider->GetDataProviderFile(path, "r");
    CHECK_NULL_RETURN(fd >= 0, "");

    // check image orientation
    auto imageSrc = ImageSource::Create(fd);
    CHECK_NULL_RETURN(imageSrc, "");
    std::string orientation = imageSrc->GetProperty("Orientation");
    LOGD("image %{public}s has orientation = %{public}s", path.c_str(), orientation.c_str());
    return orientation;
}
#endif
} // namespace

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        LOGW("No scheme, not a File or Memory path");
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

RefPtr<ImageLoader> ImageLoader::CreateImageLoader(const ImageSourceInfo& imageSourceInfo)
{
    SrcType srcType = imageSourceInfo.GetSrcType();
    switch (srcType) {
        case SrcType::INTERNAL:
        case SrcType::FILE: {
            return MakeRefPtr<FileImageLoader>();
        }
        case SrcType::NETWORK: {
            return MakeRefPtr<NetworkImageLoader>();
        }
        case SrcType::ASSET: {
            return MakeRefPtr<AssetImageLoader>();
        }
        case SrcType::BASE64: {
            return MakeRefPtr<Base64ImageLoader>();
        }
        case SrcType::RESOURCE: {
            return MakeRefPtr<ResourceImageLoader>();
        }
        case SrcType::DATA_ABILITY: {
            return MakeRefPtr<DataProviderImageLoader>();
        }
        case SrcType::DATA_ABILITY_DECODED: {
            return MakeRefPtr<DecodedDataProviderImageLoader>();
        }
        case SrcType::MEMORY: {
            if (Container::IsCurrentUseNewPipeline()) {
                return MakeRefPtr<SharedMemoryImageLoader>();
            }
            LOGE("Image source type: shared memory. image data is not come from image loader.");
            return nullptr;
        }
        case SrcType::RESOURCE_ID: {
            return MakeRefPtr<InternalImageLoader>();
        }
        case SrcType::PIXMAP: {
            return MakeRefPtr<PixelMapImageLoader>();
        }
        default: {
            LOGE("Image source type not supported!  srcType: %{public}d, sourceInfo: %{public}s", srcType,
                imageSourceInfo.ToString().c_str());
            return nullptr;
        }
    }
}

sk_sp<SkData> ImageLoader::LoadDataFromCachedFile(const std::string& uri)
{
    std::string cacheFilePath = ImageCache::GetImageCacheFilePath(uri);
    if (cacheFilePath.length() > PATH_MAX) {
        LOGE("cache file path is too long, cacheFilePath: %{private}s", cacheFilePath.c_str());
        return nullptr;
    }
    bool cacheFileFound = ImageCache::GetFromCacheFile(cacheFilePath);
    if (!cacheFileFound) {
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(cacheFilePath.c_str(), realPath) == nullptr) {
        LOGE("realpath fail! cacheFilePath: %{private}s, fail reason: %{public}s", cacheFilePath.c_str(),
            strerror(errno));
        return nullptr;
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (file) {
        return SkData::MakeFromFILE(file.get());
    }
    return nullptr;
}

sk_sp<SkData> ImageLoader::QueryImageDataFromImageCache(const ImageSourceInfo& sourceInfo)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto imageCache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(imageCache, nullptr);
    auto cacheData = imageCache->GetCacheImageData(sourceInfo.GetSrc());
    CHECK_NULL_RETURN_NOLOG(cacheData, nullptr);
    // TODO: add adapter layer and use [SkiaCachedImageData] there
    auto skiaCachedImageData = AceType::DynamicCast<SkiaCachedImageData>(cacheData);
    CHECK_NULL_RETURN(skiaCachedImageData, nullptr);
    return skiaCachedImageData->imageData;
}

void ImageLoader::CacheImageDataToImageCache(const std::string& key, const RefPtr<CachedImageData>& imageData)
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineCtx);
    auto imageCache = pipelineCtx->GetImageCache();
    CHECK_NULL_VOID(imageCache);
    imageCache->CacheImageData(key, imageData);
}

RefPtr<NG::ImageData> ImageLoader::LoadImageDataFromFileCache(const std::string& key, const std::string& suffix)
{
    ACE_FUNCTION_TRACE();
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto imageCache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(imageCache, nullptr);
    std::string filePath = ImageCache::GetImageCacheFilePath(key) + suffix;
    auto data = imageCache->GetDataFromCacheFile(filePath);
    CHECK_NULL_RETURN_NOLOG(data, nullptr);
    // add adapter layer to replace [SkiaCachedImageData]
    auto skdata = AceType::DynamicCast<SkiaCachedImageData>(data)->imageData;
    CHECK_NULL_RETURN(skdata, nullptr);
    return NG::ImageData::MakeFromDataWrapper(reinterpret_cast<void*>(&skdata));
}

// NG ImageLoader entrance
RefPtr<NG::ImageData> ImageLoader::GetImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    if (imageSourceInfo.IsPixmap()) {
        return LoadDecodedImageData(imageSourceInfo, context);
    }
    sk_sp<SkData> skData;
    do {
        skData = ImageLoader::QueryImageDataFromImageCache(imageSourceInfo);
        if (skData) {
            break;
        }
        skData = LoadImageData(imageSourceInfo, context);
        CHECK_NULL_RETURN(skData, nullptr);
        // TODO: add adapter layer and use [SkiaCachedImageData] there
        ImageLoader::CacheImageDataToImageCache(
            imageSourceInfo.GetSrc(), AceType::MakeRefPtr<SkiaCachedImageData>(skData));
    } while (0);
    return NG::ImageData::MakeFromDataWrapper(reinterpret_cast<void*>(&skData));
}

sk_sp<SkData> FileImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& /* context */)
{
    ACE_SCOPED_TRACE("LoadImageData %s", imageSourceInfo.ToString().c_str());
    const auto& src = imageSourceInfo.GetSrc();
    std::string filePath = RemovePathHead(src);
    if (imageSourceInfo.GetSrcType() == SrcType::INTERNAL) {
        // the internal source uri format is like "internal://app/imagename.png", the absolute path of which is like
        // "/data/data/{bundleName}/files/imagename.png"
        auto bundleName = AceApplicationInfo::GetInstance().GetPackageName();
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
                       .append("/files/")           // infix of absolute path
                       .append(filePath.substr(4)); // 4 is the length of "app/" from "internal://app/"
    }
    if (filePath.length() > PATH_MAX) {
        LOGE("src path is too long");
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(filePath.c_str(), realPath) == nullptr) {
        LOGE("realpath fail! filePath: %{private}s, fail reason: %{public}s src:%{public}s", filePath.c_str(),
            strerror(errno), src.c_str());
        return nullptr;
    }
    auto result = SkData::MakeFromFileName(realPath);
#ifdef PREVIEW
    // on Windows previewer, SkData::MakeFromFile keeps the file open during SkData's lifetime
    // return a copy to release the file handle
    CHECK_NULL_RETURN(result, nullptr);
    return SkData::MakeWithCopy(result->data(), result->size());
#else
    return result;
#endif
}

sk_sp<SkData> DataProviderImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    const auto& src = imageSourceInfo.GetSrc();
    auto skData = ImageLoader::LoadDataFromCachedFile(src);
    if (skData) {
        return skData;
    }
    auto pipeline = context.Upgrade();
    if (!pipeline) {
        LOGE("the pipeline context is null");
        return nullptr;
    }
    auto dataProvider = pipeline->GetDataProviderManager();
    if (!dataProvider) {
        LOGE("the data provider is null");
        return nullptr;
    }
    auto dataRes = dataProvider->GetDataProviderResFromUri(src);
    if (!dataRes || dataRes->GetData().size() == 0) {
        LOGE("fail to get data res is from data provider");
        return nullptr;
    }
    auto imageData = dataRes->GetData();
    sk_sp<SkData> data = SkData::MakeWithCopy(imageData.data(), imageData.size());
    BackgroundTaskExecutor::GetInstance().PostTask(
        [src, imgData = std::move(imageData)]() { ImageCache::WriteCacheFile(src, imgData.data(), imgData.size()); },
        BgTaskPriority::LOW);
    return data;
}

sk_sp<SkData> AssetImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    ACE_FUNCTION_TRACE();
    const auto& src = imageSourceInfo.GetSrc();
    if (src.empty()) {
        LOGE("image src is empty");
        return nullptr;
    }

    std::string assetSrc(src);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGE("invalid pipeline context");
        return nullptr;
    }
    auto assetManager = pipelineContext->GetAssetManager();
    if (!assetManager) {
        LOGE("No asset manager!");
        return nullptr;
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

std::string AssetImageLoader::LoadJsonData(const std::string& src, const WeakPtr<PipelineBase> context)
{
    if (src.empty()) {
        LOGE("image src is empty");
        return "";
    }

    std::string assetSrc(src);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGE("invalid pipeline context");
        return "";
    }
    auto assetManager = pipelineContext->GetAssetManager();
    if (!assetManager) {
        LOGE("No asset manager!");
        return "";
    }
    auto assetData = assetManager->GetAsset(assetSrc);
    if (!assetData || !assetData->GetData()) {
        LOGE("No asset data!");
        return "";
    }
    return std::string((char*)assetData->GetData(), assetData->GetSize());
}

sk_sp<SkData> NetworkImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    auto uri = imageSourceInfo.GetSrc();
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext || pipelineContext->IsJsCard()) {
        LOGW("network image in JS card is forbidden.");
        return nullptr;
    }
    // 1. find in cache file path.
    auto skData = ImageLoader::LoadDataFromCachedFile(uri);
    if (skData) {
        return skData;
    }

    // 2. if not found. download it.
    std::vector<uint8_t> imageData;
    if (!DownloadManager::GetInstance().Download(uri, imageData) || imageData.empty()) {
        LOGE("Download network image %{private}s failed!", uri.c_str());
        return nullptr;
    }
    sk_sp<SkData> data = SkData::MakeWithCopy(imageData.data(), imageData.size());
    // 3. write it into file cache.
    BackgroundTaskExecutor::GetInstance().PostTask(
        [uri, imgData = std::move(imageData)]() { ImageCache::WriteCacheFile(uri, imgData.data(), imgData.size()); },
        BgTaskPriority::LOW);
    return data;
}

sk_sp<SkData> InternalImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    size_t imageSize = 0;
    const uint8_t* internalData =
        InternalResource::GetInstance().GetResource(imageSourceInfo.GetResourceId(), imageSize);
    if (internalData == nullptr) {
        LOGE("data null, the resource id may be wrong.");
        return nullptr;
    }
    return SkData::MakeWithCopy(internalData, imageSize);
}

sk_sp<SkData> Base64ImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    std::string_view base64Code = GetBase64ImageCode(imageSourceInfo.GetSrc());
    if (base64Code.size() == 0) {
        return nullptr;
    }

#ifdef NG_BUILD
    size_t outputLen;
    SkBase64::Error error = SkBase64::Decode(base64Code.data(), base64Code.size(), nullptr, &outputLen);
    if (error != SkBase64::Error::kNoError) {
        LOGE("error base64 image code!");
        return nullptr;
    }

    sk_sp<SkData> resData = SkData::MakeUninitialized(outputLen);
    void* output = resData->writable_data();
    error = SkBase64::Decode(base64Code.data(), base64Code.size(), output, &outputLen);
    if (error != SkBase64::Error::kNoError) {
        LOGE("error base64 image code!");
        return nullptr;
    }
    return resData;
#else
    SkBase64 base64Decoder;
    SkBase64::Error error = base64Decoder.decode(base64Code.data(), base64Code.size());
    if (error != SkBase64::kNoError) {
        LOGE("error base64 image code!");
        return nullptr;
    }
    auto base64Data = base64Decoder.getData();
    const uint8_t* imageData = reinterpret_cast<uint8_t*>(base64Data);
    auto resData = SkData::MakeWithCopy(imageData, base64Decoder.getDataSize());
    // in SkBase64, the fData is not deleted after decoded.
    if (base64Data != nullptr) {
        delete[] base64Data;
        base64Data = nullptr;
    }
    return resData;
#endif
}

std::string_view Base64ImageLoader::GetBase64ImageCode(const std::string& uri)
{
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos || iter == uri.size() - 1) {
        LOGE("wrong code format!");
        return std::string_view();
    }
    // iter + 1 to skip the ","
    std::string_view code(uri.c_str() + (iter + 1));
    return code;
}

bool ResourceImageLoader::GetResourceId(const std::string& uri, uint32_t& resId) const
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MEDIA_RES_ID_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(matches[1].str()));
        return true;
    }

    std::smatch appMatches;
    if (std::regex_match(uri, appMatches, MEDIA_APP_RES_ID_REGEX) && appMatches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(appMatches[1].str()));
        return true;
    }

    return false;
}

bool ResourceImageLoader::GetResourceId(const std::string& uri, std::string& path) const
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MEDIA_APP_RES_PATH_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        path = matches[1].str();
        return true;
    }

    return false;
}

bool ResourceImageLoader::GetResourceName(const std::string& uri, std::string& resName) const
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MEDIA_RES_NAME_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resName = matches[1].str();
        return true;
    }

    return false;
}

sk_sp<SkData> ResourceImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    auto uri = imageSourceInfo.GetSrc();
    auto pipelineContext = context.Upgrade();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);

    std::unique_ptr<uint8_t[]> data;
    size_t dataLen = 0;
    std::string rawFile;
    if (GetResourceId(uri, rawFile)) {
        // must fit raw file firstly, as file name may contains number
        if (!themeConstants->GetRawFileData(rawFile, dataLen, data)) {
            LOGE("get image data by name failed, uri:%{private}s, rawFile:%{public}s", uri.c_str(), rawFile.c_str());
            return nullptr;
        }
        return SkData::MakeWithCopy(data.get(), dataLen);
    }
    uint32_t resId = 0;
    if (GetResourceId(uri, resId)) {
        if (!themeConstants->GetMediaData(resId, dataLen, data)) {
            LOGE("get image data by id failed, uri:%{private}s, id:%{public}u", uri.c_str(), resId);
            return nullptr;
        }
        return SkData::MakeWithCopy(data.get(), dataLen);
    }
    std::string resName;
    if (GetResourceName(uri, resName)) {
        if (!themeConstants->GetMediaData(resName, dataLen, data)) {
            LOGE("get image data by name failed, uri:%{private}s, resName:%{public}s", uri.c_str(), resName.c_str());
            return nullptr;
        }
        return SkData::MakeWithCopy(data.get(), dataLen);
    }
    LOGE("load image data failed, as uri is invalid:%{private}s", uri.c_str());
    return nullptr;
}

sk_sp<SkData> DecodedDataProviderImageLoader::LoadImageData(
    const ImageSourceInfo& /* imageSourceInfo */, const WeakPtr<PipelineBase>& /* context */)
{
    return nullptr;
}

RefPtr<NG::ImageData> DecodedDataProviderImageLoader::LoadDecodedImageData(
    const ImageSourceInfo& src, const WeakPtr<PipelineBase>& pipelineWk)
{
#if !defined(PIXEL_MAP_SUPPORTED)
    return nullptr;
#else
    auto orientation = GetThumbnailOrientation(src);

    // query thumbnail from cache
    auto pipeline = pipelineWk.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto cache = pipeline->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto data = DynamicCast<PixmapCachedData>(cache->GetCacheImageData(src.GetKey() + orientation));
    if (data) {
        LOGD("thumbnail cache found %{public}s, orientation = %{public}s", src.GetSrc().c_str(), orientation.c_str());
        return MakeRefPtr<NG::ImageData>(data->pixmap_);
    }

    auto dataProvider = pipeline->GetDataProviderManager();
    CHECK_NULL_RETURN(dataProvider, nullptr);

    void* pixmapMediaUniquePtr = dataProvider->GetDataProviderThumbnailResFromUri(src.GetSrc());
    auto pixmap = PixelMap::CreatePixelMapFromDataAbility(pixmapMediaUniquePtr);
    CHECK_NULL_RETURN(pixmap, nullptr);
    if (cache) {
        cache->CacheImageData(src.GetKey() + orientation, MakeRefPtr<PixmapCachedData>(pixmap));
    }
    return MakeRefPtr<NG::ImageData>(pixmap);
#endif
}

sk_sp<SkData> PixelMapImageLoader::LoadImageData(
    const ImageSourceInfo& /* imageSourceInfo */, const WeakPtr<PipelineBase>& /* context */)
{
    return nullptr;
}

RefPtr<NG::ImageData> PixelMapImageLoader::LoadDecodedImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
#if !defined(PIXEL_MAP_SUPPORTED)
    return nullptr;
#else
    if (!imageSourceInfo.GetPixmap()) {
        LOGW("no pixel map in imageSourceInfo, imageSourceInfo: %{public}s", imageSourceInfo.ToString().c_str());
        return nullptr;
    }
    return MakeRefPtr<NG::ImageData>(imageSourceInfo.GetPixmap());
#endif
}

sk_sp<SkData> SharedMemoryImageLoader::LoadImageData(
    const ImageSourceInfo& src, const WeakPtr<PipelineBase>& pipelineWk)
{
    CHECK_RUN_ON(BG);
    auto pipeline = pipelineWk.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto manager = pipeline->GetSharedImageManager();
    CHECK_NULL_RETURN(manager, nullptr);
    auto id = RemovePathHead(src.GetSrc());
    bool found = manager->FindImageInSharedImageMap(id, AceType::WeakClaim(this));
    // image data not ready yet, wait for data
    if (!found) {
        manager->RegisterLoader(id, AceType::WeakClaim(this));
        // wait for SharedImageManager to notify
        std::unique_lock<std::mutex> lock(mtx_);
        auto status = cv_.wait_for(lock, TIMEOUT_DURATION);
        if (status == std::cv_status::timeout) {
            return nullptr;
        }
    }

    auto skData = SkData::MakeWithCopy(data_.data(), data_.size());
    return skData;
}

void SharedMemoryImageLoader::UpdateData(const std::string& uri, const std::vector<uint8_t>& memData)
{
    LOGI("SharedMemory image data is ready %{public}s", uri.c_str());
    {
        std::scoped_lock<std::mutex> lock(mtx_);
        data_ = memData;
    }

    cv_.notify_one();
}

} // namespace OHOS::Ace
