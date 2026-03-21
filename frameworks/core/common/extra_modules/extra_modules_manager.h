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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EXTRA_MODULES_EXTRA_MODULES_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EXTRA_MODULES_EXTRA_MODULES_MANAGER_H

#include <string>

#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

enum class ErrCode {
    SUCCESS = 0,
    NOT_INITIALIZED = 1,
    CONFIG_FILE_NOT_FOUND = 2,
    CONFIG_PARSE_FAILED = 3,
    FEATURE_NOT_FOUND = 4,
    CAPABILITY_NOT_FOUND = 5,
    MODULE_LOAD_FAILED = 6,
    SYMBOL_NOT_FOUND = 7,
    MODULE_NOT_LOADED = 8,
    INVALID_STATE = 9,
    ALREADY_INITIALIZED = 10
};

class ExtraModulesManager {
public:
    static ExtraModulesManager& GetInstance();
    virtual ~ExtraModulesManager() = default;

    virtual ErrCode Init() = 0;
    virtual ErrCode GetCapability(
        const std::string& featureName, const std::string& capabilityName, void** outFuncPtr) = 0;
    virtual ErrCode UnloadModule(const std::string& featureName) = 0;
    virtual ErrCode Destroy() = 0;
    virtual bool IsInitialized() const = 0;

protected:
    ExtraModulesManager() = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ExtraModulesManager);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EXTRA_MODULES_EXTRA_MODULES_MANAGER_H