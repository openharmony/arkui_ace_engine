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

#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
#include <dlfcn.h>
#endif

#include <atomic>
#include <mutex>
#include <set>
#include <shared_mutex>

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
#include <algorithm>
#include <cstdarg>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <deque>
#include <sstream>
#include <unordered_map>

#include "securec.h"

#include "base/utils/container_scope/container_scope_diagnostics.h"
#endif

#include "core/common/container_consts.h"
#include "core/common/container_scope.h"

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
namespace OHOS::Ace {
namespace {
ContainerScope::ContainerScopeLogCallback g_logCallback = nullptr;

void FormatLog(ContainerScopeLogLevel level, const char* fmt, ...)
{
    auto cb = ContainerScope::GetLogCallback();
    if (!cb) {
        return;
    }
    char buf[512];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf_s(buf, sizeof(buf), sizeof(buf) - 1, fmt, args);
    va_end(args);
    if (len < 0) {
        buf[0] = '\0';
    }
    cb(level, buf);
}
} // namespace

void ContainerScope::SetLogCallback(ContainerScopeLogCallback callback)
{
    g_logCallback = callback;
}

ContainerScope::ContainerScopeLogCallback ContainerScope::GetLogCallback()
{
    return g_logCallback;
}
} // namespace OHOS::Ace

