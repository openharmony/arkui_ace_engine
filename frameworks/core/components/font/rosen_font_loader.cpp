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
#include "core/components/font/rosen_font_collection.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

#ifdef USE_GRAPHIC_TEXT_GINE
constexpr size_t FILE_HEAD_LENGTH = 7;           // 7 is the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9;         // 9 is the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // 15 is the size of "internal://app/"
#endif

const std::regex RAWFILE_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");
constexpr uint32_t RAWFILE_RESOURCE_MATCH_SIZE = 2;

RosenFontLoader::RosenFontLoader(const std::string& familyName, const std::string& familySrc)
    : FontLoader(familyName, familySrc) {}

void RosenFontLoader::AddFont(const RefPtr<PipelineBase>& context)
{
    if (familySrc_.empty()) {
        return;
    }

    if (familySrc_.substr(0, strlen(FONT_SRC_NETWORK)) == FONT_SRC_NETWORK) {
        // Get font from NetWork.
        LoadFromNetwork(context);
    } else if (familySrc_.substr(0, strlen(FONT_SRC_RESOURCE)) == FONT_SRC_RESOURCE) {
        // Get font from Resource.
        LoadFromResource(context);
#ifndef USE_GRAPHIC_TEXT_GINE
    } else {
#else
    } else if (familySrc_.find_first_of(':') != std::string::npos) {
        // Get font from file
        // Read file with absolute path to solve the problem that rawfile file registration fails during preview.
        LoadFromFile(context);
    }  else {
#endif
        // Get font from asset.
        LoadFromAsset(context);
    }
}

