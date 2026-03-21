/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "extra_modules_manager_impl.h"

#include <cstring>
#include <dlfcn.h>
#include <fstream>
#include <memory>
#include <sstream>

#include "base/json/json_util.h"
#include "base/log/log.h"

namespace OHOS::Ace {
const std::string CONFIG_FILE_PATH = "/etc/arkui/extra_modules_feature_config.json";

const char* ErrCodeToString(ErrCode code)
{
    switch (code) {
        case ErrCode::SUCCESS:
            return "Success";
        case ErrCode::NOT_INITIALIZED:
            return "Not initialized";
        case ErrCode::CONFIG_FILE_NOT_FOUND:
            return "Config file not found";
        case ErrCode::CONFIG_PARSE_FAILED:
            return "Config parse failed";
        case ErrCode::FEATURE_NOT_FOUND:
            return "Feature not found";
        case ErrCode::CAPABILITY_NOT_FOUND:
            return "Capability not found";
        case ErrCode::MODULE_LOAD_FAILED:
            return "Module load failed";
        case ErrCode::SYMBOL_NOT_FOUND:
            return "Symbol not found";
        case ErrCode::MODULE_NOT_LOADED:
            return "Module not loaded";
        case ErrCode::INVALID_STATE:
            return "Invalid state";
        case ErrCode::ALREADY_INITIALIZED:
            return "Already initialized";
        default:
            return "Unknown error";
    }
}

ModuleHolder::~ModuleHolder()
{
    Clear();
}

ModuleHolder::ModuleHolder(ModuleHolder&& other) noexcept
    : moduleName(std::move(other.moduleName)), capabilities(std::move(other.capabilities)),
      moduleHandle(other.moduleHandle)
{
    other.moduleHandle = nullptr;
}

ModuleHolder& ModuleHolder::operator=(ModuleHolder&& other) noexcept
{
    if (this != &other) {
        Clear();

        moduleName = std::move(other.moduleName);
        capabilities = std::move(other.capabilities);
        moduleHandle = other.moduleHandle;
        other.moduleHandle = nullptr;
    }
    return *this;
}

void ModuleHolder::Clear()
{
    for (auto& pair : capabilities) {
        pair.second = nullptr;
    }

    if (moduleHandle != nullptr) {
        dlclose(moduleHandle);
        moduleHandle = nullptr;
    }
}

ExtraModulesManagerImpl::ExtraModulesManagerImpl() : initialized_(false) {}

ExtraModulesManagerImpl::~ExtraModulesManagerImpl()
{
    Destroy();
}

ExtraModulesManager& ExtraModulesManager::GetInstance()
{
    static ExtraModulesManagerImpl instance;
    return instance;
}

ErrCode ExtraModulesManagerImpl::Init()
{
    if (initialized_) {
        return ErrCode::ALREADY_INITIALIZED;
    }

    ErrCode errCode = ParseConfigFile(CONFIG_FILE_PATH);
    if (errCode != ErrCode::SUCCESS) {
        LOGE("Failed to parse config file: %{public}s", ErrCodeToString(errCode));
        return errCode;
    }

    initialized_ = true;
    return ErrCode::SUCCESS;
}

ErrCode ExtraModulesManagerImpl::GetCapability(
    const std::string& featureName, const std::string& capabilityName, void** outFuncPtr)
{
    if (outFuncPtr == nullptr) {
        LOGE("Invalid output parameter");
        return ErrCode::INVALID_STATE;
    }
    *outFuncPtr = nullptr;

    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        LOGE("Not initialized");
        return ErrCode::NOT_INITIALIZED;
    }
    auto it = moduleCache_.find(featureName);
    if (it == moduleCache_.end()) {
        LOGE("Feature not found: %{public}s", featureName.c_str());
        return ErrCode::FEATURE_NOT_FOUND;
    }
    ModuleHolder& holder = it->second;
    auto capIt = holder.capabilities.find(capabilityName);
    if (capIt == holder.capabilities.end()) {
        LOGE("Capability '%{public}s' not found in feature '%{public}s'", capabilityName.c_str(), featureName.c_str());
        return ErrCode::CAPABILITY_NOT_FOUND;
    }
    if (!holder.IsLoaded()) {
        ErrCode errCode = LoadModule(holder);
        if (errCode != ErrCode::SUCCESS) {
            LOGE("Failed to load module: %{public}s", ErrCodeToString(errCode));
            return errCode;
        }
    }
    if (capIt->second == nullptr) {
        void* symbolPtr = nullptr;
        ErrCode errCode = GetSymbol(holder.moduleHandle, capabilityName, &symbolPtr);
        if (errCode != ErrCode::SUCCESS) {
            LOGE("Failed to get symbol: %{public}s", ErrCodeToString(errCode));
            return errCode;
        }
        capIt->second = symbolPtr;
    }
    *outFuncPtr = capIt->second;
    return ErrCode::SUCCESS;
}

