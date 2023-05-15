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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_ASSET_MANAGER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_ASSET_MANAGER_H

#include "base/resource/asset_manager.h"

namespace OHOS::Ace {
class JsBackendAssetManager : public AceType {
    DECLARE_ACE_TYPE(JsBackendAssetManager, AceType);
public:
    explicit JsBackendAssetManager(const RefPtr<AssetManager>& assetManager) : assetManager_(assetManager) {}
    ~JsBackendAssetManager() override = default;

    std::string GetAssetPath(const std::string& url);
    bool GetAssetContent(const std::string& url, std::string& content);
    bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content);
    bool GetResourceData(const std::string& fileUri, std::vector<uint8_t>& content, std::string& ami);
    std::vector<std::string> GetLibPath() const;
    std::string GetAppLibPathKey() const;

private:
    bool ParseFileUri(const std::string& fileUri, std::string& assetsFilePath);
    bool ParseWorkerUri(const std::string& fileUri, std::string& assetsFilePath);
    void GetFileInfo(const std::string& fileUri, std::string& fileName, std::string& filePath);
    RefPtr<AssetManager> assetManager_ = nullptr;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_ASSET_MANAGER_H
