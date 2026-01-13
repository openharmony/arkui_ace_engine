/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

#include "native_engine/native_engine.h"

extern "C" void* OHOS_MEDIA_GetPixelMap(napi_env env, napi_value value);

namespace OHOS::Ace::Framework {

void JsEngine::RunNativeEngineLoop()
{
    static bool hasPendingExpection = false;
    if (nativeEngine_ && !hasPendingExpection) {
        hasPendingExpection = nativeEngine_->HasPendingException();
        nativeEngine_->Loop(LOOP_NOWAIT, false);
    }
}

#if !defined(PREVIEW)
PixelMapNapiEntry JsEngine::GetPixelMapNapiEntry()
{
#if defined(IOS_PLATFORM) || defined(ANDROID_PLATFORM)
    return reinterpret_cast<PixelMapNapiEntry>(&OHOS_MEDIA_GetPixelMap);
#else
    static PixelMapNapiEntry pixelMapNapiEntry_ = nullptr;
    if (!pixelMapNapiEntry_) {
#if defined(_ARM64_) || defined(SIMULATOR_64)
        std::string prefix = "/system/lib64/module/";
#else
        std::string prefix = "/system/lib/module/";
#endif
#ifdef OHOS_STANDARD_SYSTEM
        std::string napiPluginName = "multimedia/libimage.z.so";
#else
        std::string napiPluginName = "multimedia/libimage_napi.z.so";
#endif
        auto napiPluginPath = prefix.append(napiPluginName);
        void* handle = dlopen(napiPluginPath.c_str(), RTLD_LAZY);
        if (handle == nullptr) {
            LOGE("Failed to open shared library %{public}s, reason: %{public}s", napiPluginPath.c_str(), dlerror());
            return nullptr;
        }
        pixelMapNapiEntry_ = reinterpret_cast<PixelMapNapiEntry>(dlsym(handle, "OHOS_MEDIA_GetPixelMap"));
        if (pixelMapNapiEntry_ == nullptr) {
            dlclose(handle);
            LOGE("Failed to get symbol OHOS_MEDIA_GetPixelMap in %{public}s", napiPluginPath.c_str());
            return nullptr;
        }
    }
    return pixelMapNapiEntry_;
#endif
}
#endif

bool JsEngine::IsLayoutChildrenCallbackFuncExist(const std::string& componentId)
{
    auto iter = layoutChildrenEvents_.find(componentId);
    if (iter == layoutChildrenEvents_.end()) {
        return false;
    }
    for (auto& f : iter->second) {
        if (f && f->HasCallback()) {
            return true;
        }
    }
    return false;
}

void JsEngine::LayoutChildrenInspectorCallback(const std::string& componentId)
{
    auto iter = layoutChildrenEvents_.find(componentId);
    if (iter != layoutChildrenEvents_.end()) {
        auto events = iter->second;
        for (auto&& observer : events) {
            (*observer)();
        }
    }
}

void JsEngine::LayoutInspectorCallback(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutEvents_.find(uniqueId);
    if (iter != uniqueIdLayoutEvents_.end()) {
        for (auto&& observer : iter->second) {
            (*observer)();
        }
    }
}

void JsEngine::DrawInspectorCallback(int32_t uniqueId)
{
    auto iter = uniqueIdDrawEvents_.find(uniqueId);
    if (iter != uniqueIdDrawEvents_.end()) {
        for (auto&& observer : iter->second) {
            (*observer)();
        }
    }
}

void JsEngine::DrawChildrenInspectorCallback(int32_t uniqueId)
{
    auto iter = uniqueIdDrawChildrenEvents_.find(uniqueId);
    if (iter != uniqueIdDrawChildrenEvents_.end()) {
        auto events = iter->second;
        for (auto&& observer : events) {
            (*observer)();
        }
    }
}

void JsEngine::LayoutChildrenInspectorCallback(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutChildrenEvents_.find(uniqueId);
    if (iter != uniqueIdLayoutChildrenEvents_.end()) {
        auto events = iter->second;
        for (auto&& observer : events) {
            (*observer)();
        }
    }
}

void JsEngine::RegisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenEvent, const std::string& componentId)
{
    if (layoutChildrenEvent) {
        layoutChildrenEvents_[componentId].emplace(layoutChildrenEvent);
    }
}

