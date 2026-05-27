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

#include "base/utils/feature_manager.h"

#include <cstdint>
#include <utility>

#include "base/log/log.h"
#include "core/common/ace_application_info.h"
#include "frameworks/core/common/extra_modules/extra_modules_manager.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t COMP_CONFIG_OK = 0;
constexpr int32_t COMP_CONFIG_LOAD_FAILED = -1;
constexpr char APP_SPACE_COMP_CONFIG_FEATURE_NAME[] = "app_space_comp_config";
constexpr char APP_SPACE_COMP_CONFIG_INIT_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_InitAppSpaceCompConfigReader";
constexpr char APP_SPACE_COMP_CONFIG_GET_CONFIG_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_GetAppSpaceCompConfig";
constexpr char APP_SPACE_COMP_CONFIG_DESTROY_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_DestroyAppSpaceCompConfig";

struct AppSpaceCompConfigResult {
    int32_t code;
    char* value;
};

using AppSpaceCompConfigInitFunc = int32_t (*)(const char* bundleName);
using AppSpaceCompConfigGetConfigFunc = AppSpaceCompConfigResult* (*)(const char* key);
using AppSpaceCompConfigDestroyFunc = void (*)(AppSpaceCompConfigResult* result);

bool EnsureExtraModulesManagerInitialized()
{
    auto& extraModuleManager = ExtraModulesManager::GetInstance();
    if (extraModuleManager.IsInitialized()) {
        return true;
    }
    auto errCode = extraModuleManager.Init();
    if (errCode == ErrCode::SUCCESS || errCode == ErrCode::ALREADY_INITIALIZED) {
        return true;
    }
    LOGW("FeatureManager init extra module manager failed, ret:%{public}d", static_cast<int32_t>(errCode));
    return false;
}

template<typename FuncType>
FuncType LoadAppSpaceCompConfigFunc(const char* capabilityName)
{
    if (!EnsureExtraModulesManagerInitialized()) {
        return nullptr;
    }
    void* funcPtr = nullptr;
    auto& extraModuleManager = ExtraModulesManager::GetInstance();
    auto errCode = extraModuleManager.GetCapability(APP_SPACE_COMP_CONFIG_FEATURE_NAME, capabilityName, &funcPtr);
    if (errCode == ErrCode::SUCCESS) {
        return reinterpret_cast<FuncType>(funcPtr);
    } else if (errCode == ErrCode::SYMBOL_NOT_FOUND) {
        extraModuleManager.UnloadModule(APP_SPACE_COMP_CONFIG_FEATURE_NAME);
        LOGW("FeatureManager load symbol failed, ret:%{public}d", static_cast<int32_t>(errCode));
    } else {
        LOGW("FeatureManager load capability failed, ret:%{public}d", static_cast<int32_t>(errCode));
    }
    return nullptr;
}

int32_t InitAppSpaceCompConfigReader(const std::string& bundleName)
{
    auto initFunc = LoadAppSpaceCompConfigFunc<AppSpaceCompConfigInitFunc>(APP_SPACE_COMP_CONFIG_INIT_SYMBOL);
    if (initFunc == nullptr) {
        return COMP_CONFIG_LOAD_FAILED;
    }
    return initFunc(bundleName.c_str());
}

std::pair<int32_t, std::string> GetAppSpaceCompConfig(const std::string& key)
{
    auto getConfigFunc =
        LoadAppSpaceCompConfigFunc<AppSpaceCompConfigGetConfigFunc>(APP_SPACE_COMP_CONFIG_GET_CONFIG_SYMBOL);
    if (getConfigFunc == nullptr) {
        return { COMP_CONFIG_LOAD_FAILED, "" };
    }

    auto destroyFunc =
        LoadAppSpaceCompConfigFunc<AppSpaceCompConfigDestroyFunc>(APP_SPACE_COMP_CONFIG_DESTROY_SYMBOL);
    if (destroyFunc == nullptr) {
        return { COMP_CONFIG_LOAD_FAILED, "" };
    }

    auto resultPtr = getConfigFunc(key.c_str());
    if (resultPtr == nullptr) {
        return { COMP_CONFIG_LOAD_FAILED, "" };
    }
    std::pair<int32_t, std::string> result = { resultPtr->code, resultPtr->value ? resultPtr->value : "" };
    destroyFunc(resultPtr);
    return result;
}
} // namespace

FeatureManager& FeatureManager::GetInstance()
{
    static FeatureManager instance;
    return instance;
}

FeatureManager::FeatureManager()
{
    Init();
}

void FeatureManager::Init()
{
    initialized_ = false;
    bundleName_ = AceApplicationInfo::GetInstance().GetPackageName();
    if (bundleName_.empty()) {
        LOGW("FeatureManager init failed, bundleName is empty");
        return;
    }

    auto ret = InitAppSpaceCompConfigReader(bundleName_);
    if (ret != COMP_CONFIG_OK) {
        LOGW("FeatureManager init failed, bundleName:%{public}s ret:%{public}d", bundleName_.c_str(), ret);
        bundleName_.clear();
        return;
    }
    initialized_ = true;
}

int32_t FeatureManager::GetFeatureParam(const std::string& key, std::string& value)
{
    value.clear();
    if (key.empty()) {
        LOGW("FeatureManager get config failed, key is empty");
        return KEY_NOT_FOUND;
    }
    if (!initialized_) {
        return INIT_FAILED;
    }

    auto config = GetAppSpaceCompConfig(key);
    if (config.first != COMP_CONFIG_OK) {
        LOGW("FeatureManager get config failed, key:%{public}s ret:%{public}d", key.c_str(), config.first);
        return KEY_NOT_FOUND;
    }
    value = config.second;
    return SUCCESS;
}
} // namespace OHOS::Ace
