/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#include "include/utils/SkBase64.h"

#include "base/image/file_uri_helper.h"
#include "base/image/image_source.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/resource_configuration.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/resource/resource_configuration.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components_ng/image_provider/adapter/drawing_image_data.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/image/image_file_cache.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
struct SkDataWrapper {
    sk_sp<SkData> data;
};

inline void SkDataWrapperReleaseProc(const void* /* pixels */, void* context)
{
    SkDataWrapper* wrapper = reinterpret_cast<SkDataWrapper*>(context);
    delete wrapper;
}

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
} // namespace

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "No scheme, not a File or Memory path");
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
    TAG_LOGW(AceLogTag::ACE_IMAGE, "Wrong scheme, not a File!");
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
            return MakeRefPtr<SharedMemoryImageLoader>();
        }
        case SrcType::RESOURCE_ID: {
            return MakeRefPtr<InternalImageLoader>();
        }
        case SrcType::PIXMAP: {
            return MakeRefPtr<PixelMapImageLoader>();
        }
        case SrcType::ASTC: {
            return MakeRefPtr<AstcImageLoader>();
        }
        default: {
            return nullptr;
        }
    }
}

std::shared_ptr<RSData> ImageLoader::LoadDataFromCachedFile(const std::string& uri)
{
    std::string cacheFilePath = ImageFileCache::GetInstance().GetImageCacheFilePath(uri);
    if (cacheFilePath.length() > PATH_MAX) {
        TAG_LOGW(
            AceLogTag::ACE_IMAGE, "cache file path is too long, cacheFilePath: %{private}s", cacheFilePath.c_str());
        return nullptr;
    }
    cacheFilePath = ImageFileCache::GetInstance().GetCacheFilePath(uri);
    if (cacheFilePath == "") {
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(cacheFilePath.c_str(), realPath) == nullptr) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "realpath fail! cacheFilePath: %{private}s, fail reason: %{public}s",
            cacheFilePath.c_str(), strerror(errno));
        return nullptr;
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (file) {
        auto skData = SkData::MakeFromFILE(file.get());
        CHECK_NULL_RETURN(skData, nullptr);
        auto rsData = std::make_shared<RSData>();
        SkDataWrapper* wrapper = new SkDataWrapper { std::move(skData) };
        rsData->BuildWithProc(wrapper->data->data(), wrapper->data->size(), SkDataWrapperReleaseProc, wrapper);
        return rsData;
    }
    return nullptr;
}

std::shared_ptr<RSData> ImageLoader::QueryImageDataFromImageCache(const ImageSourceInfo& sourceInfo)
{
    ACE_LAYOUT_SCOPED_TRACE("QueryImageDataFromImageCache[%s]", sourceInfo.ToString().c_str());
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineCtx, nullptr);
    auto imageCache = pipelineCtx->GetImageCache();
    CHECK_NULL_RETURN(imageCache, nullptr);
    auto cacheData = imageCache->GetCacheImageData(sourceInfo.GetKey());
    CHECK_NULL_RETURN(cacheData, nullptr);
    auto rosenCachedImageData = AceType::DynamicCast<NG::DrawingImageData>(cacheData);
    CHECK_NULL_RETURN(rosenCachedImageData, nullptr);
    return rosenCachedImageData->GetRSData();
}

void ImageLoader::CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& imageData)
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
    return ImageFileCache::GetInstance().GetDataFromCacheFile(key, suffix);
}

// NG ImageLoader entrance
RefPtr<NG::ImageData> ImageLoader::GetImageData(
    const ImageSourceInfo& src, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    ACE_SCOPED_TRACE("GetImageData %s", src.ToString().c_str());
    if (src.IsPixmap()) {
        return LoadDecodedImageData(src, errorInfo, context);
    }
    std::shared_ptr<RSData> rsData = nullptr;
    do {
        rsData = ImageLoader::QueryImageDataFromImageCache(src);
        if (rsData) {
            break;
        }
        rsData = LoadImageData(src, errorInfo, context);
        CHECK_NULL_RETURN(rsData, nullptr);
        ImageLoader::CacheImageData(src.GetKey(), AceType::MakeRefPtr<NG::DrawingImageData>(rsData));
    } while (false);
    return AceType::MakeRefPtr<NG::DrawingImageData>(rsData);
}

