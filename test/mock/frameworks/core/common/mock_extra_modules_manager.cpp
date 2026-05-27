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

#include "mock_extra_modules_manager.h"

#include "frameworks/core/common/extra_modules/extra_modules_manager.h"

namespace OHOS::Ace::MockExtraModulesManager {
namespace {
AppSpaceCompConfigInitFunc g_initFunc = nullptr;
AppSpaceCompConfigGetConfigFunc g_getConfigFunc = nullptr;
AppSpaceCompConfigDestroyFunc g_destroyFunc = nullptr;
} // namespace

void Reset()
{
    g_initFunc = nullptr;
    g_getConfigFunc = nullptr;
    g_destroyFunc = nullptr;
}

void SetAppSpaceCompConfigFuncs(AppSpaceCompConfigInitFunc initFunc, AppSpaceCompConfigGetConfigFunc getConfigFunc,
    AppSpaceCompConfigDestroyFunc destroyFunc)
{
    g_initFunc = initFunc;
    g_getConfigFunc = getConfigFunc;
    g_destroyFunc = destroyFunc;
}

AppSpaceCompConfigInitFunc GetAppSpaceCompConfigInitFunc()
{
    return g_initFunc;
}

AppSpaceCompConfigGetConfigFunc GetAppSpaceCompConfigGetConfigFunc()
{
    return g_getConfigFunc;
}

AppSpaceCompConfigDestroyFunc GetAppSpaceCompConfigDestroyFunc()
{
    return g_destroyFunc;
}
} // namespace OHOS::Ace::MockExtraModulesManager

namespace OHOS::Ace {
namespace {
constexpr char APP_SPACE_COMP_CONFIG_FEATURE_NAME[] = "app_space_comp_config";
constexpr char APP_SPACE_COMP_CONFIG_INIT_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_InitAppSpaceCompConfigReader";
constexpr char APP_SPACE_COMP_CONFIG_GET_CONFIG_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_GetAppSpaceCompConfig";
constexpr char APP_SPACE_COMP_CONFIG_DESTROY_SYMBOL[] = "OHOS_COMPCONFIGCLIENT_DestroyAppSpaceCompConfig";

class MockExtraModulesManagerImpl final : public ExtraModulesManager {
public:
    ErrCode Init() override
    {
        initialized_ = true;
        return ErrCode::SUCCESS;
    }

    ErrCode GetCapability(const std::string& featureName, const std::string& capabilityName, void** outFuncPtr) override
    {
        if (outFuncPtr == nullptr) {
            return ErrCode::INVALID_STATE;
        }
        *outFuncPtr = nullptr;
        if (!initialized_) {
            return ErrCode::NOT_INITIALIZED;
        }
        if (featureName != APP_SPACE_COMP_CONFIG_FEATURE_NAME) {
            return ErrCode::FEATURE_NOT_FOUND;
        }
        if (capabilityName == APP_SPACE_COMP_CONFIG_INIT_SYMBOL) {
            auto initFunc = MockExtraModulesManager::GetAppSpaceCompConfigInitFunc();
            if (initFunc == nullptr) {
                return ErrCode::SYMBOL_NOT_FOUND;
            }
            *outFuncPtr = reinterpret_cast<void*>(initFunc);
            return ErrCode::SUCCESS;
        }
        if (capabilityName == APP_SPACE_COMP_CONFIG_GET_CONFIG_SYMBOL) {
            auto getConfigFunc = MockExtraModulesManager::GetAppSpaceCompConfigGetConfigFunc();
            if (getConfigFunc == nullptr) {
                return ErrCode::SYMBOL_NOT_FOUND;
            }
            *outFuncPtr = reinterpret_cast<void*>(getConfigFunc);
            return ErrCode::SUCCESS;
        }
        if (capabilityName == APP_SPACE_COMP_CONFIG_DESTROY_SYMBOL) {
            auto destroyFunc = MockExtraModulesManager::GetAppSpaceCompConfigDestroyFunc();
            if (destroyFunc == nullptr) {
                return ErrCode::SYMBOL_NOT_FOUND;
            }
            *outFuncPtr = reinterpret_cast<void*>(destroyFunc);
            return ErrCode::SUCCESS;
        }
        return ErrCode::SYMBOL_NOT_FOUND;
    }

    ErrCode UnloadModule(const std::string& featureName) override
    {
        return featureName == APP_SPACE_COMP_CONFIG_FEATURE_NAME ? ErrCode::SUCCESS : ErrCode::FEATURE_NOT_FOUND;
    }

    ErrCode Destroy() override
    {
        initialized_ = false;
        return ErrCode::SUCCESS;
    }

    bool IsInitialized() const override
    {
        return initialized_;
    }

private:
    bool initialized_ = false;
};
} // namespace

ExtraModulesManager& ExtraModulesManager::GetInstance()
{
    static MockExtraModulesManagerImpl instance;
    return instance;
}
} // namespace OHOS::Ace