#ifndef PRINT_CONTAINER_SCOPED_LOG
#define PRINT_CONTAINER_SCOPED_LOG(level, fmt, ...) \
    OHOS::Ace::FormatLog(OHOS::Ace::ContainerScopeLogLevel::level, "[%d] " fmt, __LINE__, ##__VA_ARGS__)
#endif // PRINT_CONTAINER_SCOPED_LOG

#ifndef CONTAINER_SCOPED_LOGE
#define CONTAINER_SCOPED_LOGE(fmt, ...) PRINT_CONTAINER_SCOPED_LOG(ERROR, fmt, ##__VA_ARGS__)
#define CONTAINER_SCOPED_LOGW(fmt, ...) PRINT_CONTAINER_SCOPED_LOG(WARN, fmt, ##__VA_ARGS__)
#define CONTAINER_SCOPED_LOGI(fmt, ...) PRINT_CONTAINER_SCOPED_LOG(INFO, fmt, ##__VA_ARGS__)
#define CONTAINER_SCOPED_LOGD(fmt, ...) PRINT_CONTAINER_SCOPED_LOG(DEBUG, fmt, ##__VA_ARGS__)
#endif // CONTAINER_SCOPED_LOGE
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

namespace OHOS::Ace {
namespace {
// preview not support multi-instance, always using default instance id 0.
#if defined(PREVIEW)
constexpr int32_t DEFAULT_ID = 0;
#else
constexpr int32_t DEFAULT_ID = INSTANCE_ID_UNDEFINED;
#endif

std::shared_mutex mutex_;
std::set<int32_t> containerSet_;
thread_local int32_t currentLocalId_(DEFAULT_ID);
thread_local int32_t currentId_(DEFAULT_ID);
std::atomic<int32_t> recentActiveId_(DEFAULT_ID);
std::atomic<int32_t> recentForegroundId_(DEFAULT_ID);

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
bool trackingEnabled_ = false;
thread_local size_t maxHistorySize_ = 64;
thread_local uint64_t nextUid_ = 1;
thread_local std::unordered_map<uint64_t, CurrentIdStackFrame> activeStack_;
thread_local std::deque<uint64_t> activeOrder_;
thread_local std::deque<CurrentIdStackFrame> history_;
#endif // ENABLE_CONTAINER_SCOPE_TRACKING
} // namespace

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
void PopCurrentStackUnderflow(uint64_t uid, int32_t restoreId, const char* fileId, int32_t line)
{
    CONTAINER_SCOPED_LOGE("STACK_UNDERFLOW: POP uid=%" PRIu64 " not found at %s:%d,"
                          " restoreId=%d, currentId=%d,"
                          " activeStackDepth=%zu, stackTop=%s",
        uid, (fileId ? fileId : "unknown"), line, restoreId, currentId_, activeOrder_.size(),
        activeOrder_.empty() ? "(empty)" : std::to_string(activeOrder_.back()).c_str());
    CurrentIdStackFrame orphanFrame;
    orphanFrame.uid = uid;
    orphanFrame.popFileId = fileId;
    orphanFrame.popLine = line;
    orphanFrame.oldValue = restoreId;
    orphanFrame.newValue = currentId_;
    orphanFrame.anomalies |= FrameAnomaly::STACK_UNDERFLOW;
    orphanFrame.anomalyDetailKind = AnomalyDetailKind::POP_UID_NO_MATCHING_PUSH;
    if (history_.size() >= maxHistorySize_) {
        history_.pop_front();
    }
    history_.push_back(std::move(orphanFrame));
}

void PopCurrentMatched(uint64_t uid, int32_t restoreId, const char* fileId, int32_t line,
    std::unordered_map<uint64_t, CurrentIdStackFrame>::iterator it)
{
    auto& frame = it->second;
    frame.popFileId = fileId;
    frame.popLine = line;
    if (uid != activeOrder_.back()) {
        auto orderIt = std::find(activeOrder_.begin(), activeOrder_.end(), uid);
        auto distance = std::distance(orderIt + 1, activeOrder_.end());
        frame.skippedCount = static_cast<uint32_t>(distance);
        frame.expectedTopUid = activeOrder_.back();
        frame.anomalies |= FrameAnomaly::OUT_OF_ORDER_POP;
        frame.anomalyDetailKind = AnomalyDetailKind::OUT_OF_ORDER_POP_DYNAMIC;
        uint32_t toSkip =
            std::min(static_cast<uint32_t>(distance), static_cast<uint32_t>(CurrentIdStackFrame::MAX_SKIPPED_UIDS));
        for (uint32_t i = 0; i < toSkip; ++i) {
            frame.skippedUids[i] = *(orderIt + 1 + i);
        }
        CONTAINER_SCOPED_LOGE("OUT_OF_ORDER_POP: POP uid=%" PRIu64 " at %s:%d,"
                              " expected top=%" PRIu64,
            uid, (fileId ? fileId : "unknown"), line, activeOrder_.back());
    }
    if (restoreId != frame.oldValue) {
        frame.anomalies |= FrameAnomaly::VALUE_MISMATCH;
        frame.anomalyDetailKind = AnomalyDetailKind::POP_VALUE_MISMATCH;
        CONTAINER_SCOPED_LOGE("VALUE_MISMATCH: uid=%" PRIu64 " PUSH saved %d at %s:%d,"
                              " but POP restoring to %d at %s:%d,"
                              " stackDepth=%zu",
            uid, frame.oldValue, (frame.pushFileId ? frame.pushFileId : "unknown"), frame.pushLine, restoreId,
            (fileId ? fileId : "unknown"), line, activeOrder_.size());
    }
    frame.anomalies &= ~FrameAnomaly::UNPAIRED_PUSH;

    if (history_.size() >= maxHistorySize_) {
        history_.pop_front();
    }
    history_.push_back(std::move(frame));
    activeStack_.erase(it);
    auto orderIt = std::find(activeOrder_.begin(), activeOrder_.end(), uid);
    if (orderIt != activeOrder_.end()) {
        activeOrder_.erase(orderIt);
    }

    CONTAINER_SCOPED_LOGD("POP uid=%" PRIu64 " restore %d->%d stackDepth=%zu"
                          " at %s:%d",
        uid, currentId_, restoreId, activeOrder_.size(), (fileId ? fileId : "unknown"), line);
}

struct AnomalyCounts {
    uint32_t outOfOrder = 0;
    uint32_t underflow = 0;
    uint32_t mismatch = 0;
    uint32_t unpaired = 0;
};

AnomalyCounts CountHistoryAnomalies()
{
    AnomalyCounts counts;
    for (const auto& f : history_) {
        if ((f.anomalies & FrameAnomaly::OUT_OF_ORDER_POP) != 0) {
            counts.outOfOrder++;
        }
        if ((f.anomalies & FrameAnomaly::STACK_UNDERFLOW) != 0) {
            counts.underflow++;
        }
        if ((f.anomalies & FrameAnomaly::VALUE_MISMATCH) != 0) {
            counts.mismatch++;
        }
        if ((f.anomalies & FrameAnomaly::UNPAIRED_PUSH) != 0) {
            counts.unpaired++;
        }
    }
    return counts;
}

void AppendAnomalySummary(std::ostringstream& oss, const AnomalyCounts& counts)
{
    uint32_t anomalyCount = counts.outOfOrder + counts.underflow + counts.mismatch + counts.unpaired;
    oss << "History: " << history_.size() << " frames (" << anomalyCount << " with anomalies)\n";

    if (anomalyCount > 0) {
        if (counts.outOfOrder > 0) {
            oss << "  - OUT_OF_ORDER_POP: " << counts.outOfOrder << " instances\n";
        }
        if (counts.underflow > 0) {
            oss << "  - STACK_UNDERFLOW: " << counts.underflow << " instances\n";
        }
        if (counts.mismatch > 0) {
            oss << "  - VALUE_MISMATCH: " << counts.mismatch << " instances\n";
        }
        if (counts.unpaired > 0) {
            oss << "  - UNPAIRED_PUSH: " << counts.unpaired << " instances\n";
        }
    }
}

std::string CurrentIdStackFrame::ToString() const
{
    std::ostringstream oss;
    oss << "Frame[uid=" << uid << ", parent=" << (parentUid == 0 ? "root" : std::to_string(parentUid)) << ", "
        << oldValue << "->" << newValue;
    oss << ", push=" << (pushFileId ? pushFileId : "unknown") << ":" << pushLine;
    if (popFileId != nullptr) {
        oss << ", pop=" << popFileId << ":" << popLine;
    }
    oss << ", type=" << sourceType;
    if (anomalies != FrameAnomaly::NONE) {
        oss << ", anomalies=";
        if ((anomalies & FrameAnomaly::UNPAIRED_PUSH) != 0u) {
            oss << "UNPAIRED_PUSH|";
        }
        if ((anomalies & FrameAnomaly::STACK_UNDERFLOW) != 0u) {
            oss << "STACK_UNDERFLOW|";
        }
        if ((anomalies & FrameAnomaly::VALUE_MISMATCH) != 0u) {
            oss << "VALUE_MISMATCH|";
        }
        if ((anomalies & FrameAnomaly::OUT_OF_ORDER_POP) != 0u) {
            oss << "OUT_OF_ORDER_POP|";
        }
    }
    if (anomalyDetailKind != AnomalyDetailKind::NONE) {
        if (anomalyDetailKind == AnomalyDetailKind::OUT_OF_ORDER_POP_DYNAMIC) {
            oss << ", detail=POP(uid=" << uid << ") not top; expected=" << expectedTopUid << ", skipped "
                << skippedCount << " frames";
            for (uint32_t i = 0; i < skippedCount && i < MAX_SKIPPED_UIDS; i++) {
                oss << (i == 0 ? " [" : ", ") << "uid=" << skippedUids[i];
            }
            if (skippedCount > 0) {
                oss << "]";
            }
        } else {
            oss << ", detail=" << AnomalyDetailKindToStr(anomalyDetailKind);
        }
    }
    oss << "]";
    return oss.str();
}
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
void* ContainerScope::registerHandler_ = nullptr;
ContainerScope::ReportScopeErrorFun ContainerScope::reportScopeError_ = nullptr;

void ContainerScope::ReportScopeError()
{
    if (reportScopeError_ != nullptr) {
        reportScopeError_();
        return;
    }
    registerHandler_ = dlopen("libace_compatible.z.so", RTLD_LAZY);
    reportScopeError_ = (ReportScopeErrorFun)dlsym(registerHandler_, "OHOS_ACE_ScopeErrorHivewReport");
    reportScopeError_();
}

void ContainerScope::CheckIdChange(int32_t id)
{
    if (id < 0) {
        return;
    }
    auto safeId = SafelyId();
    if (id != safeId) {
        ReportScopeError();
    }
}
#endif

int32_t ContainerScope::CurrentId()
{
    return currentId_;
}

void ContainerScope::UpdateLocalCurrent(int32_t id)
{
    currentLocalId_ = id;
}

int32_t ContainerScope::CurrentLocalId()
{
    return currentLocalId_;
}

int32_t ContainerScope::DefaultId()
{
    if (ContainerCount() > 0) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return *containerSet_.rbegin();
    }
    return INSTANCE_ID_UNDEFINED;
}

int32_t ContainerScope::SingletonId()
{
    if (ContainerCount() != 1) {
        return INSTANCE_ID_UNDEFINED;
    }
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return *containerSet_.begin();
}

int32_t ContainerScope::RecentActiveId()
{
    return recentActiveId_.load(std::memory_order_relaxed);
}

int32_t ContainerScope::RecentForegroundId()
{
    return recentForegroundId_.load(std::memory_order_relaxed);
}

int32_t ContainerScope::SafelyId()
{
    uint32_t containerCount = ContainerCount();
    if (containerCount == 0) {
        return INSTANCE_ID_UNDEFINED;
    }
    if (containerCount == 1) {
        return SingletonId();
    }
    int32_t currentId = RecentActiveId();
    if (currentId >= 0) {
        return currentId;
    }
    currentId = RecentForegroundId();
    if (currentId >= 0) {
        return currentId;
    }
    return DefaultId();
}

std::pair<int32_t, InstanceIdGenReason> ContainerScope::CurrentIdWithReason()
{
    int32_t currentId = CurrentId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::SCOPE };
    }
    uint32_t containerCount = ContainerCount();
    if (containerCount == 0) {
        return { INSTANCE_ID_UNDEFINED, InstanceIdGenReason::UNDEFINED };
    }
    if (containerCount == 1) {
        return { SingletonId(), InstanceIdGenReason::SINGLETON };
    }
    currentId = ContainerScope::RecentActiveId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::ACTIVE };
    }
    currentId = ContainerScope::RecentForegroundId();
    if (currentId >= 0) {
        return { currentId, InstanceIdGenReason::FOREGROUND };
    }
    return { ContainerScope::DefaultId(), InstanceIdGenReason::DEFAULT };
}