ErrCode ExtraModulesManagerImpl::UnloadModule(const std::string& featureName)
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = moduleCache_.find(featureName);
    if (it == moduleCache_.end()) {
        return ErrCode::FEATURE_NOT_FOUND;
    }
    ModuleHolder& holder = it->second;
    if (!holder.IsLoaded()) {
        return ErrCode::MODULE_NOT_LOADED;
    }
    holder.Clear();
    return ErrCode::SUCCESS;
}

ErrCode ExtraModulesManagerImpl::Destroy()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        return ErrCode::NOT_INITIALIZED;
    }
    for (auto& pair : moduleCache_) {
        if (pair.second.IsLoaded()) {
            pair.second.Clear();
        }
    }
    moduleCache_.clear();
    initialized_ = false;
    return ErrCode::SUCCESS;
}

ErrCode ExtraModulesManagerImpl::LoadModule(ModuleHolder& holder)
{
    std::string libraryPath = BuildLibraryPath(holder.moduleName);

    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        const char* error = dlerror();
        LOGE("dlopen failed for %{public}s: %{public}s", libraryPath.c_str(), error ? error : "unknown error");
        return ErrCode::MODULE_LOAD_FAILED;
    }
    holder.moduleHandle = handle;
    return ErrCode::SUCCESS;
}

ErrCode ExtraModulesManagerImpl::ParseConfigFile(const std::string& configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open()) {
        LOGE("Cannot open config file: %{public}s", configPath.c_str());
        return ErrCode::CONFIG_FILE_NOT_FOUND;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    auto config = JsonUtil::ParseJsonString(content);
    if (!config || !config->IsValid() || !config->IsObject()) {
        LOGE("Invalid JSON config file: %{public}s", configPath.c_str());
        return ErrCode::CONFIG_PARSE_FAILED;
    }

    auto feature = config->GetChild();
    while (feature && feature->IsValid()) {
        std::string featureName = feature->GetKey();
        if (!feature->IsObject()) {
            LOGE("Feature '%{public}s' is not an object", featureName.c_str());
            feature = feature->GetNext();
            continue;
        }

        if (!feature->Contains("module") || !feature->Contains("capabilities")) {
            LOGE("Invalid config for feature '%{public}s': missing 'module' or 'capabilities' field",
                featureName.c_str());
            feature = feature->GetNext();
            continue;
        }

        ModuleHolder holder;
        holder.moduleName = feature->GetString("module", "");

        auto capabilities = feature->GetValue("capabilities");
        if (!capabilities || !capabilities->IsArray()) {
            LOGE("Invalid 'capabilities' field for '%{public}s': expected array", featureName.c_str());
            feature = feature->GetNext();
            continue;
        }

        int size = capabilities->GetArraySize();
        for (int i = 0; i < size; ++i) {
            auto cap = capabilities->GetArrayItem(i);
            if (cap && cap->IsString()) {
                holder.capabilities[cap->GetString()] = nullptr;
            }
        }
        moduleCache_[featureName] = std::move(holder);
        feature = feature->GetNext();
    }
    return ErrCode::SUCCESS;
}

std::string ExtraModulesManagerImpl::BuildLibraryPath(const std::string& moduleName)
{
    std::string libraryPath;
#if defined(__aarch64__) || defined(__x86_64__)
    libraryPath = "/system/lib64/" + moduleName;
#else
    libraryPath = "/system/lib/" + moduleName;
#endif
    return libraryPath;
}

ErrCode ExtraModulesManagerImpl::GetSymbol(void* moduleHandle, const std::string& symbolName, void** outSymbolPtr)
{
    if (moduleHandle == nullptr || outSymbolPtr == nullptr) {
        return ErrCode::INVALID_STATE;
    }
    *outSymbolPtr = nullptr;

    dlerror();

    void* symbol = dlsym(moduleHandle, symbolName.c_str());
    if (symbol == nullptr) {
        const char* error = dlerror();
        LOGE("dlsym failed for '%{public}s': %{public}s", symbolName.c_str(), error ? error : "unknown error");
        return ErrCode::SYMBOL_NOT_FOUND;
    }
    *outSymbolPtr = symbol;
    return ErrCode::SUCCESS;
}
} // namespace OHOS::Ace