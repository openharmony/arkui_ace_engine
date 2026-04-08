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

#include "smart_layout_engine_loader.h"

#ifndef WINDOWS_PLATFORM
#include <dlfcn.h>
#endif

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

namespace {
const std::string SMART_LAYOUT_SO = "libsmartlayout.z.so";
const std::string CREATE_FUNC_NAME = "CreateSmartLayoutEngine";
} // namespace

SmartLayoutEngineLoader& SmartLayoutEngineLoader::GetInstance()
{
    static SmartLayoutEngineLoader instance;
    return instance;
}

ISmartLayoutEngine* SmartLayoutEngineLoader::GetEngine()
{
#ifndef WINDOWS_PLATFORM
    if (loadAttempted_.load(std::memory_order_acquire)) {
        return engine_;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    if (loadAttempted_.load(std::memory_order_relaxed)) {
        return engine_;
    }

    if (LoadEngine()) {
        loadAttempted_.store(true, std::memory_order_release);
    }
    return engine_;
#else
    return nullptr;
#endif
}

bool SmartLayoutEngineLoader::IsEngineAvailable() const
{
    return engine_ != nullptr;
}

#ifndef WINDOWS_PLATFORM
bool SmartLayoutEngineLoader::LoadEngine()
{
    soHandle_ = dlopen(SMART_LAYOUT_SO.c_str(), RTLD_LAZY);
    if (soHandle_ == nullptr) {
        LOGW("SmartLayoutEngineLoader: Failed to load %{public}s: %{public}s",
             SMART_LAYOUT_SO.c_str(), dlerror());
        return false;
    }

    auto createFunc = reinterpret_cast<SmartLayoutEngineCreateFunc>(
        dlsym(soHandle_, CREATE_FUNC_NAME.c_str()));
    if (createFunc == nullptr) {
        LOGW("SmartLayoutEngineLoader: Failed to find symbol %{public}s: %{public}s",
             CREATE_FUNC_NAME.c_str(), dlerror());
        dlclose(soHandle_);
        soHandle_ = nullptr;
        return false;
    }

    engine_ = createFunc();
    if (engine_ == nullptr) {
        LOGW("SmartLayoutEngineLoader: CreateSmartLayoutEngine returned nullptr");
        dlclose(soHandle_);
        soHandle_ = nullptr;
        return false;
    }

    LOGI("SmartLayoutEngineLoader: Engine loaded successfully");
    return true;
}
#endif

SmartLayoutEngineLoader::~SmartLayoutEngineLoader()
{
#ifndef WINDOWS_PLATFORM
    if (engine_ != nullptr) {
        delete engine_;
        engine_ = nullptr;
    }
    if (soHandle_ != nullptr) {
        dlclose(soHandle_);
        soHandle_ = nullptr;
    }
#endif
}

} // namespace OHOS::Ace::NG