const std::string ContainerScope::ReasonToDescription(InstanceIdGenReason reason)
{
    switch (reason) {
        case InstanceIdGenReason::SCOPE:
            return "The instance is determined by the caller";
        case InstanceIdGenReason::ACTIVE:
            return "No specific instance was specified, so the most recently active instance was retrieved";
        case InstanceIdGenReason::DEFAULT:
            return "No specific instance was specified, using default";
        case InstanceIdGenReason::SINGLETON:
            return "No specific instance was specified, return the only remaining instance";
        case InstanceIdGenReason::FOREGROUND:
            return "No specific instance was specified, return the foreground instance";
        case InstanceIdGenReason::UNDEFINED:
            return "No valid instance exists";
        default:
            return "Unknown reason";
    }
}

const std::set<int32_t> ContainerScope::GetAllUIContexts()
{
    return containerSet_;
}

void ContainerScope::UpdateCurrent(int32_t id)
{
    currentId_ = id;
}

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
uint64_t ContainerScope::PushCurrent(int32_t id, const char* fileId, int32_t line, int32_t sourceType)
{
    uint64_t uid = 0;
    if (trackingEnabled_) {
        uid = nextUid_++;

        CurrentIdStackFrame frame;
        frame.uid = uid;
        frame.parentUid = activeOrder_.empty() ? 0 : activeOrder_.back();
        frame.pushFileId = fileId;
        frame.pushLine = line;
        frame.oldValue = currentId_;
        frame.newValue = id;
        frame.sourceType = sourceType;

        if (sourceType == static_cast<int32_t>(CurrentIdSourceType::CONTAINER_INDIRECT)) {
            frame.anomalies |= FrameAnomaly::UNPAIRED_PUSH;
            frame.anomalyDetailKind = AnomalyDetailKind::CONTAINER_INIT_NO_POP;
        }

        activeStack_.emplace(uid, std::move(frame));
        activeOrder_.push_back(uid);
        CONTAINER_SCOPED_LOGD("PUSH uid=%" PRIu64 " %d->%d stackDepth=%zu"
                              " at %s:%d",
            uid, currentId_, id, activeOrder_.size(), (fileId ? fileId : "unknown"), line);
    }
    currentId_ = id;
    return uid;
}