void JsEngine::UnregisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenEvent, const std::string& componentId)
{
    // if layoutChildrenEvent is undefine, remove all
    if (!layoutChildrenEvent) {
        return;
    }
    auto iter = layoutChildrenEvents_.find(componentId);
    if (iter != layoutChildrenEvents_.end()) {
        iter->second.erase(layoutChildrenEvent);
        if (iter->second.empty()) {
            layoutChildrenEvents_.erase(componentId);
        }
    }
}

void JsEngine::RegisterLayoutInspectorCallback(const RefPtr<InspectorEvent>& layoutEvent, int32_t uniqueId)
{
    uniqueIdLayoutEvents_[uniqueId].emplace(layoutEvent);
}

void JsEngine::UnregisterLayoutInspectorCallback(const RefPtr<InspectorEvent>& layoutEvent, int32_t uniqueId)
{
    auto iter = uniqueIdLayoutEvents_.find(uniqueId);
    if (iter != uniqueIdLayoutEvents_.end()) {
        iter->second.erase(layoutEvent);
        if (iter->second.empty()) {
            uniqueIdLayoutEvents_.erase(uniqueId);
        }
    }
}

void JsEngine::RegisterDrawInspectorCallback(const RefPtr<InspectorEvent>& drawEvent, int32_t uniqueId)
{
    uniqueIdDrawEvents_[uniqueId].emplace(drawEvent);
}

void JsEngine::UnregisterDrawInspectorCallback(const RefPtr<InspectorEvent>& drawEvent, int32_t uniqueId)
{
    auto iter = uniqueIdDrawEvents_.find(uniqueId);
    if (iter != uniqueIdDrawEvents_.end()) {
        iter->second.erase(drawEvent);
        if (iter->second.empty()) {
            uniqueIdDrawEvents_.erase(uniqueId);
        }
    }
}

void JsEngine::RegisterDrawChildrenInspectorCallback(const RefPtr<InspectorEvent>& drawChildrenEvent, int32_t uniqueId)
{
    if (drawChildrenEvent) {
        uniqueIdDrawChildrenEvents_[uniqueId].emplace(drawChildrenEvent);
    }
}

void JsEngine::UnregisterDrawChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& drawChildrenEvent, int32_t uniqueId)
{
    if (!drawChildrenEvent) {
        return;
    }
    auto iter = uniqueIdDrawChildrenEvents_.find(uniqueId);
    if (iter != uniqueIdDrawChildrenEvents_.end()) {
        iter->second.erase(drawChildrenEvent);
        if (iter->second.empty()) {
            uniqueIdDrawChildrenEvents_.erase(uniqueId);
        }
    }
}

void JsEngine::RegisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenEvent, int32_t uniqueId)
{
    if (layoutChildrenEvent) {
        uniqueIdLayoutChildrenEvents_[uniqueId].emplace(layoutChildrenEvent);
    }
}

void JsEngine::UnregisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenEvent, int32_t uniqueId)
{
    if (!layoutChildrenEvent) {
        return;
    }
    auto iter = uniqueIdLayoutChildrenEvents_.find(uniqueId);
    if (iter != uniqueIdLayoutChildrenEvents_.end()) {
        iter->second.erase(layoutChildrenEvent);
        if (iter->second.empty()) {
            uniqueIdLayoutChildrenEvents_.erase(uniqueId);
        }
    }
}

bool JsEngine::IsLayoutCallBackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutEvents_.find(uniqueId);
    if (iter == uniqueIdLayoutEvents_.end()) {
        return false;
    }
    for (auto& f : iter->second) {
        if (f && f->HasCallback()) {
            return true;
        }
    }
    return false;
}

bool JsEngine::IsDrawCallBackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdDrawEvents_.find(uniqueId);
    if (iter == uniqueIdDrawEvents_.end()) {
        return false;
    }
    for (auto& f : iter->second) {
        if (f && f->HasCallback()) {
            return true;
        }
    }
    return false;
}

bool JsEngine::IsDrawChildrenCallbackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdDrawChildrenEvents_.find(uniqueId);
    if (iter == uniqueIdDrawChildrenEvents_.end()) {
        return false;
    }
    for (auto& f : iter->second) {
        if (f && f->HasCallback()) {
            return true;
        }
    }
    return false;
}

bool JsEngine::IsLayoutChildrenCallbackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutChildrenEvents_.find(uniqueId);
    if (iter == uniqueIdLayoutChildrenEvents_.end()) {
        return false;
    }
    for (auto& f : iter->second) {
        if (f && f->HasCallback()) {
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace::Framework
