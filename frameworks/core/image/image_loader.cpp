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

#include "core/image/image_loader.h"

#include <regex>

#include "third_party/skia/include/codec/SkCodec.h"
#include "third_party/skia/include/utils/SkBase64.h"

#include "base/network/download_manager.h"
#include "base/resource/asset_manager.h"
#include "base/utils/string_utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace {
namespace {

constexpr size_t FILE_HEAD_LENGTH = 7;           // 7 is the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9;         // 9 is the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // 15 is the size of "internal://app/"
constexpr size_t RESOLUTION_ASSETS_HEAD_LENGTH = 9; // 15 is the size of "assets://"
// regex for "resource://colormode/xxx.type", colormode can be "light" or "dark", xxx represents system resource id,
// type can be "jpg", "png", "svg" and so on.
const std::regex MEDIA_RES_ID_REGEX(R"(^resource://\w+/([0-9]+)\.\w+$)", std::regex::icase);
constexpr uint32_t MEDIA_RESOURCE_MATCH_SIZE = 2;

#ifdef WINDOWS_PLATFORM
char* realpath(const char* path, char* resolved_path)
{
    if (strcpy_s(resolved_path, PATH_MAX, path) != 0) {
        return nullptr;
    }
    return resolved_path;
}
#endif

bool IsValidBase64Head(const std::string& uri, const std::string& pattern)
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

} // namespace

void ImageLoader::CacheResizedImage(const sk_sp<SkImage>& image, const std::string& key)
{
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    auto data = image->encodeToData(SkEncodedImageFormat::kPNG, 100);
    if (data) {
        ImageCache::WriteCacheFile(key, data->data(), data->size());
    }
#endif
}

Size ImageLoader::CalculateOriImageMatchedResolutionSize(const std::string& src, double oriHeight, double oriwidth)
{
    return Size(0.0, 0.0);
}

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        LOGW("No scheme, not a File or Memory path! The path is %{private}s", uri.c_str());
        return std::string();
    }
    std::string head = uri.substr(0, iter);
    if ((head == "file" && uri.size() > FILE_HEAD_LENGTH) || (head == "memory" && uri.size() > MEMORY_HEAD_LENGTH) ||
        (head == "internal" && uri.size() > INTERNAL_FILE_HEAD_LENGTH) ||
        (head == "assets" && uri.size() > RESOLUTION_ASSETS_HEAD_LENGTH)) {
        // the file uri format is like "file:///data/data...",
        // the memory uri format is like "memory://imagename.png" for example,
        // iter + 3 to get the absolutely file path substring : "/data/data..." or the image name: "imagename.png"
        // the resolution assets uri format is like "assets:///resources/..." for example,
        return uri.substr(iter + 3);
    }
    LOGE("Wrong scheme, not a File!");
    return std::string();
}

SrcType ImageLoader::ResolveURI(const std::string& uri)
{
    if (uri.empty()) {
        return SrcType::UNSUPPORTED;
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
        return SrcType::UNSUPPORTED;
    } else if (head == "memory") {
        return SrcType::MEMORY;
    } else if (head == "assets") {
        return SrcType::RESOLUTIONASSETS;
    } else if (head == "resource") {
        return SrcType::RESOURCE;
    } else if (head == "dataability") {
        return SrcType::DATA_ABILITY;
    } else {
        return SrcType::UNSUPPORTED;
    }
}

std::string FileImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> FileImageLoader::LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context)
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
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (!file) {
        LOGE("open file failed, filePath: %{private}s, fail reason: %{public}s", filePath.c_str(), strerror(errno));
        return nullptr;
    }
    return SkData::MakeFromFILE(file.get());
}

std::string DataProviderImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
        std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> DataProviderImageLoader::LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context)
{
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
    return SkData::MakeWithCopy(dataRes->GetData().data(), dataRes->GetData().size());
}

