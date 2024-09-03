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

#include "form_module_preloader.h"

#include "adapter/ohos/entrance/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"


namespace OHOS::Ace {
namespace {
    // KEY: bundleName, VALUE: formModuleList
    std::unordered_map<std::string, std::unordered_set<std::string>> gFormModuleMap_;

    std::mutex gMapLock_;
}
#ifdef FORM_SUPPORTED
extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceModuleCard(void* runtime, const char* bundleName,
    const void* hapPathMap)
{
    std::unordered_set<std::string> formModuleList;
    auto hapPathMapPtr = reinterpret_cast<const std::map<std::string, std::string>*>(hapPathMap);
    if (!FormModulePreloader::CreateFormModuleList(std::string(bundleName), formModuleList, hapPathMapPtr)) {
        TAG_LOGW(AceLogTag::ACE_FORM, "CreateFormModuleList failed, will load all modules later.");
    }
    Framework::JsiDeclarativeEngineInstance::PreloadAceModuleCard(runtime, formModuleList);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_ReloadAceModuleCard(void* runtime, const char* bundleName,
    const void* hapPathMap)
{
    std::unordered_set<std::string> formModuleList;
    auto hapPathMapPtr = reinterpret_cast<const std::map<std::string, std::string>*>(hapPathMap);
    bool ret = FormModulePreloader::GetNewFormModuleList(std::string(bundleName), formModuleList, hapPathMapPtr);
    if (ret && formModuleList.empty()) {
        TAG_LOGI(AceLogTag::ACE_FORM, "There are no new components to load.");
        return;
    } else if (!ret) {
        TAG_LOGW(AceLogTag::ACE_FORM, "GetNewFormModuleList failed, will load all modules later.");
        formModuleList.clear(); // JsiDeclarativeEngineInstance will load all module if input list is empty.
    }
    Framework::JsiDeclarativeEngineInstance::ReloadAceModuleCard(runtime, formModuleList);
}
#endif

bool FormModulePreloader::CreateFormModuleList(const std::string& bundleName,
    std::unordered_set<std::string>& formModuleList, const std::map<std::string, std::string>* hapPathMap)
{
    if (ReadFormModuleList(bundleName, formModuleList, hapPathMap, false)) {
        std::lock_guard<std::mutex> lock(gMapLock_);
        gFormModuleMap_.emplace(bundleName, formModuleList);
        TAG_LOGI(AceLogTag::ACE_FORM, "push formModuleList to map, bundleName: %{public}s.", bundleName.c_str());
        return true;
    }
    return false;
}

bool FormModulePreloader::GetNewFormModuleList(const std::string& bundleName,
    std::unordered_set<std::string>& formModuleList, const std::map<std::string, std::string>* hapPathMap)
{
    {
        std::lock_guard<std::mutex> lock(gMapLock_);
        if (gFormModuleMap_.find(bundleName) == gFormModuleMap_.end()) {
            // This means that reading the list of components fails on preload
            TAG_LOGW(AceLogTag::ACE_FORM, "All modules of bundle %{public}s have been loaded.", bundleName.c_str());
            return true;
        }
    }
    return ReadFormModuleList(bundleName, formModuleList, hapPathMap, true);
}

bool FormModulePreloader::ReadFormModuleList(const std::string& bundleName, std::unordered_set<std::string>&
    formModuleList, const std::map<std::string, std::string>* hapPathMap, bool isReloadCondition)
{
    if (hapPathMap == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "hapPathMap of bundle %{public}s is null.", bundleName.c_str());
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "hapPaths size of bundle %{public}s is %{public}zu",
        bundleName.c_str(), hapPathMap->size());
    bool readSuccess = false;
    for (auto hapPathPair: *hapPathMap) {
        const std::string& hapPath = hapPathPair.second;
        // Create HapAssetProvider
        RefPtr<AssetManager> assetManager = CreateAssetManager(hapPath);
        if (assetManager == nullptr) {
            TAG_LOGW(AceLogTag::ACE_FORM, "CreateAssetManager failed, hapPath: %{private}s.", hapPath.c_str());
            continue;
        }
        // Read component_collection.json
        std::string content;
        if (!ReadFileFromAssetManager(assetManager, "component_collection.json", content)) {
            TAG_LOGW(
                AceLogTag::ACE_FORM, "Read component_collection.json failed, hapPath: %{private}s.", hapPath.c_str());
            continue;
        }
        // Parse component_collection.json
        if (!ParseComponentCollectionJson(bundleName, content, formModuleList, isReloadCondition)) {
            TAG_LOGW(
                AceLogTag::ACE_FORM, "Parse component_collection.json failed, hapPath: %{private}s.", hapPath.c_str());
            continue;
        }
        readSuccess = true;
    }
    return readSuccess;
}

bool FormModulePreloader::ParseComponentCollectionJson(
    const std::string& bundleName, const std::string& content,
    std::unordered_set<std::string>& formModuleList, bool isReloadCondition)
{
    auto collectionJson = JsonUtil::ParseJsonString(content);
    if (collectionJson == nullptr || collectionJson->IsNull()) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Parse component_collection.json failed");
        return false;
    }
    for (auto child = collectionJson->GetChild(); child && !child->IsNull(); child = child->GetNext()) {
        std::string etsPath = child->GetKey();
        auto item = collectionJson->GetValue(etsPath);
        if (item == nullptr || !item->IsValid() || !item->IsArray()) {
            TAG_LOGW(
                AceLogTag::ACE_FORM, "Parse component_collection.json failed, etsPath: %{private}s.", etsPath.c_str());
            return false;
        }
        int32_t len = item->GetArraySize();
        for (int32_t index = 0; index < len; ++index) {
            auto component = item->GetArrayItem(index);
            if (component == nullptr || !component->IsString()) {
                TAG_LOGW(AceLogTag::ACE_FORM, "Read view failed, etsPath: %{private}s.", etsPath.c_str());
                return false;
            }
            std::string componentName = component->GetString();
            if (!isReloadCondition) {
                formModuleList.emplace(componentName);
                continue;
            }
            std::lock_guard<std::mutex> lock(gMapLock_);
            auto& iter = gFormModuleMap_[bundleName];
            if (iter.find(componentName) == iter.end()) {
                formModuleList.emplace(componentName);
                iter.emplace(bundleName);
            }
        }
    }
    return true;
}

