/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "drawable_bridge.h"

#include <memory>
#ifdef WINDOWS_PLATFORM
#include <windows.h>
#include <winsock2.h>
#else
#include <dlfcn.h>
#endif

#include "drawable_log.h"

#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "application_context.h"
#endif

namespace OHOS::Ace {
namespace {
#if defined(WINDOWS_PLATFORM)
constexpr char LIBACE_MODULE[] = "ace_compatible.dll";
#elif defined(MAC_PLATFORM)
constexpr char LIBACE_MODULE[] = "libace_compatible.dylib";
#elif defined(LINUX_PLATFORM)
constexpr char LIBACE_MODULE[] = "libace_compatible.so";
#else
constexpr char LIBACE_MODULE[] = "libace_compatible.z.so";
#endif
constexpr char PARSE_RESOURCE_OBJECT[] = "OHOS_ACE_ParseResourceObject";
constexpr char PARSE_DIMENSION_TO_PX[] = "OHOS_ACE_ParseDimensionToPx";

using ParseObjectFunc = void* (*)(void* object);
using GetArkUIDrawableDescriptorFunc = const ArkUIDrawableDescriptor* (*)();
using ParseDimensionFunc = int32_t (*)(void* value);

class LibraryHandle {
public:
    explicit LibraryHandle(void* handle) : handle_(handle) {}

    ~LibraryHandle()
    {
        if (handle_) {
#ifdef WINDOWS_PLATFORM
            FreeLibrary((HMODULE)handle_);
#else
            dlclose(handle_);
#endif
        }
    }

    void* Get() const
    {
        return handle_;
    }

    explicit operator bool() const
    {
        return handle_ != nullptr;
    }

private:
    void* handle_;
};

std::unique_ptr<LibraryHandle> LoadLibraryInternal(const char* libraryName)
{
#ifdef WINDOWS_PLATFORM
    HMODULE handle = LoadLibrary(libraryName);
#else
    void* handle = dlopen(libraryName, RTLD_LAZY | RTLD_LOCAL);
#endif

    if (!handle) {
        return nullptr;
    }

    return std::make_unique<LibraryHandle>(handle);
}

template<typename FuncType>
FuncType GetFunctionInternal(const std::unique_ptr<LibraryHandle>& library, const char* funcName)
{
    if (!library || !library->Get()) {
        return nullptr;
    }

#ifdef WINDOWS_PLATFORM
    return reinterpret_cast<FuncType>(GetProcAddress((HMODULE)library->Get(), funcName));
#else
    return reinterpret_cast<FuncType>(dlsym(library->Get(), funcName));
#endif
}

template<typename FuncType>
FuncType GetAceFunction(const char* funcName)
{
    auto library = LoadLibraryInternal(LIBACE_MODULE);
    if (!library) {
        return nullptr;
    }
    return GetFunctionInternal<FuncType>(library, funcName);
}

} // namespace

void* ParseResourceObject(void* value)
{
    auto entry = GetAceFunction<ParseObjectFunc>(PARSE_RESOURCE_OBJECT);
    return entry ? entry(value) : nullptr;
}

int32_t ParseDimensionToPx(void* value)
{
    auto entry = GetAceFunction<ParseDimensionFunc>(PARSE_DIMENSION_TO_PX);
    return entry ? entry(value) : 0;
}

std::shared_ptr<Global::Resource::ResourceManager> GetResourceManager()
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    std::shared_ptr<AbilityRuntime::Platform::ApplicationContext> applicationContext =
        AbilityRuntime::Platform::ApplicationContext::GetInstance();
    if (!applicationContext) {
        HILOGE("Failed to get applicationContext!");
        return nullptr;
    }
    auto resMgr = applicationContext->GetResourceManager();
    if (!resMgr) {
        HILOGE("Failed to get resource manager!");
    }
    return resMgr;
#else
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
    return resMgr;
#endif
}

const ArkUIDrawableDescriptor* GetArkUIDrawableModifier()
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    return GetArkUIDrawableDescriptor();
#else
#ifdef WINDOWS_PLATFORM
    static HMODULE handle = nullptr;
#else
    static void* handle = nullptr;
#endif
    static void* drawable = nullptr;
    static bool initialized = false;
    if (!initialized) {
#ifdef WINDOWS_PLATFORM
        handle = LoadLibrary(LIBACE_MODULE);
        if (handle != nullptr) {
            drawable = (void*)GetProcAddress(handle, DRAWABLE_FUNC_NAME);
            initialized = true;
        }
#else
        handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
        if (handle != nullptr) {
            drawable = dlsym(handle, DRAWABLE_FUNC_NAME);
            initialized = true;
        }
#endif
    }
    if (handle == nullptr) {
        return nullptr;
    }
    auto entry = reinterpret_cast<GetArkUIDrawableDescriptorFunc>(drawable);
    if (entry == nullptr) {
        return nullptr;
    }
    const auto* result = entry();
    return result;
#endif
}
} // namespace OHOS::Ace