std::string AssetImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> AssetImageLoader::LoadImageData(const std::string& src, const WeakPtr<PipelineContext> context)
{
    if (src.empty()) {
        LOGE("image src is empty");
        return nullptr;
    }

    std::string assetSrc;
    if (needResizeSrcImage_) {
        assetSrc = RemovePathHead(src);
    } else {
        assetSrc = src;
    }
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

Size AssetImageLoader::CalculateOriImageMatchedResolutionSize(const std::string& assetSrc, double oriHeight,
    double oriwidth)
{
    if (!needResizeSrcImage_) {
        return Size(0.0, 0.0);
    }

    std::string src;
    if (needResizeSrcImage_) {
        src = RemovePathHead(assetSrc);
    } else {
        src = assetSrc;
    }

    if (src[0] == '/') {
        src = src.substr(1);
    }

    std::regex declarativeImageSrcPartten(
        "^resources\\/.*\\/media\\/\\w*(\\.jpg|\\.png|\\.webp|\\.bmp)$");
    std::smatch result;
    if (std::regex_match(src, result, declarativeImageSrcPartten)) {
        auto startPos = src.find_first_of("/");
        auto endPos = src.find_first_of("/", startPos + 1);
        if ((startPos != std::string::npos) && (endPos != std::string::npos)) {
            auto srcResTag = src.substr(startPos + 1, endPos - startPos - 1);
            auto ratio = AceApplicationInfo::GetInstance().GetTargetMediaScaleRatio(srcResTag);
            auto targetWidth = oriwidth * ratio;
            auto targetHeight = oriHeight * ratio;
            return Size(targetWidth, targetHeight);
        }
    }

    return Size(0.0, 0.0);
}

std::string NetworkImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> NetworkImageLoader::LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context)
{
    // 1. find in cache file path.
    LOGD("Network Image!");
    std::string cacheFilePath = ImageCache::GetNetworkImageCacheFilePath(uri);
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
    if (!DownloadManager::GetInstance().Download(uri, imageData) || imageData.empty()) {
        LOGE("Download image %{private}s failed!", uri.c_str());
        return nullptr;
    }
    // 3. write it into file cache.
    ImageCache::WriteCacheFile(uri, imageData.data(), imageData.size());
    return SkData::MakeWithCopy(imageData.data(), imageData.size());
}

sk_sp<SkData> MemoryImageLoader::LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context)
{
    if (uriUpdatedCallback_) {
        uriUpdatedCallback_(uri);
    }
    return skData_;
}

void MemoryImageLoader::UpdateData(const std::string& uri, const std::vector<uint8_t>& memData)
{
    if (memData.empty()) {
        LOGE("image data is null, uri: %{private}s", uri.c_str());
        skData_ = nullptr;
        return;
    }
    skData_ = SkData::MakeWithCopy(memData.data(), memData.size());
    if (imageDataUpdatedCallback_) {
        imageDataUpdatedCallback_(uri);
    }
}

std::string MemoryImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

std::string InternalImageLoader::GenerateKey(const std::string& src, Size targetImageSize) const
{
    return std::string("InterResource") + std::to_string(static_cast<int32_t>(resourceId_)) +
           std::to_string(static_cast<int32_t>(targetImageSize.Width())) +
           std::to_string(static_cast<int32_t>(targetImageSize.Height()));
}

sk_sp<SkData> InternalImageLoader::LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context)
{
    size_t imageSize = 0;
    const uint8_t* internalData = InternalResource::GetInstance().GetResource(resourceId_, imageSize);
    if (internalData == nullptr) {
        LOGE("data null, the resource id may be wrong.");
        return nullptr;
    }
    return SkData::MakeWithCopy(internalData, imageSize);
}

sk_sp<SkData> Base64ImageLoader::LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context)
{
    SkBase64 base64Decoder;
    size_t imageSize = 0;
    std::string base64Code = GetBase64ImageCode(uri, imageSize);
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

std::string Base64ImageLoader::GetBase64ImageCode(const std::string& uri, size_t& imageSize)
{
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos || iter == uri.size() - 1) {
        LOGE("wrong code format!");
        imageSize = 0;
        return std::string();
    }
    // iter + 1 to skip the ","
    std::string code = uri.substr(iter + 1);
    imageSize = GetBase64ImageSize(code);
    return code;
}

size_t Base64ImageLoader::GetBase64ImageSize(const std::string& code)
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

bool ResourceImageLoader::GetResourceId(const std::string& uri, const RefPtr<ThemeConstants>& themeContants,
    uint32_t& resId) const
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MEDIA_RES_ID_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(matches[1].str()));
        return true;
    }
    return false;
}

sk_sp<SkData> ResourceImageLoader::LoadImageData(const std::string& uri, const WeakPtr<PipelineContext> context)
{
    uint32_t resId = 0;
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGE("invalid pipeline context");
        return nullptr;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        LOGE("get theme manager failed");
        return nullptr;
    }
    auto themeContants = themeManager->GetThemeConstants();
    if (!themeContants) {
        LOGE("get theme constants failed");
        return nullptr;
    }
    if (!GetResourceId(uri, themeContants, resId)) {
        LOGE("get image resource id failed");
        return nullptr;
    }
    std::ostringstream osstream;
    auto ret = themeContants->GetMediaResource(resId, osstream);
    if (!ret) {
        LOGE("get image(%{public}s) from resource manager failed", uri.c_str());
        return nullptr;
    }
    const auto& mediaRes = osstream.str();
    return SkData::MakeWithCopy(mediaRes.c_str(), mediaRes.size());
}

std::string ResourceImageLoader::GenerateKey(const std::string& src, Size targetSize) const
{
    return std::string(src) + std::to_string(static_cast<int32_t>(targetSize.Width())) +
           std::to_string(static_cast<int32_t>(targetSize.Height()));
}

} // namespace OHOS::Ace