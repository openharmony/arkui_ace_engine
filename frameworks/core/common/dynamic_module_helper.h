/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "compatible/components/component_loader.h"

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/dynamic_module.h"

namespace OHOS::Ace {

using ComponentLoaderFunc = ComponentLoader* (*)(const char* name);
using DynamicModuleCreateFunc = DynamicModule* (*)();

constexpr const char* COMPATIABLE_COMPONENT_LOADER = "OHOS_ACE_Compatible_GetLoader";
constexpr const char* DYNAMIC_MODULE_CREATE = "OHOS_ACE_DynamicModule_Create";

class ACE_FORCE_EXPORT DynamicModuleHelper final {
public:
    static DynamicModuleHelper& GetInstance();
    std::unique_ptr<ComponentLoader> GetLoaderByName(const char* name);
    DynamicModule* GetDynamicModule(const std::string& name);

private:
    DynamicModuleHelper() = default;
    ~DynamicModuleHelper() = default;

    ComponentLoaderFunc compatibleLoaderFunc_ = nullptr;
    std::unordered_map<std::string, std::unique_ptr<DynamicModule>> moduleMap_;
    std::mutex moduleMapMutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_DYNAMIC_MODULE_HELPER_H