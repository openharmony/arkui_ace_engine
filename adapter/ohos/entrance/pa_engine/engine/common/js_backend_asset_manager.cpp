/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "js_backend_asset_manager.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
const char SLASH = '/';
const char SLASHSTR[] = "/";
const char SUPDIRECTORY[] = "../";

std::string JsBackendAssetManager::GetAssetPath(const std::string& url)
{
    return Framework::GetAssetPathImpl(assetManager_, url);
}

bool JsBackendAssetManager::GetAssetContent(const std::string& url, std::string& content)
{
    return Framework::GetAssetContentImpl(assetManager_, url, content);
}

bool JsBackendAssetManager::GetAssetContent(const std::string& url, std::vector<uint8_t>& content)
{
    return Framework::GetAssetContentImpl(assetManager_, url, content);
}

void JsBackendAssetManager::GetFileInfo(const std::string& fileUri, std::string& fileName, std::string& filePath)
{
    size_t slashPos = fileUri.find_last_of(SLASH);
    if (slashPos == std::string::npos) {
        fileName = fileUri;
    } else {
        fileName = fileUri.substr(slashPos + 1);
        filePath = fileUri.substr(0, slashPos + 1);
    }
 
    if (Framework::StartWith(filePath, SLASHSTR)) {
        filePath = filePath.substr(1);
    }
}

bool JsBackendAssetManager::ParseWorkerUri(const std::string& fileUri, std::string& assetsFilePath)
{
    if (!assetManager_ || fileUri.empty() || (fileUri.length() > PATH_MAX)) {
        return false;
    }

    std::string fileName;
    std::string filePath;
    GetFileInfo(fileUri, fileName, filePath);
    if (Framework::StartWith(filePath, SUPDIRECTORY)) {
        filePath = filePath.substr(3); // 3 : offset of filePath
    }
    std::vector<std::string> files;
    assetManager_->GetAssetList(filePath, files);

    bool fileExist = false;
    for (const auto& file : files) {
        size_t filePos = file.find_last_of(SLASH);
        if (filePos != std::string::npos) {
            if (file.substr(filePos + 1) == fileName) {
                assetsFilePath = filePath + fileName;
                fileExist = true;
                break;
            }
        }
    }
    return fileExist;
}

bool JsBackendAssetManager::ParseFileUri(const std::string& fileUri, std::string& assetsFilePath)
{
    if (assetManager_ == nullptr || fileUri.empty() || (fileUri.length() > PATH_MAX)) {
        return false;
    }

    std::string fileName;
    std::string filePath;
    GetFileInfo(fileUri, fileName, filePath);
    std::vector<std::string> files;
    assetManager_->GetAssetList(filePath, files);

    bool fileExist = false;
    for (const auto& file : files) {
        bool startWithSlash = Framework::StartWith(file, SLASHSTR);
        if ((startWithSlash && (file.substr(1) == fileName)) || (!startWithSlash && (file == fileName))) {
            assetsFilePath = filePath + file;
            fileExist = true;
            break;
        }
    }

    return fileExist;
}

bool JsBackendAssetManager::GetResourceData(const std::string& fileUri, std::vector<uint8_t>& content, std::string& ami)
{
    std::string targetFilePath;
    if (!ParseWorkerUri(fileUri, targetFilePath)) {
        LOGE("GetResourceData parse file uri failed.");
        return false;
    }
    ami = assetManager_->GetAssetPath(targetFilePath, true) + targetFilePath;
    if (!Framework::GetAssetContentAllowEmpty(assetManager_, targetFilePath, content)) {
        LOGE("GetResourceData GetAssetContent failed.");
        return false;
    }

    return true;
}

std::vector<std::string> JsBackendAssetManager::GetLibPath() const
{
    if (assetManager_ == nullptr) {
        LOGE("GetLibPath failed.");
        return std::vector<std::string>();
    }
    return assetManager_->GetLibPath();
}

std::string JsBackendAssetManager::GetAppLibPathKey() const
{
    if (assetManager_ == nullptr) {
        LOGE("GetLibPath failed.");
        return std::string();
    }
    return assetManager_->GetAppLibPathKey();
}
} // namespace OHOS::Ace