// NG ImageLoader entrance
bool NetworkImageLoader::DownloadImage(DownloadCallback&& downloadCallback, const std::string& src, bool sync)
{
    return sync ? DownloadManager::GetInstance()->DownloadSyncWithPreload(
                      std::move(downloadCallback), src, Container::CurrentId())
                : DownloadManager::GetInstance()->DownloadAsyncWithPreload(
                      std::move(downloadCallback), src, Container::CurrentId());
}

std::shared_ptr<RSData> FileImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& /* context */)
{
    const auto& src = imageSourceInfo.GetSrc();
    std::string filePath = RemovePathHead(src);
    auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
    ACE_SCOPED_TRACE("LoadImageData %s", imageDfxConfig.ToStringWithSrc().c_str());
    if (imageSourceInfo.GetSrcType() == SrcType::INTERNAL) {
        // the internal source uri format is like "internal://app/imagename.png", the absolute path of which is like
        // "/data/data/{bundleName}/files/imagename.png"
        auto bundleName = AceApplicationInfo::GetInstance().GetPackageName();
        if (bundleName.empty()) {
            TAG_LOGW(AceLogTag::ACE_IMAGE,
                "bundleName is empty, LoadImageData for internal source fail! %{private}s-%{public}s.",
                imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
            return nullptr;
        }
        if (!StringUtils::StartWith(filePath, "app/")) { // "app/" is infix of internal path
            TAG_LOGW(AceLogTag::ACE_IMAGE, "internal path format is wrong. path is %{private}s-%{public}s.",
                src.c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
            return nullptr;
        }
        filePath = std::string("/data/data/") // head of absolute path
                       .append(bundleName)
                       .append("/files/")           // infix of absolute path
                       .append(filePath.substr(4)); // 4 is the length of "app/" from "internal://app/"
    } else if (imageSourceInfo.GetSrcType() == SrcType::FILE) {
        filePath = FileUriHelper::GetRealPath(src);
    }
    if (filePath.length() > PATH_MAX) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "path is too long. %{public}s.", imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_FILE_PATH_TOO_LONG, "path is too long." };
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    realpath(filePath.c_str(), realPath);
    auto result = SkData::MakeFromFileName(realPath);
    if (!result) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "read data failed, filePath: %{private}s, realPath: %{private}s, "
            "src: %{private}s, fail reason: %{private}s.%{public}s.",
            filePath.c_str(), src.c_str(), realPath, strerror(errno), imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_FILE_READ_DATA_FAILED, "read data failed." };
        return nullptr;
    }
    auto rsData = std::make_shared<RSData>();
#ifdef PREVIEW
    // on Windows previewer, SkData::MakeFromFile keeps the file open during Drawing::Data's lifetime
    // return a copy to release the file handle
    return rsData->BuildWithCopy(result->data(), result->size()) ? rsData : nullptr;
#else
    SkDataWrapper* wrapper = new SkDataWrapper { std::move(result) };
    return rsData->BuildWithProc(wrapper->data->data(), wrapper->data->size(), SkDataWrapperReleaseProc, wrapper)
               ? rsData
               : nullptr;
#endif
}

std::shared_ptr<RSData> DataProviderImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    const auto& src = imageSourceInfo.GetSrc();
    auto drawingData = ImageLoader::LoadDataFromCachedFile(src);
    if (drawingData) {
        return drawingData;
    }
    auto pipeline = context.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dataProvider = pipeline->GetDataProviderManager();
    CHECK_NULL_RETURN(dataProvider, nullptr);
    auto res = dataProvider->GetDataProviderResFromUri(src, errorInfo);
    CHECK_NULL_RETURN(res, nullptr);
    // function is ok, just pointer cast from SKData to RSData
    auto skData = SkData::MakeFromMalloc(res->GetData().release(), res->GetSize());
    CHECK_NULL_RETURN(skData, nullptr);
    auto data = std::make_shared<RSData>();
    SkDataWrapper* wrapper = new SkDataWrapper { std::move(skData) };
    data->BuildWithProc(wrapper->data->data(), wrapper->data->size(), SkDataWrapperReleaseProc, wrapper);
    return data;
}

