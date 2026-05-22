/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
#include <set>
#include <string>

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
#include <vector>
#endif

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
enum class InstanceIdGenReason : uint32_t {
    SCOPE = 0,
    ACTIVE,
    DEFAULT,
    SINGLETON,
    FOREGROUND,
    UNDEFINED,
    LOCAL,
};

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING

struct CurrentIdStackFrame;
enum class CurrentIdSourceType : int32_t {
    RAII_SCOPE = 0,
    JS_FRONTEND = 1,
    NATIVE_INTERFACE = 2,
    ANI_INTERFACE = 3,
    CANGJIE_FRONTEND = 4,
    CONTAINER_INDIRECT = 5,
};

enum class ContainerScopeLogLevel : int32_t {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
};
#endif

class ACE_EXPORT ContainerScope final {
public:
    using ReportScopeErrorFun = void (*)();
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
    using ContainerScopeLogCallback = void (*)(ContainerScopeLogLevel level, const char* message);
#endif
    using CheckRunOnUIThreadFunc = bool (*)(int32_t, bool);
    template<typename T>
    explicit ContainerScope(T) = delete;

    explicit ContainerScope(int32_t id);
    ContainerScope(int32_t id, bool enable);
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
    explicit ContainerScope(int32_t id, const char* fileId, int32_t line = 0);
    ContainerScope(int32_t id, bool enable, const char* fileId, int32_t line = 0);
#endif
    ~ContainerScope();

    static int32_t CurrentId();
    static int32_t CurrentLocalId();
    static int32_t DefaultId();
    static int32_t SingletonId();
    static int32_t RecentActiveId();
    static int32_t RecentForegroundId();
    static int32_t SafelyId(bool checkThread = true);
    static std::pair<int32_t, InstanceIdGenReason> CurrentIdWithReason(bool checkThread = true);

    // Convert InstanceIdGenReason enum to human-readable description
    static const std::string ReasonToDescription(InstanceIdGenReason reason);
    static const std::set<int32_t> GetAllUIContexts();

    static void Add(int32_t id);
    static void Remove(int32_t id);
    static void RemoveAndCheck(int32_t id);

    static uint32_t ContainerCount();

    static void UpdateCurrent(int32_t id);
    static void UpdateLocalCurrent(int32_t id);
    static void UpdateSingleton(int32_t id);
    static void UpdateRecentActive(int32_t id);
    static void UpdateRecentForeground(int32_t id);
    static void RegisterThreadCheckFunc(CheckRunOnUIThreadFunc checkFunc);
    static void CheckIdChange(int32_t id);

    // Isolated thread management for dc/card scenarios.
    // In these scenarios, each thread maintains its own local container set to avoid
    // cross-thread instance ID confusion. Base query functions (ContainerCount, SingletonId,
    // RecentActiveId, RecentForegroundId, DefaultId) check isIsolatedThread_ internally
    // and return thread-local values when true.
    static void MarkIsolatedThread();
    static void AddLocal(int32_t id);
    static void RemoveLocal(int32_t id);
    static void ResetIsolatedThread();

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
    static uint64_t PushCurrent(int32_t id, const char* fileId, int32_t line, int32_t sourceType);
    static void PopCurrent(uint64_t uid, int32_t restoreId, const char* fileId, int32_t line, int32_t sourceType);

    static std::vector<CurrentIdStackFrame> GetStackHistory();
    static std::vector<CurrentIdStackFrame> GetActiveFrames();
    static void ClearHistory();
    static void EnableTracking(bool enable);
    static bool IsTrackingEnabled();
    static void SetMaxHistorySize(size_t size);
    static bool IsStackBalanced();
    static std::string Diagnose();

    static void SetLogCallback(ContainerScopeLogCallback callback);
    static ContainerScopeLogCallback GetLogCallback();
#endif

#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
    static void* registerHandler_;
    static ReportScopeErrorFun reportScopeError_;
    static void ReportScopeError();
#endif
private:
    int32_t restoreId_ = CurrentId();
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
    uint64_t pushedUid_ = 0;
    bool pushed_ = false;
#endif
    ACE_DISALLOW_COPY_AND_MOVE(ContainerScope);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_SCOPE_H
