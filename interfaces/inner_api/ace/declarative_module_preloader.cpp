/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/declarative_module_preloader.h"

#include "utils.h"
#include "ace_forward_compatibility.h"

namespace OHOS::Ace {

using CreateFunc = void (*)(void*);
constexpr char PRE_INIT_ACE_MODULE_FUNC[] = "OHOS_ACE_PreloadAceModule";

void InitAceModule(void* runtime)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFunc>(LOADSYM(handle, PRE_INIT_ACE_MODULE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime);
}

void DeclarativeModulePreloader::Preload(NativeEngine& runtime)
{
    InitAceModule(reinterpret_cast<void*>(&runtime));
}

// ArkTsCard start
using CreateFuncCard = void (*)(void*, const char*, const void*);
constexpr char PRE_INIT_ACE_MODULE_FUNC_CARD[] = "OHOS_ACE_PreloadAceModuleCard";
constexpr char RELOAD_ACE_MODULE_FUNC_CARD[] = "OHOS_ACE_ReloadAceModuleCard";

void InitAceModuleCard(void* runtime, const char* bundleName, const void* hapPathMap)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFuncCard>(LOADSYM(handle, PRE_INIT_ACE_MODULE_FUNC_CARD));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime, bundleName, hapPathMap);
}

void DeclarativeModulePreloader::PreloadCard(NativeEngine& runtime, const std::string& bundleName,
    const std::map<std::string, std::string>& hapPathMap)
{
    InitAceModuleCard(reinterpret_cast<void*>(&runtime), bundleName.c_str(),
        reinterpret_cast<const void*>(&hapPathMap));
}

void ReloadAceModuleCard(void* runtime, const char* bundleName, const void* hapPathMap)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFuncCard>(LOADSYM(handle, RELOAD_ACE_MODULE_FUNC_CARD));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime, bundleName, hapPathMap);
}

void DeclarativeModulePreloader::ReloadCard(NativeEngine& runtime, const std::string &bundleName,
    const std::map<std::string, std::string>& hapPathMap)
{
    ReloadAceModuleCard(reinterpret_cast<void*>(&runtime), bundleName.c_str(),
        reinterpret_cast<const void*>(&hapPathMap));
}
// ArkTsCard end

using CreateFuncWorker = void (*)(void*);
constexpr char PRE_INIT_ACE_MODULE_FUNC_WORKER[] = "OHOS_ACE_PreloadAceModuleWorker";

void InitAceModuleWorker(void* runtime)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFuncWorker>(LOADSYM(handle, PRE_INIT_ACE_MODULE_FUNC_WORKER));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime);
}

void DeclarativeModulePreloader::PreloadWorker(NativeEngine& runtime)
{
    InitAceModuleWorker(reinterpret_cast<void*>(&runtime));
}
} // namespace OHOS::Ace