void ContainerScope::PopCurrent(uint64_t uid, int32_t restoreId, const char* fileId, int32_t line, int32_t sourceType)
{
    if (trackingEnabled_) {
        auto it = activeStack_.find(uid);
        if (uid == 0 || it == activeStack_.end()) {
            PopCurrentStackUnderflow(uid, restoreId, fileId, line);
        } else {
            PopCurrentMatched(uid, restoreId, fileId, line, it);
        }
    }
    currentId_ = restoreId;
}

std::vector<CurrentIdStackFrame> ContainerScope::GetStackHistory()
{
    return { history_.begin(), history_.end() };
}

std::vector<CurrentIdStackFrame> ContainerScope::GetActiveFrames()
{
    std::vector<CurrentIdStackFrame> result;
    result.reserve(activeOrder_.size());
    for (auto uid : activeOrder_) {
        auto it = activeStack_.find(uid);
        if (it != activeStack_.end()) {
            result.push_back(it->second);
        }
    }
    return result;
}

void ContainerScope::ClearHistory()
{
    history_.clear();
    activeStack_.clear();
    activeOrder_.clear();
}

void ContainerScope::EnableTracking(bool enable)
{
    trackingEnabled_ = enable;
}

bool ContainerScope::IsTrackingEnabled()
{
    return trackingEnabled_;
}

