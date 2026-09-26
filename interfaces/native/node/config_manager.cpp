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

#include <array>
#include <atomic>

#include "node_model.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NodeModel::ConfigManager {
namespace {
constexpr char UI_THREAD_CHECK_NAME[] = "UI_THREAD";
constexpr char UI_THREAD_CHECK_REASON[] = "C API must be called on the UI thread";
constexpr char NODE_DISPOSED_CHECK_NAME[] = "NODE_DISPOSED";
constexpr char NODE_DISPOSED_DEFAULT_REASON[] = "Node has been disposed";
constexpr const char* DEFAULT_DEBUG_CRASH_HINT =
    "; This crash is enabled by default in debug builds. To disable it, call "
    "OH_ArkUI_NativeModule_SetRuntimeCheckMode. "
    "For guidance on fixing this issue, visit the official developer website.";

struct EffectiveMode {
    CheckMode mode;
    bool isDefault;
};

class RuntimeCheckManager final {
public:
    RuntimeCheckManager()
    {
        for (auto& mode : configuredModes_) {
            mode.store(UNCONFIGURED, std::memory_order_relaxed);
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
        if (!IsCurrentThreadSafe()) {
            LOGF_ABORT("OH_ArkUI_NativeModule_SetRuntimeCheckMode must be called on the UI thread");
        }
        if (!IsValidCheckType(checkType) || !IsValidMode(mode)) {
            return false;
        }

        const auto index = static_cast<uint32_t>(checkType);
        // UI-thread writes may overlap checks on worker threads. The mode publishes no other data.
        // Default resolution never overwrites the configured mode.
        configuredModes_[index].store(mode, std::memory_order_relaxed);
        return true;
    }

    EffectiveMode GetEffectiveMode(CheckType type) const
    {
        const auto index = static_cast<uint32_t>(type);
        if (index >= CHECK_TYPE_COUNT) {
            return { CheckMode::DISABLED, false };
        }
        auto mode = configuredModes_[index].load(std::memory_order_relaxed);
        if (mode != UNCONFIGURED) {
            return { static_cast<CheckMode>(mode), false };
        }

        const bool isDebug = ReadDebugBuild();
        // A configuration made while resolving the backend takes precedence over the default.
        mode = configuredModes_[index].load(std::memory_order_relaxed);
        if (mode != UNCONFIGURED) {
            return { static_cast<CheckMode>(mode), false };
        }
        return { ResolveCheckMode(type, isDebug), true };
    }

    void CheckUIThread(const char* publicApiName) const
    {
        const auto effective = GetEffectiveMode(CheckType::UI_THREAD);
        if (effective.mode == CheckMode::DISABLED || IsCurrentThreadSafe()) {
            return;
        }
        EmitDiagnosis(UI_THREAD_CHECK_NAME, publicApiName, UI_THREAD_CHECK_REASON, effective);
    }

    void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage) const
    {
        const auto effective = GetEffectiveMode(CheckType::NODE_DISPOSED);
        if (effective.mode == CheckMode::DISABLED ||
            nodePtr == nullptr || nodePtr->magic == ARKUI_NODE_MAGIC_VALID) {
            return;
        }
        EmitDiagnosis(NODE_DISPOSED_CHECK_NAME, apiName,
            (errorMessage != nullptr) ? errorMessage : NODE_DISPOSED_DEFAULT_REASON, effective);
    }

    bool IsCurrentThreadSafe() const
    {
        const auto* impl = GetBasicAPI();
        // Without the bridge there is no container/pipeline context either: treated as safe.
        return impl == nullptr || impl->isCurrentThreadSafe == nullptr || impl->isCurrentThreadSafe();
    }

private:
    static constexpr uint32_t CHECK_TYPE_COUNT = static_cast<uint32_t>(CheckType::COUNT);
    // An unconfigured check follows the application build type, cached only after initialization.
    static constexpr int32_t UNCONFIGURED = -1;
    static constexpr int32_t DEBUG_UNRESOLVED = -1;

    static bool IsValidCheckType(int32_t checkType)
    {
        return checkType >= 0 && static_cast<uint32_t>(checkType) < CHECK_TYPE_COUNT;
    }

    static bool IsValidMode(int32_t mode)
    {
        return mode >= static_cast<int32_t>(CheckMode::DISABLED) &&
               mode <= static_cast<int32_t>(CheckMode::CRASH);
    }

    bool ReadDebugBuild() const
    {
        auto debugBuild = cachedDebugBuild_.load(std::memory_order_relaxed);
        if (debugBuild != DEBUG_UNRESOLVED) {
            return debugBuild != 0;
        }

        const auto* impl = GetBasicAPI();
        const bool hasDebugGetter = impl != nullptr && impl->isDebugForParallel != nullptr;
        // Read readiness first so an initialization-time false value is never cached as final.
        const bool isDebugSet =
            hasDebugGetter && impl->isDebugForParallelSet != nullptr && impl->isDebugForParallelSet();
        const bool isDebug = hasDebugGetter && impl->isDebugForParallel();
        if (isDebugSet) {
            // The first ready reader publishes the build type. A delayed reader uses the winner.
            const bool published =
                cachedDebugBuild_.compare_exchange_strong(debugBuild, isDebug ? 1 : 0, std::memory_order_relaxed);
            return published ? isDebug : debugBuild != 0;
        }

        // Another reader may have published a ready value while this reader queried the backend.
        debugBuild = cachedDebugBuild_.load(std::memory_order_relaxed);
        return debugBuild == DEBUG_UNRESOLVED ? isDebug : debugBuild != 0;
    }

    CheckMode ResolveCheckMode(CheckType type, bool isDebug) const
    {
        switch (type) {
            case CheckType::UI_THREAD:
            case CheckType::NODE_DISPOSED:
                return isDebug ? CheckMode::CRASH : CheckMode::DISABLED;
            default:
                return CheckMode::DISABLED;
        }
    }

    void EmitDiagnosis(
        const char* checkName, const char* apiName, const char* reason, const EffectiveMode& effective) const
    {
        const char* api = (apiName != nullptr) ? apiName : "unknown";
        const char* hint = (effective.isDefault && effective.mode == CheckMode::CRASH)
            ? DEFAULT_DEBUG_CRASH_HINT : "";
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
            "ArkUI runtime check hit. checkName: %{public}s, apiName: %{public}s, reason: %{public}s%{public}s",
            checkName, api, reason, hint);
        LogBacktrace();
        if (effective.mode == CheckMode::CRASH) {
            LOGF_ABORT("ArkUI runtime check abort. checkName: %{public}s, apiName: %{public}s, "
                "reason: %{public}s%{public}s",
                checkName, api, reason, hint);
        }
    }

    // Only successful user configuration writes these slots; defaults never do.
    std::array<std::atomic<int32_t>, CHECK_TYPE_COUNT> configuredModes_ {};
    // Shared application build type: unresolved (-1), release (0), or debug (1).
    // Cache it only after the backend reports that application information is ready.
    mutable std::atomic<int32_t> cachedDebugBuild_ { DEBUG_UNRESOLVED };
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

void CheckUIThread(const char* publicApiName)
{
    GetManager().CheckUIThread(publicApiName);
}

void CheckNodeDisposed(ArkUI_NodeHandle nodePtr, const char* apiName, const char* errorMessage)
{
    GetManager().CheckNodeDisposed(nodePtr, apiName, errorMessage);
}

} // namespace OHOS::Ace::NodeModel::ConfigManager