void RosenFontLoader::LoadFromNetwork(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineBase>& context)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }
            std::vector<uint8_t> fontData;
            if (!DownloadManager::GetInstance().Download(fontLoader->familySrc_, fontData) || fontData.empty()) {
                return;
            }
            context->GetTaskExecutor()->PostTask(
                [fontData, weak] {
                    auto fontLoader = weak.Upgrade();
                    if (!fontLoader) {
                        return;
                    }
                    // Load font.
                    RosenFontCollection::GetInstance().LoadFontFromList(
                        fontData.data(), fontData.size(), fontLoader->familyName_);
                    fontLoader->isLoaded_ = true;

                    // When font is already loaded, notify all which used this font.
                    fontLoader->NotifyCallbacks();
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

#ifdef USE_GRAPHIC_TEXT_GINE
void RosenFontLoader::LoadFromFile(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineBase>& context)
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
                LOGE("src path is too long");
                return;
            }

            auto assetData = fontLoader->GetAssetFromFile(filePath);
            if (!assetData) {
                LOGE("No asset data!");
                return;
            }
            context->GetTaskExecutor()->PostTask(
                [assetData, weak] {
                    auto fontLoader = weak.Upgrade();
                    if (!fontLoader) {
                        return;
                    }
                    // Load font.
                    RosenFontCollection::GetInstance().LoadFontFromList(
                        assetData->GetData(), assetData->GetSize(), fontLoader->familyName_);
                    fontLoader->isLoaded_ = true;

                    // When font is already loaded, notify all which used this font.
                    fontLoader->NotifyCallbacks();
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

RefPtr<Asset> RosenFontLoader::GetAssetFromFile(const std::string& fileName) const
{
    errno = 0;
    LOGI("GetFile: %{private}s", fileName.c_str());
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(fileName, realPath)) {
        return nullptr;
    }
    auto fp = std::fopen(realPath, "rb");
    if (!fp) {
        LOGE("[%{private}s] open file error %{public}s", fileName.c_str(), strerror(errno));
        return nullptr;
    }

    if (std::fseek(fp, 0, SEEK_END) != 0) {
        LOGE("[%{private}s] seek file tail error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    size_t size = std::ftell(fp);
    if (size < 0) {
        LOGE("[%{private}s] tell file error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    auto data = std::make_unique<char[]>(size);
    if (data == nullptr) {
        LOGE("[%{private}s] new uint8_t array failed", fileName.c_str());
        std::fclose(fp);
        return nullptr;
    }

    if (std::fseek(fp, 0, SEEK_SET) != 0) {
        LOGE("[%{private}s] seek file begin error %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }

    auto rsize = std::fread(data.get(), 1, size, fp);
    if (rsize <= 0) {
        LOGE("[%{private}s] read file failed, %{public}s", fileName.c_str(), strerror(errno));
        std::fclose(fp);
        return nullptr;
    }
    std::fclose(fp);
    LOGI("[%{private}s] length: %{public}zu/%{public}zu success", fileName.c_str(), rsize, size);
    return AceType::MakeRefPtr<RSAsset>(std::move(data), rsize);
}

std::string RosenFontLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        LOGW("No need RemovePathHead.");
        return uri;
    }
    std::string head = uri.substr(0, iter);
    if ((head == "file" && uri.size() > FILE_HEAD_LENGTH) || (head == "memory" && uri.size() > MEMORY_HEAD_LENGTH) ||
        (head == "internal" && uri.size() > INTERNAL_FILE_HEAD_LENGTH)) {
        // the file uri format is like "file:///data/data...",
        // the memory uri format is like "memory://font.ttf" for example,
        // iter + 3 to get the absolutely file path substring : "/data/data..." or the font file name: "font.ttf"
        return uri.substr(iter + 3);
    }
    LOGE("Wrong scheme, not a valid File!");
    return std::string();
}
#endif

void RosenFontLoader::LoadFromResource(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineBase>& context)
{
    auto weakContext = AceType::WeakClaim(AceType::RawPtr(context));
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakContext] {
            auto fontLoader = weak.Upgrade();
            auto context = weakContext.Upgrade();
            if (!fontLoader || !context) {
                return;
            }
            auto themeManager = context->GetThemeManager();
            if (!themeManager) {
                LOGE("No theme manager!");
                return;
            }
            auto themeConstants =  themeManager->GetThemeConstants();
            std::string rawFile;
            std::unique_ptr<uint8_t[]> data;
            size_t dataLen = 0;
            std::smatch matches;
            if (std::regex_match(fontLoader->familySrc_, matches, RAWFILE_APP_RES_PATH_REGEX)
                && matches.size() == RAWFILE_RESOURCE_MATCH_SIZE) {
                rawFile = matches[1].str();
            }
            if (rawFile.empty()) {
                return;
            }
            if (!themeConstants->GetRawFileData(rawFile, dataLen, data) || !data.get()) {
                LOGE("Get raw file data failed!");
                return;
            }

            auto fontDataPtr = data.get();
            std::vector<uint8_t> fontData;
            for (size_t i = 0; i < dataLen; i++) {
                fontData.emplace_back(fontDataPtr[i]);
            }
            context->GetTaskExecutor()->PostTask(
                [fontData, weak] {
                    auto fontLoader = weak.Upgrade();
                    if (!fontLoader) {
                        return;
                    }
                    // Load font.
                    RosenFontCollection::GetInstance().LoadFontFromList(fontData.data(), fontData.size(),
                        fontLoader->familyName_);
                    fontLoader->isLoaded_ = true;

                    // When font is already loaded, notify all which used this font.
                    fontLoader->NotifyCallbacks();
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

void RosenFontLoader::LoadFromAsset(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineBase>& context)
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
                LOGE("No asset manager!");
                return;
            }
            std::string assetSrc(fontLoader->familySrc_);
            if (assetSrc[0] == '/') {
                assetSrc = assetSrc.substr(1); // get the asset src without '/'.
            } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
                assetSrc = assetSrc.substr(2); // get the asset src without './'.
            }
            auto assetData = assetManager->GetAsset(assetSrc);
            if (!assetData) {
                LOGE("No asset data!");
                return;
            }

            context->GetTaskExecutor()->PostTask(
                [assetData, weak] {
                    auto fontLoader = weak.Upgrade();
                    if (!fontLoader) {
                        return;
                    }
                    // Load font.
                    RosenFontCollection::GetInstance().LoadFontFromList(
                        assetData->GetData(), assetData->GetSize(), fontLoader->familyName_);
                    fontLoader->isLoaded_ = true;

                    // When font is already loaded, notify all which used this font.
                    fontLoader->NotifyCallbacks();
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::BACKGROUND);
}

void RosenFontLoader::NotifyCallbacks()
{
    for (const auto& [node, callback] : callbacksNG_) {
        if (callback) {
            callback();
        }
    }
    callbacksNG_.clear();
    if (variationChanged_) {
        variationChanged_();
    }
}

} // namespace OHOS::Ace