std::shared_ptr<RSData> AssetImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    ACE_FUNCTION_TRACE();
    const auto& src = imageSourceInfo.GetSrc();
    auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
    if (src.empty()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "image src is empty. %{public}s.", imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_ASSET_URI_INVALID, "uri is invalid." };
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
        TAG_LOGW(
            AceLogTag::ACE_IMAGE, "invalid pipeline context. %{public}s", imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto assetManager = pipelineContext->GetAssetManager();
    if (!assetManager) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "NoAssetManager! %{public}s", imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto assetData = assetManager->GetAsset(assetSrc);
    if (!assetData) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "NoAssetData-%{public}s", imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_ASSET_GET_FAILED, "get asset failed." };
        return nullptr;
    }
    const uint8_t* data = assetData->GetData();
    const size_t dataSize = assetData->GetSize();
    auto drawingData = std::make_shared<RSData>();
    drawingData->BuildWithCopy(data, dataSize);
    return drawingData;
}

std::string AssetImageLoader::LoadJsonData(const std::string& src, const WeakPtr<PipelineBase> context)
{
    if (src.empty()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "image src is empty");
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
        return "";
    }
    auto assetManager = pipelineContext->GetAssetManager();
    if (!assetManager) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "No asset manager!");
        return "";
    }
    auto assetData = assetManager->GetAsset(assetSrc);
    if (!assetData || !assetData->GetData()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "No asset data!");
        return "";
    }
    return std::string((char*)assetData->GetData(), assetData->GetSize());
}

std::shared_ptr<RSData> NetworkImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    auto uri = imageSourceInfo.GetSrc();
    auto pipelineContext = context.Upgrade();
    auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
    if (!pipelineContext || pipelineContext->IsJsCard()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "network image in JS card is forbidden. %{public}s",
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    // 1. find in cache file path.
    auto drawingData = ImageLoader::LoadDataFromCachedFile(uri);
    if (drawingData) {
        return drawingData;
    }

    // 2. if not found. download it.
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "Download network image by loader, uri=%{private}s, %{public}s", uri.c_str(),
            imageDfxConfig.ToStringWithoutSrc().c_str());
    }

#ifndef OHOS_PLATFORM
    std::vector<uint8_t> imageData;
    if (!DownloadManager::GetInstance()->Download(uri, imageData) || imageData.empty()) {
        return nullptr;
    }
    auto data = std::make_shared<RSData>();
    data->BuildWithCopy(imageData.data(), imageData.size());
    WriteCacheToFile(uri, imageData);
#else
    auto downloadResult = std::make_shared<DownloadResult>();
    if (!DownloadManager::GetInstance()->Download(uri, downloadResult)) {
        return nullptr;
    }
    auto data = std::make_shared<RSData>();
    data->BuildWithCopy(downloadResult->dataOut.data(), downloadResult->dataOut.size());
    WriteCacheToFile(uri, downloadResult->dataOut);
#endif
    return data;
}

std::shared_ptr<RSData> InternalImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    size_t imageSize = 0;
    const uint8_t* internalData =
        InternalResource::GetInstance().GetResource(imageSourceInfo.GetResourceId(), imageSize);
    if (internalData == nullptr) {
        auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Resource is invalid, %{public}s", imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto drawingData = std::make_shared<RSData>();
    drawingData->BuildWithCopy(internalData, imageSize);
    return drawingData;
}

std::shared_ptr<RSData> Base64ImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    std::string_view base64Code = GetBase64ImageCode(imageSourceInfo.GetSrc());
    auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
    if (base64Code.size() == 0) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "base64Code = %{private}s is empty. %{public}s.",
            imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_BASE_WRONG_CODE_FORMAT, "wrong code format." };
        return nullptr;
    }

    size_t outputLen;
    SkBase64::Error error = SkBase64::Decode(base64Code.data(), base64Code.size(), nullptr, &outputLen);
    if (error != SkBase64::Error::kNoError) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "error base64 image code = %{public}d! Base64Size = %{public}d, outputLen = %{public}d, %{public}s",
            static_cast<int32_t>(base64Code.size()), static_cast<int32_t>(error), static_cast<int32_t>(outputLen),
            imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_BASE_DECODE_IMAGE_FAILED, "decode base64 image failed." };
        return nullptr;
    }

    auto resData = std::make_shared<RSData>();
    resData->BuildUninitialized(outputLen);
    void* output = resData->WritableData();

    error = SkBase64::Decode(base64Code.data(), base64Code.size(), output, &outputLen);
    if (error != SkBase64::Error::kNoError) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "error base64 image code = %{public}d! Base64Size = %{public}d, outputLen = %{public}d, %{public}s",
            static_cast<int32_t>(base64Code.size()), static_cast<int32_t>(error), static_cast<int32_t>(outputLen),
            imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_BASE_DECODE_IMAGE_FAILED, "decode base64 image failed." };
        return nullptr;
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "base64 size=%{public}d, src=%{private}s. %{public}s.", (int)base64Code.size(),
            imageSourceInfo.ToString().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
    }
    return resData;
}

