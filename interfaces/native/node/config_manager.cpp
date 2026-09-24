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

#include "config_manager.h"

#include <atomic>

#include "base/log/log_wrapper.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "node_model.h"

namespace OHOS::Ace::NodeModel::ConfigManager {
namespace {
// Check type values, kept in sync with OH_ArkUI_NativeModule_RuntimeCheckType (public C API).
constexpr int32_t CHECK_TYPE_UI_THREAD = 0;
constexpr int32_t CHECK_TYPE_NODE_DISPOSED = 1;
constexpr int32_t CHECK_TYPE_COUNT = 2;

// Runtime check mode values, kept in sync with OH_ArkUI_NativeModule_RuntimeCheckMode (public C API).
constexpr int32_t MODE_DISABLED = 0;
constexpr int32_t MODE_LOG = 1;
constexpr int32_t MODE_CRASH = 2;

// An unconfigured check follows the application build type cached at construction.
constexpr int32_t MODE_UNCONFIGURED = -1;

constexpr const char* CHECK_NAME_NODE_DISPOSED = "NODE_DISPOSED";
constexpr const char* DEFAULT_DEBUG_CRASH_HINT =
    "; This crash is enabled by default in debug builds. To disable it, call "
    "OH_ArkUI_NativeModule_SetRuntimeCheckMode. "
    "For guidance on fixing this issue, visit the official developer website.";

struct EffectiveMode {
    int32_t mode;
    bool isDefault;
};

class RuntimeCheckManager final {
public:
    // Application debug information must be initialized before this manager is first used.
    RuntimeCheckManager() : isDebugBuild_(ReadDebugBuild())
    {
        for (int32_t i = 0; i < CHECK_TYPE_COUNT; ++i) {
            configuredModes_[i].store(MODE_UNCONFIGURED, std::memory_order_relaxed);
        }
    }

    static RuntimeCheckManager& GetInstance()
    {
        static RuntimeCheckManager instance;
        return instance;
    }

    bool SetRuntimeCheckMode(int32_t checkType, int32_t mode)
    {
        // The UI thread constraint is checked before parameter validation and is not
        // controlled by any check mode.
        if (!IsUIThread()) {
            LOGF_ABORT("ArkUI runtime check config abort. apiName: OH_ArkUI_NativeModule_SetRuntimeCheckMode, "
                "reason: this function must be called on the UI thread");
        }
        if (!IsValidCheckType(checkType) || !IsValidMode(mode)) {
            return false;
        }
        // UI-thread writes may overlap checks on worker threads. The mode publishes no other data.
        configuredModes_[checkType].store(mode, std::memory_order_relaxed);
        return true;
    }

    EffectiveMode GetEffectiveMode(int32_t checkType) const
    {
        if (!IsValidCheckType(checkType)) {
            return { MODE_DISABLED, false };
        }
        const int32_t configured = configuredModes_[checkType].load(std::memory_order_relaxed);
        if (configured != MODE_UNCONFIGURED) {
            return { configured, false };
        }
        const bool debugDefault = checkType == CHECK_TYPE_NODE_DISPOSED && isDebugBuild_;
        return { debugDefault ? MODE_CRASH : MODE_DISABLED, true };
    }

    void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage)
    {
        const auto effectiveMode = GetEffectiveMode(CHECK_TYPE_NODE_DISPOSED);
        const int32_t mode = effectiveMode.mode;
        if (mode == MODE_DISABLED || nodePtr == nullptr || nodePtr->magic == ARKUI_NODE_MAGIC_VALID) {
            return;
        }
        const char* api = (apiName != nullptr) ? apiName : "unknown";
        const char* reason = (errorMessage != nullptr) ? errorMessage : "Node has been disposed";
        const char* hint = effectiveMode.isDefault && mode == MODE_CRASH ? DEFAULT_DEBUG_CRASH_HINT : "";
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
            "ArkUI runtime check hit. checkName: %{public}s, apiName: %{public}s, reason: %{public}s%{public}s",
            CHECK_NAME_NODE_DISPOSED, api, reason, hint);
        LogBacktrace();
        if (mode == MODE_CRASH) {
            LOGF_ABORT("ArkUI runtime check abort. checkName: %{public}s, apiName: %{public}s, "
                "reason: %{public}s%{public}s",
                CHECK_NAME_NODE_DISPOSED, api, reason, hint);
        }
    }

private:
    static bool IsValidCheckType(int32_t checkType)
    {
        return checkType == CHECK_TYPE_UI_THREAD || checkType == CHECK_TYPE_NODE_DISPOSED;
    }

    static bool IsValidMode(int32_t mode)
    {
        return mode == MODE_DISABLED || mode == MODE_LOG || mode == MODE_CRASH;
    }

    bool IsUIThread() const
    {
        const auto* impl = GetFullImpl();
        // Without the bridge there is no container/pipeline context either: treated as safe.
        return impl == nullptr || impl->getBasicAPI()->isCurrentThreadSafe();
    }

    bool ReadDebugBuild() const
    {
        const auto* impl = GetFullImpl();
        return impl != nullptr && impl->getBasicAPI()->isDebugVersion();
    }

    const bool isDebugBuild_;
    std::atomic<int32_t> configuredModes_[CHECK_TYPE_COUNT];
};

RuntimeCheckManager& GetManager()
{
    return RuntimeCheckManager::GetInstance();
}
} // namespace

bool SetRuntimeCheckMode(int32_t checkType, int32_t mode)
{
    return GetManager().SetRuntimeCheckMode(checkType, mode);
}

void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage)
{
    GetManager().CheckNodeDisposed(nodePtr, apiName, errorMessage);
}

} // namespace OHOS::Ace::NodeModel::ConfigManager
