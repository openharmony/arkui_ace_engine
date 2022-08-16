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

#include "library_loader.h"

#include "hilog_wrapper.h"

#if defined(UNIX_PLATFORM)
#include <dlfcn.h>
#elif defined(WINDOWS_PLATFORM)
#include <windows.h>
#else
#error "Unsupported platform"
#endif

#include <string>

namespace OHOS::Ace::Framework {
#ifdef WINDOWS_PLATFORM
void* Load(std::string_view libraryName)
{
    HMODULE module = LoadLibrary(libraryName.data());
    void* handle = reinterpret_cast<void*>(module);
    if (handle != nullptr) {
        return handle;
    }

    LOGE("Failed to open %{public}s, reason:%{public}sn", libraryName.data(),
        std::to_string(GetLastError()).c_str());
    return nullptr;
}

void* ResolveSymbol(void* handle, std::string_view symbol)
{
    HMODULE module = reinterpret_cast<HMODULE>(handle);
    void* addr = reinterpret_cast<void*>(GetProcAddress(module, symbol.data()));
    if (addr != nullptr) {
        return addr;
    }
    LOGE("Failed to get symbol:%{public}s, reason:%{public}s", symbol.data(),
        std::to_string(GetLastError()).c_str());
    return nullptr;
}

void CloseHandle(void* handle)
{
    if (handle != nullptr) {
        FreeLibrary(reinterpret_cast<HMODULE>(handle));
    }
}
#else // UNIX_PLATFORM
void* Load(std::string_view libraryName)
{
    void* handle = dlopen(libraryName.data(), RTLD_LAZY);
    if (handle != nullptr) {
        return handle;
    }
    LOGE("Failed to open %{public}s, reason:%{public}sn", libraryName.data(), dlerror());
    return nullptr;
}

void* ResolveSymbol(void* handle, std::string_view symbol)
{
    void* addr = dlsym(handle, symbol.data());
    if (addr != nullptr) {
        return addr;
    }
    LOGE("Failed to get symbol:%{public}s, reason:%{public}sn", symbol.data(), dlerror());
    return nullptr;
}

void CloseHandle(void* handle)
{
    if (handle != nullptr) {
        dlclose(handle);
    }
}
#endif
}