std::string_view Base64ImageLoader::GetBase64ImageCode(const std::string& uri)
{
    auto iter = uri.find_first_of(',');
    if (iter == std::string::npos || ((uri.size() > 0) && (iter == uri.size() - 1))) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "wrong code format!");
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

std::shared_ptr<RSData> ResourceImageLoader::LoadImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    int32_t instanceId = Container::CurrentIdSafely();
    auto uri = imageSourceInfo.GetSrc();
    auto bundleName = imageSourceInfo.GetBundleName();
    auto moudleName = imageSourceInfo.GetModuleName();

    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moudleName, instanceId);
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        auto adapterInCache = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        CHECK_NULL_RETURN(adapterInCache, nullptr);
        ResourceConfiguration resConfig;
        if (imageSourceInfo.GetLocalColorMode() != ColorMode::COLOR_MODE_UNDEFINED) {
            resConfig.SetColorMode(imageSourceInfo.GetLocalColorMode());
        } else {
            resConfig.SetColorMode(Container::CurrentColorMode());
        }
        ConfigurationChange configChange { .colorModeUpdate = true };
        resourceAdapter = adapterInCache->GetOverrideResourceAdapter(resConfig, configChange);
    } else {
        auto themeManager = PipelineBase::CurrentThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        themeConstants = themeManager->GetThemeConstants();
        CHECK_NULL_RETURN(themeConstants, nullptr);
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    std::unique_ptr<uint8_t[]> data;
    size_t dataLen = 0;
    std::string rawFile;
    if (GetResourceId(uri, rawFile)) {
        // must fit raw file firstly, as file name may contains number
        if (!resourceWrapper->GetRawFileData(rawFile, dataLen, data, bundleName, moudleName)) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "get image data by name failed, uri:%{private}s, rawFile:%{private}s",
                uri.c_str(), rawFile.c_str());
            errorInfo = { ImageErrorCode::GET_IMAGE_RESOURCE_GET_DATA_BY_NAME_FAILED,
                "get image data by name failed." };
            return nullptr;
        }
        auto drawingData = std::make_shared<RSData>();
        drawingData->BuildWithCopy(data.get(), dataLen);
        return drawingData;
    }
    uint32_t resId = 0;
    if (!imageSourceInfo.GetIsUriPureNumber() && GetResourceId(uri, resId)) {
        if (resourceWrapper->GetMediaData(resId, dataLen, data, bundleName, moudleName)) {
            auto drawingData = std::make_shared<RSData>();
            drawingData->BuildWithCopy(data.get(), dataLen);
            return drawingData;
        } else {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "get image data by id failed, uri:%{private}s, id:%{public}u", uri.c_str(),
                resId);
            errorInfo = { ImageErrorCode::GET_IMAGE_RESOURCE_GET_DATA_BY_ID_FAILED, "get image data by id failed." };
        }
    }
    std::string resName;
    if (GetResourceName(uri, resName)) {
        if (!resourceWrapper->GetMediaData(resName, dataLen, data, bundleName, moudleName)) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "get image data by name failed, uri:%{private}s, resName:%{private}s",
                uri.c_str(), resName.c_str());
            errorInfo = { ImageErrorCode::GET_IMAGE_RESOURCE_GET_DATA_BY_NAME_FAILED,
                "get image data by name failed." };
            return nullptr;
        }
        auto drawingData = std::make_shared<RSData>();
        drawingData->BuildWithCopy(data.get(), dataLen);
        errorInfo = { ImageErrorCode::DEFAULT, "" };
        return drawingData;
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "load image data failed, as uri is invalid:%{private}s", uri.c_str());
    errorInfo = { ImageErrorCode::GET_IMAGE_RESOURCE_URI_INVALID, "uri is invalid." };
    return nullptr;
}

std::shared_ptr<RSData> DecodedDataProviderImageLoader::LoadImageData(const ImageSourceInfo& /* imageSourceInfo */,
    ImageErrorInfo& /* errorInfo */, const WeakPtr<PipelineBase>& /* context */)
{
    return nullptr;
}

