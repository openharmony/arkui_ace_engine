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
constexpr char CREATE_DRAWABLE[] = "OHOS_ACE_CreateDrawableDescriptorByType";
constexpr char GET_PIXELMAP[] = "OHOS_ACE_DrawableDescriptor_GetPixelMap";
constexpr char PARSE_RESOURCE_OBJECT[] = "OHOS_ACE_ParseResourceObject";
constexpr char ANIMATED_GET_CONTROLLER[] = "OHOS_ACE_AnimatedDrawableDescriptor_GetAnimationController";
constexpr char ANIMATED_SET_PIXELMAP_LIST[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetPixelMapList";
constexpr char ANIMATED_SET_PATH[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetPath";
constexpr char ANIMATED_LOAD_SYNC[] = "OHOS_ACE_AnimatedDrawableDescriptorLoadSync";
constexpr char ANIMATED_SET_RESORUCE[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetResource";
constexpr char ANIMATED_SET_TOTAL_DRURATION[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetTotalDuration";
constexpr char ANIMATED_SET_DURATIONS[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetDurations";
constexpr char ANIMATED_SET_ITERATIONS[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetIterations";
constexpr char ANIMATED_SET_AUTOPLAY[] = "OHOS_ACE_AnimatedDrawableDescriptor_SetAutoPlay";
constexpr char ANIMATED_START[] = "OHOS_ACE_AnimationController_Start";
constexpr char ANIMATED_PAUSE[] = "OHOS_ACE_AnimationController_Pause";
constexpr char ANIMATED_STOP[] = "OHOS_ACE_AnimationController_Stop";
constexpr char ANIMATED_RESUME[] = "OHOS_ACE_AnimationController_Resume";
constexpr char ANIMATED_GET_STATUS[] = "OHOS_ACE_AnimationController_GetStatus";
constexpr char INCREASE_REFCOUNT_DRAWABLE[] = "OHOS_ACE_IncreaseRefDrawableDescriptor";
constexpr char DECREASE_REFCOUNT_DRAWABLE[] = "OHOS_ACE_DecreaseRefDrawableDescriptor";

using CreateDrawableFunc = void* (*)(uint32_t type);
using GetControllerFunc = void* (*)(void* object, const char*);
using ParseObjectFunc = void* (*)(void* object);
using GetStatusFunc = int32_t (*)(void* object);
using GetPixelMapFunc = void (*)(void* object, std::shared_ptr<Media::PixelMap>& pixelmap);
using SetPixelMapListFunc = void (*)(void* object, std::vector<void*> pixelMaps);
using SetPathFunc = void (*)(void* object, const char* path);
using SetResourceFunc = void (*)(void* object, void* resource);
using SetTotalDurationFunc = void (*)(void* object, int32_t duration);
using SetIterationsFunc = void (*)(void* object, int32_t iteration);
using SetDurationsFunc = void (*)(void* object, const std::vector<int32_t>& durations);
using SetAutoPlayFunc = void (*)(void* object, bool autoPlay);
using ObjectFunc = void (*)(void* object);
using LoadSyncFunc = void (*)(void* object, int32_t& width, int32_t& height, int32_t& errorCode);

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

void* CreateDrawableC(uint32_t type)
{
    auto entry = GetAceFunction<CreateDrawableFunc>(CREATE_DRAWABLE);
    return entry ? entry(type) : nullptr;
}

void GetPixelMapC(void* object, std::shared_ptr<Media::PixelMap>& pixelmap)
{
    if (auto entry = GetAceFunction<GetPixelMapFunc>(GET_PIXELMAP)) {
        entry(object, pixelmap);
    }
}

void* ParseResourceObject(void* value)
{
    auto entry = GetAceFunction<ParseObjectFunc>(PARSE_RESOURCE_OBJECT);
    return entry ? entry(value) : nullptr;
}

int32_t AnimatedGetStatusC(void* object)
{
    if (auto entry = GetAceFunction<GetStatusFunc>(ANIMATED_GET_STATUS)) {
        return entry(object);
    }
    return -1;
}

void* AnimatedGetController(void* object, const char* id)
{
    if (auto entry = GetAceFunction<GetControllerFunc>(ANIMATED_GET_CONTROLLER)) {
        return entry(object, id);
    }
    return nullptr;
}

void AnimatedLoadSync(void* object, int32_t& width, int32_t& height, int32_t& errorCode)
{
    if (auto entry = GetAceFunction<LoadSyncFunc>(ANIMATED_LOAD_SYNC)) {
        entry(object, width, height, errorCode);
    }
}

void AnimatedSetPixelMapListC(void* object, std::vector<void*> pixelMaps)
{
    if (auto entry = GetAceFunction<SetPixelMapListFunc>(ANIMATED_SET_PIXELMAP_LIST)) {
        entry(object, pixelMaps);
    }
}

void AnimatedSetPath(void* object, const char* path)
{
    if (auto entry = GetAceFunction<SetPathFunc>(ANIMATED_SET_PATH)) {
        entry(object, path);
    }
}

void AnimatedSetResource(void* object, void* resource)
{
    if (auto entry = GetAceFunction<SetResourceFunc>(ANIMATED_SET_RESORUCE)) {
        entry(object, resource);
    }
}

void AnimatedSetTotalDurationC(void* object, int32_t duration)
{
    if (auto entry = GetAceFunction<SetTotalDurationFunc>(ANIMATED_SET_TOTAL_DRURATION)) {
        entry(object, duration);
    }
}

void AnimatedSetDurationsC(void* object, const std::vector<int32_t>& durations)
{
    if (auto entry = GetAceFunction<SetDurationsFunc>(ANIMATED_SET_DURATIONS)) {
        entry(object, durations);
    }
}

void AnimatedSetIterationsC(void* object, int32_t iteration)
{
    if (auto entry = GetAceFunction<SetIterationsFunc>(ANIMATED_SET_ITERATIONS)) {
        entry(object, iteration);
    }
}

void AnimatedSetAutoPlayC(void* object, bool autoPlay)
{
    if (auto entry = GetAceFunction<SetAutoPlayFunc>(ANIMATED_SET_AUTOPLAY)) {
        entry(object, autoPlay);
    }
}

void AnimatedStartC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(ANIMATED_START)) {
        entry(object);
    }
}

void AnimatedStopC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(ANIMATED_STOP)) {
        entry(object);
    }
}

void AnimatedPauseC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(ANIMATED_PAUSE)) {
        entry(object);
    }
}

void AnimatedResumeC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(ANIMATED_RESUME)) {
        entry(object);
    }
}

void IncreaseRefCountDrawableC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(INCREASE_REFCOUNT_DRAWABLE)) {
        entry(object);
    }
}

void DecreaseRefCountDrawableC(void* object)
{
    if (auto entry = GetAceFunction<ObjectFunc>(DECREASE_REFCOUNT_DRAWABLE)) {
        entry(object);
    }
}
} // namespace OHOS::Ace