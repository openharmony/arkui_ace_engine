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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_EXTRA_MODULES_EXTRA_MODULES_MANAGER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_EXTRA_MODULES_EXTRA_MODULES_MANAGER_IMPL_H

#include <mutex>
#include <unordered_map>

#include "core/common/extra_modules/extra_modules_manager.h"

namespace OHOS::Ace {

const char* ErrCodeToString(ErrCode code);

struct ModuleHolder {
    ModuleHolder() : moduleHandle(nullptr) {}
    ~ModuleHolder();
    ModuleHolder(const ModuleHolder&) = delete;
    ModuleHolder& operator=(const ModuleHolder&) = delete;
    ModuleHolder(ModuleHolder&& other) noexcept;
    ModuleHolder& operator=(ModuleHolder&& other) noexcept;
    bool IsLoaded() const
    {
        return moduleHandle != nullptr;
    }
    void Clear();
    std::string moduleName;
    std::unordered_map<std::string, void*> capabilities;
    void* moduleHandle;
};

class ExtraModulesManagerImpl final : public ExtraModulesManager {
public:
    ~ExtraModulesManagerImpl() override;
    ErrCode Init() override;
    ErrCode GetCapability(
        const std::string& featureName, const std::string& capabilityName, void** outFuncPtr) override;
    ErrCode UnloadModule(const std::string& featureName) override;
    ErrCode Destroy() override;
    bool IsInitialized() const override
    {
        return initialized_;
    }

private:
    ErrCode LoadModule(ModuleHolder& holder);
    ErrCode ParseConfigFile(const std::string& configPath);
    std::string BuildLibraryPath(const std::string& moduleName);
    ErrCode GetSymbol(void* moduleHandle, const std::string& symbolName, void** outSymbolPtr);
    ACE_DISALLOW_COPY_AND_MOVE(ExtraModulesManagerImpl);
    friend ExtraModulesManager;
    ExtraModulesManagerImpl();

private:
    std::unordered_map<std::string, ModuleHolder> moduleCache_;
    mutable std::mutex mutex_;
    bool initialized_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_FEATURE_CONFIG_EXTRA_MODULES_EXTRA_MODULES_MANAGER_IMPL_H
