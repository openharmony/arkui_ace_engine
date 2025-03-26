/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/font/rosen_font_loader.h"

#include "base/network/download_manager.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

constexpr size_t FILE_HEAD_LENGTH = 7;           // 7 is the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9;         // 9 is the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // 15 is the size of "internal://app/"

const std::regex RAWFILE_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");
constexpr uint32_t RAWFILE_RESOURCE_MATCH_SIZE = 2;

RosenFontLoader::RosenFontLoader(const std::string& familyName, const std::string& familySrc)
    : FontLoader(familyName, familySrc)
{}
RosenFontLoader::RosenFontLoader(const std::string& familyName, const std::vector<std::string>& familySrcArray)
    : FontLoader(familyName, familySrcArray)
{}

void RosenFontLoader::AddFont(
    const RefPtr<PipelineBase>& context, const std::string& bundleName, const std::string& moduleName)
{
    if (context == nullptr || familySrc_.empty()) {
        TAG_LOGW(AceLogTag::ACE_FONT, "AddFont familySrc is empty:%{public}d", familySrc_.empty());
        return;
    }

    if (familySrc_.substr(0, strlen(FONT_SRC_NETWORK)) == FONT_SRC_NETWORK) {
        // Get font from NetWork.
        LoadFromNetwork(context);
    } else if (familySrc_.substr(0, strlen(FONT_SRC_RESOURCE)) == FONT_SRC_RESOURCE) {
        // Get font from Resource.
        LoadFromResource(context, bundleName, moduleName);
    } else if (familySrc_.find_first_of(':') != std::string::npos) {
        // Get font from file
        // Read file with absolute path to solve the problem that rawfile file registration fails during preview.
        LoadFromFile(context);
    } else {
        // Get font from asset.
        LoadFromAsset(context);
    }
}

void RosenFontLoader::SetDefaultFontFamily(const char* fontFamily, const std::vector<std::string>& familySrc)
{
    RosenFontCollection::GetInstance().LoadFontFamily(fontFamily, familySrc);
}

void RosenFontLoader::LoadFromNetwork(const RefPtr<PipelineBase>& context)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }
            TAG_LOGI(AceLogTag::ACE_FONT, "begin to load font from network.");
            DownloadCallback downloadCallback;
            downloadCallback.successCallback = [weak, weakContext](
                                                   const std::string&& imageData, bool async, int32_t instanceId) {
                ContainerScope scope(instanceId);
                auto context = weakContext.Upgrade();
                CHECK_NULL_VOID(context);
                context->GetTaskExecutor()->PostTask(
                    [imageData, weak] {
                        auto fontLoader = weak.Upgrade();
                        CHECK_NULL_VOID(fontLoader);
                        // Load font.
                        RosenFontCollection::GetInstance().LoadFontFromList(
                            reinterpret_cast<const uint8_t*>(imageData.c_str()), imageData.size(),
                            fontLoader->familyName_);
                        fontLoader->isLoaded_ = true;
                        // When font is already loaded, notify all which used this font.
                        fontLoader->NotifyCallbacks();
                    },
                    TaskExecutor::TaskType::UI, "ArkUIFontLoadFromList");
            };
            downloadCallback.failCallback = [](std::string errorMessage, bool async, int32_t instanceId) {
                TAG_LOGW(
                    AceLogTag::ACE_FONT, "Sync Download font Failed,errorMessage is %{public}s", errorMessage.c_str());
            };
            downloadCallback.cancelCallback = downloadCallback.failCallback;
            if (!DownloadManager::GetInstance()->DownloadSync(std::move(downloadCallback),
                fontLoader->familySrc_, context->GetInstanceId(), -1)) {
                return;
            }
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIFontLoadFromNetwork");
}

