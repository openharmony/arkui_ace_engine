/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <dlfcn.h>

#include "base/ressched/ressched_report.h"
#include <unistd.h>
#include <sys/syscall.h>
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "native_engine/impl/ark/ark_native_engine.h"

namespace OHOS::Ace {
namespace {
const std::string RES_SCHED_CLIENT_SO = "libressched_client.z.so";
const std::string SMART_GC_SO = "libsmart_gc_plugin.z.so";
}

void NotifyForceExpandStateFunc(int32_t state, bool isTid, uint64_t tid)
{
    auto engine = EngineHelper::GetCurrentEngineSafely();
    CHECK_NULL_VOID(engine);
    auto nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    if (isTid) {
        nativeEngine->NotifyForceExpandState(tid, state);
    } else {
        nativeEngine->NotifyForceExpandState(state);
    }
}

ReportDataFunc LoadReportDataFunc()
{
    auto handle = dlopen(RES_SCHED_CLIENT_SO.c_str(), RTLD_NOW);
    CHECK_NULL_RETURN(handle, nullptr);
    auto func = reinterpret_cast<ReportDataFunc>(dlsym(handle, "ReportData"));
    if (func == nullptr) {
        LOGW("dlsym function ReportData failed!");
        dlclose(handle);
        return nullptr;
    }
    LOGI("dlsym function ReportData success.");
    return func;
}

ReportSyncEventFunc LoadReportSyncEventFunc()
{
    auto handle = dlopen(RES_SCHED_CLIENT_SO.c_str(), RTLD_NOW);
    CHECK_NULL_RETURN(handle, nullptr);
    auto func = reinterpret_cast<ReportSyncEventFunc>(dlsym(handle, "ReportSyncEvent"));
    if (func == nullptr) {
        LOGW("dlsym function ReportSyncEvent failed!");
        dlclose(handle);
        return nullptr;
    }
    LOGI("dlsym function ReportSyncEvent success.");
    return func;
}

SetNotifyForceExpandStateFunc LoadSetNotifyForceExpandStateFunc()
{
    auto handle = dlopen(SMART_GC_SO.c_str(), RTLD_NOW);
    CHECK_NULL_RETURN(handle, nullptr);
    auto func = reinterpret_cast<SetNotifyForceExpandStateFunc>(dlsym(handle, "SetNotifyForceExpandStateFunc"));
    if (func == nullptr) {
        LOGW("dlsym function SetNotifyForceExpandStateFunc failed!");
        dlclose(handle);
        return nullptr;
    }
    LOGI("dlsym function SetNotifyForceExpandStateFunc success.");
    return func;
}

NotifyAppSceneFunc LoadNotifyAppSceneFunc()
{
    auto handle = dlopen(SMART_GC_SO.c_str(), RTLD_NOW);
    CHECK_NULL_RETURN(handle, nullptr);
    auto func = reinterpret_cast<NotifyAppSceneFunc>(dlsym(handle, "NotifyAppSceneFunc"));
    if (func == nullptr) {
        LOGW("dlsym function NotifyAppSceneFunc failed!");
        dlclose(handle);
        return nullptr;
    }
    LOGI("dlsym function NotifyAppSceneFunc success.");
    return func;
}

int64_t ResSchedReport::GetTid()
{
    return gettid();
}

int64_t ResSchedReport::GetPid()
{
    return getpid();
}

pthread_t ResSchedReport::GetPthreadSelf()
{
    return pthread_self();
}
} // namespace OHOS::Ace
