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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_LOADER_H

#include <atomic>
#include <mutex>
#include "engine/smart_layout_engine_interface.h"

namespace OHOS::Ace::NG {

/**
 * @brief SmartLayout engine loader
 *
 * Singleton pattern, encapsulates dlopen/dlsym logic for dynamic loading of libsmartlayout.z.so.
 * Loads the so on first GetEngine() call, returns cached interface pointer on subsequent calls.
 * Returns nullptr on load failure, caller should silently fall back to original layout.
 */
class SmartLayoutEngineLoader {
public:
    /**
     * @brief Get singleton instance
     * @return Reference to loader singleton
     */
    static SmartLayoutEngineLoader& GetInstance();

    /**
     * @brief Get engine interface
     * @return Engine interface pointer, nullptr if load failed
     *
     * Performs dlopen on first call, returns cached pointer on subsequent calls.
     * Uses double-checked locking for thread safety.
     */
    ISmartLayoutEngine* GetEngine();

    /**
     * @brief Check if engine is available
     * @return true if engine is successfully loaded
     */
    bool IsEngineAvailable() const;

private:
    SmartLayoutEngineLoader() = default;
    ~SmartLayoutEngineLoader();

    SmartLayoutEngineLoader(const SmartLayoutEngineLoader&) = delete;
    SmartLayoutEngineLoader& operator=(const SmartLayoutEngineLoader&) = delete;

#ifndef WINDOWS_PLATFORM
    /**
     * @brief Perform so loading
     * @return true if load succeeded
     */
    bool LoadEngine();
#endif

    std::mutex mutex_;
#ifndef WINDOWS_PLATFORM
    void* soHandle_ = nullptr;
#endif
    ISmartLayoutEngine* engine_ = nullptr;
    std::atomic<bool> loadAttempted_ {false};
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_LOADER_H