void RosenFontLoader::LoadFromFile(const RefPtr<PipelineBase>& context)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }

            auto filePath = fontLoader->RemovePathHead(fontLoader->familySrc_);
            if (filePath.length() > PATH_MAX) {
                TAG_LOGW(AceLogTag::ACE_FONT, "src path is too long");
                return;
            }
            TAG_LOGI(AceLogTag::ACE_FONT, "begin to load font from file.");

            auto assetData = fontLoader->GetAssetFromFile(filePath);
            if (!assetData) {
                TAG_LOGW(AceLogTag::ACE_FONT, "No asset data!");
                return;
            }
            const std::vector<uint8_t> fontData(assetData->GetData(), assetData->GetData() + assetData->GetSize());
            fontLoader->PostLoadFontTask(std::move(fontData), context);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIFontLoadFromFile");
}

RefPtr<Asset> RosenFontLoader::GetAssetFromFile(const std::string& fileName) const
{
    errno = 0;
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(fileName, realPath)) {
        return nullptr;
    }
    auto fp = std::fopen(realPath, "rb");
    if (!fp) {
        TAG_LOGW(AceLogTag::ACE_FONT, "[%{private}s] open file error %{public}s", fileName.c_str(), strerror(errno));
        return nullptr;
    }

    if (std::fseek(fp, 0, SEEK_END) != 0) {
        TAG_LOGW(
            AceLogTag::ACE_FONT, "[%{private}s] seek file tail error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    size_t size = std::ftell(fp);
    if (size < 0) {
        TAG_LOGW(AceLogTag::ACE_FONT, "[%{private}s] tell file error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    auto data = std::make_unique<char[]>(size);
    if (data == nullptr) {
        TAG_LOGW(AceLogTag::ACE_FONT, "[%{private}s] new uint8_t array failed", fileName.c_str());
        std::fclose(fp);
        return nullptr;
    }

    if (std::fseek(fp, 0, SEEK_SET) != 0) {
        TAG_LOGW(
            AceLogTag::ACE_FONT, "[%{private}s] seek file begin error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    auto rsize = std::fread(data.get(), 1, size, fp);
    if (rsize <= 0) {
        TAG_LOGW(AceLogTag::ACE_FONT, "[%{private}s] read file failed, %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }
    std::fclose(fp);
    TAG_LOGI(
        AceLogTag::ACE_FONT, "[%{private}s] length: %{public}zu/%{public}zu success", fileName.c_str(), rsize, size);
    return AceType::MakeRefPtr<RSAsset>(std::move(data), rsize);
}

std::string RosenFontLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        TAG_LOGI(AceLogTag::ACE_FONT, "No need RemovePathHead.");
        return uri;
    }
    std::string head = uri.substr(0, iter);
    if ((head == "file" && uri.size() > FILE_HEAD_LENGTH) || (head == "memory" && uri.size() > MEMORY_HEAD_LENGTH) ||
        (head == "internal" && uri.size() > INTERNAL_FILE_HEAD_LENGTH)) {
        // the file uri format is like "file:///data/data...",
        // the memory uri format is like "memory://font.ttf" for example,
        // iter + 3 to get the absolutely file path substring : "/data/data..." or the font file name: "font.ttf"
        auto startIndex = iter + 3;
        startIndex = std::clamp(startIndex, static_cast<size_t>(0), uri.length());
        return uri.substr(startIndex);
    }
    TAG_LOGW(AceLogTag::ACE_FONT, "Wrong scheme, not a valid File!");
    return std::string();
}

void RosenFontLoader::LoadFromResource(
    const RefPtr<PipelineBase>& context, const std::string& bundleName, const std::string& moduleName)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext, bundleName, moduleName] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }
            auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, context->GetInstanceId());
            RefPtr<ResourceAdapter> resourceAdapter = nullptr;
            RefPtr<ThemeConstants> themeConstants = nullptr;
            if (SystemProperties::GetResourceDecoupling()) {
                resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
                CHECK_NULL_VOID(resourceAdapter);
            } else {
                auto themeManager = PipelineBase::CurrentThemeManager();
                CHECK_NULL_VOID(themeManager);
                themeConstants = themeManager->GetThemeConstants();
                CHECK_NULL_VOID(themeConstants);
            }
            auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
            std::string rawFile;
            std::unique_ptr<uint8_t[]> data;
            size_t dataLen = 0;
            std::smatch matches;
            if (std::regex_match(fontLoader->familySrc_, matches, RAWFILE_APP_RES_PATH_REGEX) &&
                matches.size() == RAWFILE_RESOURCE_MATCH_SIZE) {
                rawFile = matches[1].str();
            }
            if (rawFile.empty()) {
                TAG_LOGW(AceLogTag::ACE_FONT, "LoadFromResource rawFile is empty");
                return;
            }

            if (!resourceWrapper->GetRawFileData(rawFile, dataLen, data, bundleName, moduleName) || !data.get()) {
                TAG_LOGW(AceLogTag::ACE_FONT, "Get font data by rawFile failed, src:%{private}s, rawFile:%{public}s",
                    fontLoader->familySrc_.c_str(), rawFile.c_str());
                return;
            }

            const std::vector<uint8_t> fontData(data.get(), data.get() + dataLen);
            fontLoader->PostLoadFontTask(std::move(fontData), context);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIFontLoadFromResource");
}

void RosenFontLoader::LoadFromAsset(const RefPtr<PipelineBase>& context)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }
            auto assetManager = context->GetAssetManager();
            if (!assetManager) {
                return;
            }
            TAG_LOGI(AceLogTag::ACE_FONT, "begin to load font from asset.");
            std::string assetSrc(fontLoader->familySrc_);
            if (assetSrc[0] == '/') {
                assetSrc = assetSrc.substr(1); // get the asset src without '/'.
            } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
                assetSrc = assetSrc.substr(2); // get the asset src without './'.
            }
            auto assetData = assetManager->GetAsset(assetSrc);
            if (!assetData) {
                TAG_LOGW(AceLogTag::ACE_FONT, "No asset data!");
                return;
            }
            const std::vector<uint8_t> fontData(assetData->GetData(), assetData->GetData() + assetData->GetSize());
            fontLoader->PostLoadFontTask(std::move(fontData), context);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIFontLoadFromAsset");
}

