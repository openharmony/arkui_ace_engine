/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_ACCESSOR_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_ACCESSOR_UTILS_H

#include "arkoala_api_generated.h"
#include "core/event/key_event.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "frameworks/base/utils/string_utils.h"

namespace OHOS::Ace::NG {
class AccessorUtils {
public:
    static bool CheckKeysPressed(const std::vector<std::string>& keysStrs,
        const std::vector<OHOS::Ace::KeyCode>& keysCodes);
    template<typename... Args>
    static void ThrowTSException(int32_t code, const char* format, Args... args);
};

namespace {
#ifdef WINDOWS_PLATFORM
#include <windows.h>
inline void* LoadLibrary(const char* libPath)
{
    return LoadLibraryA(libPath);
}
inline void* FindSymbol(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
inline void* LoadLibrary(const char* libPath)
{
    void* handle = dlopen(libPath, RTLD_LOCAL | RTLD_LAZY);
    if (!handle) {
        return nullptr;
    }
    return handle;
}
inline void* FindSymbol(void* library, const char* name)
{
    return dlsym(library, name);
}
#endif

#ifdef WINDOWS_PLATFORM
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.dll";
#else
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.z.so";
#endif
using AniThrowErrorFunc = void (*)(Ark_VMContext vmContext, int32_t errCode, const std::string& errorMsg);
}

template<typename... Args>
void AccessorUtils::ThrowTSException(int32_t errCode, const char* format, Args... args)
{
    Ark_VMContext vmContext = CallbackHelper<VoidCallback>::GetVMContext();
    if (vmContext == nullptr) {
        LOGE("null env");
        return;
    }
    auto handle = LoadLibrary(LIBARKOALA_MODULE);
    if (handle == nullptr) {
        LOGE("dlopen can't find libArkoalaNative.z.so");
        return;
    }
    auto aniErrorFunc = reinterpret_cast<AniThrowErrorFunc>(FindSymbol(handle, "AniThrowError"));
    if (aniErrorFunc == nullptr) {
        LOGE("dlsym can't find ANI_ThrowError");
        return;
    }
    const std::string errorMsg = StringUtils::FormatString(format, args...);
    aniErrorFunc(vmContext, errCode, errorMsg);
}
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_ACCESSOR_UTILS_H