// return orientation of pixmap for cache key
std::string DecodedDataProviderImageLoader::GetThumbnailOrientation(const ImageSourceInfo& src)
{
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
    close(fd);
    CHECK_NULL_RETURN(imageSrc, "");
    std::string orientation = imageSrc->GetProperty("Orientation");
    return orientation;
}

RefPtr<NG::ImageData> DecodedDataProviderImageLoader::LoadDecodedImageData(
    const ImageSourceInfo& src, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& pipelineWk)
{
#ifndef PIXEL_MAP_SUPPORTED
    return nullptr;
#else
    ACE_FUNCTION_TRACE();
    auto pipeline = pipelineWk.Upgrade();
    auto imageDfxConfig = src.GetImageDfxConfig();
    if (!pipeline) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Pipeline is empty in decodeData. %{public}s.",
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto dataProvider = pipeline->GetDataProviderManager();
    if (!dataProvider) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "dataProvider is empty in pipeline. %{public}s.",
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }

    void* pixmapMediaUniquePtr = dataProvider->GetDataProviderThumbnailResFromUri(src.GetSrc());
    auto pixmap = PixelMap::CreatePixelMapFromDataAbility(pixmapMediaUniquePtr);
    if (!pixmap) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "DecodeData is Empty. %{public}s.", imageDfxConfig.ToStringWithoutSrc().c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_DECODE_DATA_PROVIDER_DATA_EMPTY, "decode data is empty." };
        return nullptr;
    }
    TAG_LOGI(AceLogTag::ACE_IMAGE,
        "src=%{private}s, pixmap from Media width*height=%{public}d*%{public}d, ByteCount=%{public}d. %{public}s",
        src.ToString().c_str(), pixmap->GetWidth(), pixmap->GetHeight(), pixmap->GetByteCount(),
        imageDfxConfig.ToStringWithoutSrc().c_str());
    if (SystemProperties::GetDebugPixelMapSaveEnabled()) {
        pixmap->SavePixelMapToFile("_fromMedia_");
    }

    auto cache = pipeline->GetImageCache();
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "DecodedDataProvider src=%{private}s,Key=%{private}s. %{public}s.",
            src.ToString().c_str(), src.GetKey().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
    }
    if (cache) {
        cache->CacheImageData(src.GetKey(), MakeRefPtr<NG::PixmapData>(pixmap));
    }
    return MakeRefPtr<NG::PixmapData>(pixmap);
#endif
}

std::shared_ptr<RSData> PixelMapImageLoader::LoadImageData(const ImageSourceInfo& /* imageSourceInfo */,
    ImageErrorInfo& /* errorInfo */, const WeakPtr<PipelineBase>& /* context */)
{
    return nullptr;
}

RefPtr<NG::ImageData> PixelMapImageLoader::LoadDecodedImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
#ifndef PIXEL_MAP_SUPPORTED
    return nullptr;
#else
    auto imageDfxConfig = imageSourceInfo.GetImageDfxConfig();
    if (!imageSourceInfo.GetPixmap()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "no pixel map in imageSourceInfo, imageSourceInfo: %{private}s. %{public}s.",
            imageSourceInfo.ToString().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "src is pixmap %{private}s, %{public}s.", imageSourceInfo.ToString().c_str(),
            imageDfxConfig.ToStringWithoutSrc().c_str());
    }
    return MakeRefPtr<NG::PixmapData>(imageSourceInfo.GetPixmap());
#endif
}

std::shared_ptr<RSData> SharedMemoryImageLoader::LoadImageData(
    const ImageSourceInfo& src, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& pipelineWk)
{
    CHECK_RUN_ON(BACKGROUND);
    auto imageDfxConfig = src.GetImageDfxConfig();
    auto pipeline = pipelineWk.Upgrade();
    if (!pipeline) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Pipeline is empty in sharedImageLoader. %{public}s.",
            imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto manager = pipeline->GetOrCreateSharedImageManager();
    auto id = RemovePathHead(src.GetSrc());
    bool found = manager->FindImageInSharedImageMap(id, AceType::WeakClaim(this));
    // image data not ready yet, wait for data
    if (!found) {
        manager->RegisterLoader(id, AceType::WeakClaim(this));
        // wait for SharedImageManager to notify
        std::unique_lock<std::mutex> lock(mtx_);
        auto status = cv_.wait_for(lock, TIMEOUT_DURATION);
        if (status == std::cv_status::timeout) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "load SharedMemoryImage timeout! %{private}s,  %{public}s.",
                imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
            errorInfo = { ImageErrorCode::GET_IMAGE_SHARED_MEMORY_LOAD_TIMEOUT, "load shared memory image data timeout." };
            return nullptr;
        }
    }

    std::unique_lock<std::mutex> lock(mtx_);
    auto drawingData = std::make_shared<RSData>();
    drawingData->BuildWithCopy(data_.data(), data_.size());
    return drawingData;
}