void ContainerScope::SetMaxHistorySize(size_t size)
{
    maxHistorySize_ = size;
}

bool ContainerScope::IsStackBalanced()
{
    return activeStack_.empty();
}

std::string ContainerScope::Diagnose()
{
    std::ostringstream oss;
    oss << "=== currentId_ Stack Diagnosis ===\n"
        << "Current value: " << currentId_ << "\n"
        << "Active frames (top first): " << activeOrder_.size() << "\n";

    int32_t index = 0;
    for (auto rit = activeOrder_.rbegin(); rit != activeOrder_.rend(); ++rit) {
        auto frameIt = activeStack_.find(*rit);
        if (frameIt == activeStack_.end()) {
            continue;
        }
        const auto& f = frameIt->second;
        index++;
        oss << "  #" << index << " " << f.ToString() << "\n"
            << "      parent: " << (f.parentUid == 0 ? "none (root)" : "uid=") << f.parentUid << "\n";
    }

    auto counts = CountHistoryAnomalies();
    AppendAnomalySummary(oss, counts);

    oss << "Stack balanced: " << (activeOrder_.empty() ? "YES" : "NO") << "\n";
    return oss.str();
}
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

void ContainerScope::UpdateRecentActive(int32_t id)
{
    recentActiveId_.store(id, std::memory_order_relaxed);
}

void ContainerScope::UpdateRecentForeground(int32_t id)
{
    recentForegroundId_.store(id, std::memory_order_relaxed);
}

uint32_t ContainerScope::ContainerCount()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<uint32_t>(containerSet_.size());
}

void ContainerScope::Add(int32_t id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    containerSet_.emplace(id);
}

void ContainerScope::Remove(int32_t id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    containerSet_.erase(id);
}

void ContainerScope::RemoveAndCheck(int32_t id)
{
    Remove(id);
    if (RecentActiveId() == id) {
        UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    }
    if (RecentForegroundId() == id) {
        UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    }
}

ContainerScope::ContainerScope(int32_t id)
{
    UpdateCurrent(id);
}

ContainerScope::ContainerScope(int32_t id, bool enable)
{
    if (enable) {
#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
        CheckIdChange(id);
#endif
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
        pushedUid_ = PushCurrent(id, nullptr, DEFAULT_ID, static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
        pushed_ = true;
#else
        UpdateCurrent(id);
#endif
    }
}

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
ContainerScope::ContainerScope(int32_t id, const char* fileId, int32_t line)
    : pushedUid_(PushCurrent(id, fileId, line, static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE))), pushed_(true)
{}

ContainerScope::ContainerScope(int32_t id, bool enable, const char* fileId, int32_t line) : pushed_(false)
{
    if (enable) {
#if defined(NAPI_SCOPE_ERROR_HIVEW_REPORT)
        CheckIdChange(id);
#endif
        pushedUid_ = PushCurrent(id, fileId, line, static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
        pushed_ = true;
    }
}
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

ContainerScope::~ContainerScope()
{
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
    if (pushed_) {
        PopCurrent(pushedUid_, restoreId_, nullptr, DEFAULT_ID, static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    } else {
        UpdateCurrent(restoreId_);
    }
#else
    UpdateCurrent(restoreId_);
#endif
}
} // namespace OHOS::Ace
