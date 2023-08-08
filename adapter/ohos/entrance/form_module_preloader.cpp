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

#include <mutex>
#include <unordered_map>

#include "adapter/ohos/entrance/utils.h"
#include "base/log/log.h"
#include "base/json/json_util.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"


namespace OHOS::Ace {
namespace {
    // KEY: bundleName, VALUE: formModuleList
    std::unordered_map<std::string, std::unordered_set<std::string>> gFormModuleMap_;

    std::mutex gMapLock_;
}
#ifdef FORM_SUPPORTED
extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceModuleCard(void* runtime, const char* bundleName)
{
    std::unordered_set<std::string> formModuleList;
    if (!FormModulePreloader::CreateFormModuleList(std::string(bundleName), formModuleList)) {
        LOGW("CreateFormModuleList failed, will load all modules later.");
    }
    Framework::JsiDeclarativeEngineInstance::PreloadAceModuleCard(runtime, formModuleList);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_ReloadAceModuleCard(void* runtime, const char* bundleName)
{
    std::unordered_set<std::string> formModuleList;
    bool ret = FormModulePreloader::GetNewFormModuleList(std::string(bundleName), formModuleList);
    if (ret && formModuleList.empty()) {
        LOGI("There are no new components to load.");
        return;
    } else if (!ret) {
        LOGW("GetNewFormModuleList failed, will load all modules later.");
        formModuleList.clear(); // JsiDeclarativeEngineInstance will load all module if input list is empty.
    }
    Framework::JsiDeclarativeEngineInstance::ReloadAceModuleCard(runtime, formModuleList);
}
#endif

bool FormModulePreloader::CreateFormModuleList(
    const std::string& bundleName, std::unordered_set<std::string>& formModuleList)
{
    if (ReadFormModuleList(bundleName, formModuleList, false)) {
        std::lock_guard<std::mutex> lock(gMapLock_);
        gFormModuleMap_.emplace(bundleName, formModuleList);
        return true;
    }
    return false;
}

bool FormModulePreloader::GetNewFormModuleList(
    const std::string& bundleName, std::unordered_set<std::string>& formModuleList)
{
    {
        std::lock_guard<std::mutex> lock(gMapLock_);
        if (gFormModuleMap_.find(bundleName) == gFormModuleMap_.end()) {
            // This means that reading the list of components fails on preload
            LOGW("All modules of bundle %{public}s have been loaded.", bundleName.c_str());
            return true;
        }
    }
    return ReadFormModuleList(bundleName, formModuleList, true);
}

bool FormModulePreloader::ReadFormModuleList(
    const std::string& bundleName, std::unordered_set<std::string>& formModuleList, bool isReloadCondition)
{
    std::vector<std::string> hapPaths;
    GetHapPathsByBundleName(bundleName, hapPaths);
    if (hapPaths.empty()) {
        LOGE("hapPath of bundle %{public}s is empty.", bundleName.c_str());
        return false;
    }
    LOGI("hapPaths size of bundle %{public}s is %{public}zu", bundleName.c_str(), hapPaths.size());
    for (const std::string& hapPath : hapPaths) {
        // Create HapAssetProvider
        RefPtr<AssetManager> flutterAssetManager = CreateAssetManager(hapPath);
        if (flutterAssetManager == nullptr) {
            LOGE("CreateAssetManager failed, hapPath: %{private}s.", hapPath.c_str());
            return false;
        }
        // Read component_collection.json
        std::unordered_set<std::string> formEtsFilePaths;
        if (!GetFormEtsFilePath(flutterAssetManager, formEtsFilePaths)) {
            LOGE("Read form_config.json failed, hapPath: %{private}s.", hapPath.c_str());
            return false;
        }
        std::string content;
        if (!ReadFileFromAssetManager(flutterAssetManager, "component_collection.json", content)) {
            LOGE("Read component_collection.json failed, hapPath: %{private}s.", hapPath.c_str());
            return false;
        }
        // Parse component_collection.json
        if (!ParseComponentCollectionJson(bundleName, formEtsFilePaths, content, formModuleList, isReloadCondition)) {
            LOGE("Parse component_collection.json failed, hapPath: %{private}s.", hapPath.c_str());
            return false;
        }
    }
    return true;
}

bool FormModulePreloader::ParseComponentCollectionJson(
    const std::string& bundleName, const std::unordered_set<std::string>& formEtsFilePaths,
    const std::string& content, std::unordered_set<std::string>& formModuleList, bool isReloadCondition)
{
    auto collectionJson = JsonUtil::ParseJsonString(content);
    if (collectionJson == nullptr || collectionJson->IsNull()) {
        LOGE("Parse component_collection.json failed");
        return false;
    }
    for (auto child = collectionJson->GetChild(); child && !child->IsNull(); child = child->GetNext()) {
        std::string etsPath = child->GetKey();
        if (!IsFormEtsFilePath(formEtsFilePaths, etsPath)) {
            continue;
        }
        auto item = collectionJson->GetValue(etsPath);
        if (item == nullptr || !item->IsValid() || !item->IsArray()) {
            LOGE("Parse component_collection.json failed, etsPath: %{private}s.", etsPath.c_str());
            return false;
        }
        int32_t len = item->GetArraySize();
        for (int32_t index = 0; index < len; ++index) {
            auto component = item->GetArrayItem(index);
            if (component == nullptr || !component->IsString()) {
                LOGE("Read view failed, etsPath: %{private}s.", etsPath.c_str());
                return false;
            }
            std::string componentName = component->GetString();
            if (!isReloadCondition) {
                formModuleList.emplace(componentName);
                continue;
            }
            std::lock_guard<std::mutex> lock(gMapLock_);
            if (gFormModuleMap_[bundleName].find(componentName) == gFormModuleMap_[bundleName].end()) {
                LOGD("Add new module: %{public}s", componentName.c_str());
                formModuleList.emplace(componentName);
                gFormModuleMap_[bundleName].emplace(bundleName);
            }
        }
    }
    return true;
}

void FormModulePreloader::GetHapPathsByBundleName(const std::string& bundleName, std::vector<std::string>& hapPaths)
{
    // Create AssetProvider and get all hap-paths of target bundle
    std::string packagePath = "/data/bundles/" + bundleName + "/";
    std::vector<std::string> basePaths;
    basePaths.push_back("/");
    auto assetProvider = CreateAssetProvider(packagePath, basePaths, false);
    if (assetProvider == nullptr) {
        LOGE("CreateAssetProvider failed, basePath: %{private}s.", packagePath.c_str());
        return;
    }
    assetProvider->GetAssetList("", hapPaths);
    for (auto iter = hapPaths.begin(); iter != hapPaths.end();) {
        if (!std::regex_match(*iter, std::regex(".*\\.hap"))) {
            iter = hapPaths.erase(iter);
        } else {
            *iter = packagePath + *iter;
            ++iter;
        }
    }
}

bool FormModulePreloader::ReadFileFromAssetManager(
    const RefPtr<AssetManager>& assetManager, const std::string& fileName, std::string& content)
{
    if (assetManager == nullptr) {
        LOGE("assetManager is null.");
        return false;
    }
    auto jsAsset = assetManager->GetAsset(fileName);
    if (jsAsset == nullptr) {
        LOGE("uri: %{private}s Asset is null", fileName.c_str());
        return false;
    }
    auto bufLen = jsAsset->GetSize();
    auto buffer = jsAsset->GetData();
    if ((buffer == nullptr) || (bufLen <= 0)) {
        LOGE("uri: %{private}s buffer is null", fileName.c_str());
        return false;
    }
    content.assign(buffer, buffer + bufLen);
    return true;
}

bool FormModulePreloader::GetFormEtsFilePath(
    const RefPtr<AssetManager>& assetManager, std::unordered_set<std::string>& filePaths)
{
    // Read form_config.json
    std::string content;
    if (!ReadFileFromAssetManager(assetManager, "form_config.json", content)) {
        LOGE("Read form_config failed");
        return false;
    }
    auto collectionJson = JsonUtil::ParseJsonString(content);
    if (collectionJson == nullptr || collectionJson->IsNull()) {
        LOGE("ParseJsonString failed.");
        return false;
    }
    auto formJson = collectionJson->GetValue("forms");
    if (formJson == nullptr || formJson->IsNull() || !formJson->IsArray()) {
        LOGE("Get form-config from json failed.");
        return false;
    }
    // Read FormEtsFilePath
    int32_t len = formJson->GetArraySize();
    for (int32_t index = 0; index < len; ++index) {
        auto config = formJson->GetArrayItem(index);
        if (config == nullptr || config->IsNull()) {
            LOGE("Form-config is invalid.");
            return false;
        }
        auto path = config->GetValue("src");
        if (path == nullptr || !path->IsString()) {
            LOGE("Read src from form-config failed.");
            return false;
        }
        filePaths.emplace(path->GetString());
    }
    return true;
}

bool FormModulePreloader::IsFormEtsFilePath(
    const std::unordered_set<std::string>& formEtsFilePaths, std::string path)
{
    std::replace(path.begin(), path.end(), '\\', '/');
    std::string rootPath = "src/main";
    auto pos = path.find(rootPath);
    if (pos == std::string::npos) {
        return formEtsFilePaths.find(path) != formEtsFilePaths.end();
    }
    // Convert to relative path
    std::string relativePath = path.substr(pos + static_cast<int32_t>(rootPath.length()));
    relativePath.insert(relativePath.begin(), '.');
    return formEtsFilePaths.find(relativePath) != formEtsFilePaths.end();
}

RefPtr<AssetManager> FormModulePreloader::CreateAssetManager(const std::string& hapPath)
{
    RefPtr<AssetManager> flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
    if (flutterAssetManager == nullptr) {
        LOGE("Create flutterAssetManager failed.");
        return nullptr;
    }
    std::vector<std::string> basePaths;
    basePaths.emplace_back("");
    basePaths.emplace_back("ets/");
    basePaths.emplace_back("resources/base/profile/");
    auto assetProvider = CreateAssetProvider(hapPath, basePaths, false);
    if (assetProvider == nullptr) {
        LOGE("CreateAssetProvider failed");
        return nullptr;
    }
    flutterAssetManager->PushBack(std::move(assetProvider));
    return flutterAssetManager;
}
} // namespace OHOS::Ace