void SharedMemoryImageLoader::UpdateData(const std::string& uri, const std::vector<uint8_t>& memData)
{
    TAG_LOGI(AceLogTag::ACE_IMAGE, "SharedMemory image data is ready %{private}s", uri.c_str());
    {
        std::scoped_lock<std::mutex> lock(mtx_);
        data_ = memData;
    }

    cv_.notify_one();
}

std::shared_ptr<RSData> AstcImageLoader::LoadImageData(const ImageSourceInfo& /* ImageSourceInfo */,
    ImageErrorInfo& /* errorInfo */, const WeakPtr<PipelineBase>& /* context */)
{
    return nullptr;
}

RefPtr<NG::ImageData> AstcImageLoader::LoadDecodedImageData(
    const ImageSourceInfo& src, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& pipelineWK)
{
#ifndef PIXEL_MAP_SUPPORTED
    return nullptr;
#else
    ACE_FUNCTION_TRACE();
    auto imageDfxConfig = src.GetImageDfxConfig();
    auto pipeline = pipelineWK.Upgrade();
    if (!pipeline) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Pipeline is empty in sharedImageLoader. Src = %{private}s-%{public}s.",
            imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    auto dataProvider = pipeline->GetDataProviderManager();
    if (!dataProvider) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "DataProvider is empty in AstcLoading. Src = %{private}s, %{public}s.",
            imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }

    void* pixmapMediaUniquePtr = dataProvider->GetDataProviderThumbnailResFromUri(src.GetSrc());
    auto pixmap = PixelMap::CreatePixelMapFromDataAbility(pixmapMediaUniquePtr);
    if (!pixmap) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Pixelmap is Empty. Src = %{private}s, %{public}s.",
            imageDfxConfig.GetImageSrc().c_str(), imageDfxConfig.ToStringWithoutSrc().c_str());
        return nullptr;
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE,
            "src=%{public}s, astc pixmap from Media width*height=%{public}d*%{public}d, ByteCount=%{public}d.",
            imageDfxConfig.ToStringWithSrc().c_str(), pixmap->GetWidth(), pixmap->GetHeight(), pixmap->GetByteCount());
    }

    if (SystemProperties::GetDebugPixelMapSaveEnabled()) {
        pixmap->SavePixelMapToFile(imageDfxConfig.ToStringWithoutSrc() + "_ASTC_LOADER_");
    }

    auto cache = pipeline->GetImageCache();
    if (cache) {
        cache->CacheImageData(src.GetKey(), MakeRefPtr<NG::PixmapData>(pixmap));
    }
    return MakeRefPtr<NG::PixmapData>(pixmap);
#endif
}

std::string AstcImageLoader::GetThumbnailOrientation(const ImageSourceInfo& src)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto dataProvider = pipeline->GetDataProviderManager();
    CHECK_NULL_RETURN(dataProvider, "");

    auto path = src.GetSrc();
    auto pos = path.find("/astc");
    path = path.substr(0, pos);
    int32_t fd = dataProvider->GetDataProviderFile(path, "r");
    CHECK_NULL_RETURN(fd >= 0, "");

    auto imageSrc = ImageSource::Create(fd);
    close(fd);
    CHECK_NULL_RETURN(imageSrc, "");
    std::string orientation = imageSrc->GetProperty("Orientation");
    return orientation;
}

void ImageLoader::WriteCacheToFile(const std::string& uri, const std::vector<uint8_t>& imageData)
{
    BackgroundTaskExecutor::GetInstance().PostTask(
        [uri, data = std::move(imageData)]() {
            ImageFileCache::GetInstance().WriteCacheFile(uri, data.data(), data.size());
        },
        BgTaskPriority::LOW);
}

void ImageLoader::WriteCacheToFile(const std::string& uri, const std::string& imageData)
{
    BackgroundTaskExecutor::GetInstance().PostTask(
        [uri, data = std::move(imageData)]() {
            ImageFileCache::GetInstance().WriteCacheFile(uri, data.data(), data.size());
        },
        BgTaskPriority::LOW);
}
} // namespace OHOS::Ace
