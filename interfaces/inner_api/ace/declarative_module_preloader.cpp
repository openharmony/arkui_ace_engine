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

namespace OHOS::Ace {

#if defined(WINDOWS_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.dll";
#elif defined(MAC_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.dylib";
#elif defined(LINUX_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.so";
#else
constexpr char ACE_LIB_NAME[] = "libace.z.so";
#endif

using CreateFunc = void (*)(void*);
constexpr char PRE_INIT_ACE_MODULE_FUNC[] = "OHOS_ACE_PreloadAceModule";

void InitAceModule(void* runtime)
{
    LIBHANDLE handle = LOADLIB(ACE_LIB_NAME);
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
using CreateFuncCard = void (*)(void*, const char*);
constexpr char PRE_INIT_ACE_MODULE_FUNC_CARD[] = "OHOS_ACE_PreloadAceModuleCard";
constexpr char RELOAD_ACE_MODULE_FUNC_CARD[] = "OHOS_ACE_ReloadAceModuleCard";

void InitAceModuleCard(void* runtime, const char* bundleName)
{
    LIBHANDLE handle = LOADLIB(ACE_LIB_NAME);
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFuncCard>(LOADSYM(handle, PRE_INIT_ACE_MODULE_FUNC_CARD));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime, bundleName);
}

void DeclarativeModulePreloader::PreloadCard(NativeEngine& runtime, const std::string &bundleName)
{
    InitAceModuleCard(reinterpret_cast<void*>(&runtime), bundleName.c_str());
}

void ReloadAceModuleCard(void* runtime, const char* bundleName)
{
    LIBHANDLE handle = LOADLIB(ACE_LIB_NAME);
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFuncCard>(LOADSYM(handle, RELOAD_ACE_MODULE_FUNC_CARD));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime, bundleName);
}

void DeclarativeModulePreloader::ReloadCard(NativeEngine& runtime, const std::string &bundleName)
{
    ReloadAceModuleCard(reinterpret_cast<void*>(&runtime), bundleName.c_str());
}
// ArkTsCard end
} // namespace OHOS::Ace