bool FormModulePreloader::ReadFileFromAssetManager(
    const RefPtr<AssetManager>& assetManager, const std::string& fileName, std::string& content)
{
    if (assetManager == nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "assetManager is null.");
        return false;
    }
    auto jsAsset = assetManager->GetAsset(fileName);
    if (jsAsset == nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "uri: %{private}s Asset is null", fileName.c_str());
        return false;
    }
    auto bufLen = jsAsset->GetSize();
    auto buffer = jsAsset->GetData();
    if ((buffer == nullptr) || (bufLen <= 0)) {
        TAG_LOGW(AceLogTag::ACE_FORM, "uri: %{private}s buffer is null", fileName.c_str());
        return false;
    }
    content.assign(buffer, buffer + bufLen);
    return true;
}

RefPtr<AssetManager> FormModulePreloader::CreateAssetManager(const std::string& hapPath)
{
    std::vector<std::string> basePaths;
    basePaths.emplace_back("");
    basePaths.emplace_back("ets/");
    basePaths.emplace_back("ets/widget/");
    basePaths.emplace_back("resources/base/profile/");
    RefPtr<AssetManager> assetManager = Referenced::MakeRefPtr<AssetManagerImpl>();
    if (assetManager == nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Create AssetManagerImpl failed.");
        return nullptr;
    }
    auto assetProvider = CreateAssetProviderImpl(hapPath, basePaths, false);
    if (assetProvider == nullptr) {
        TAG_LOGW(AceLogTag::ACE_FORM, "CreateAssetProvider failed.");
        return nullptr;
    }
    assetManager->PushBack(std::move(assetProvider));
    return assetManager;
}
} // namespace OHOS::Ace