void RosenFontLoader::PostLoadFontTask(const std::vector<uint8_t>& fontData, const RefPtr<PipelineBase>& context)
{
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [fontData, weak = AceType::WeakClaim(this)] {
            auto fontLoader = weak.Upgrade();
            CHECK_NULL_VOID(fontLoader);
            // Load font.
            RosenFontCollection::GetInstance().LoadFontFromList(
                fontData.data(), fontData.size(), fontLoader->familyName_);
            fontLoader->isLoaded_ = true;

            // When font is already loaded, notify all which used this font.
            fontLoader->NotifyCallbacks();
        },
        TaskExecutor::TaskType::UI, "ArkUIFontLoadFromList");
}

void RosenFontLoader::NotifyCallbacks()
{
    for (const auto& [node, callback] : callbacks_) {
        if (callback) {
            callback();
        }
    }
    callbacks_.clear();
    std::stringstream ssNodes;
    ssNodes << "[";
    for (const auto& [node, callback] : callbacksNG_) {
        auto uiNode = node.Upgrade();
        if (uiNode) {
            ssNodes << std::to_string(uiNode->GetId());
            ssNodes << ", ";
        }
        if (callback) {
            callback();
        }
    }
    ssNodes << "]";
    ACE_SCOPED_TRACE("Load Success! NotifyCallbacks [familyName:%s][size:%d][nodes:%s]", familyName_.c_str(),
        static_cast<uint32_t>(callbacksNG_.size()), ssNodes.str().c_str());
    TAG_LOGI(AceLogTag::ACE_FONT,
        "Load Success! NotifyCallbacks [familyName:%{public}s][size:%{public}d][nodes:%{public}s]", familyName_.c_str(),
        static_cast<uint32_t>(callbacksNG_.size()), ssNodes.str().c_str());
    callbacksNG_.clear();
    if (variationChanged_) {
        variationChanged_();
    }
}

} // namespace OHOS::Ace
