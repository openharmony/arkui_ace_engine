/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/log/jank_frame_report.h"
#include "base/perfmonitor/perf_monitor.h"

namespace OHOS::Ace {
JankFrameReport& JankFrameReport::GetInstance()
{
    static thread_local JankFrameReport instance;
    return instance;
}

JankFrameReport::JankFrameReport() {}

void JankFrameReport::JankFrameRecord(int64_t timeStampNanos, const std::string& windowName) {}

void JankFrameReport::SetFrameJankFlag(JankFrameFlag flag) {}

void JankFrameReport::ClearFrameJankFlag(JankFrameFlag flag) {}

void JankFrameReport::StartRecord(const std::string& pageUrl) {}

void JankFrameReport::FlushRecord() {}

void JankFrameReport::RecordFrameUpdate() {}

PerfMonitor* PerfMonitor::GetPerfMonitor()
{
    return nullptr;
}

void PerfMonitor::Start(const std::string& sceneId, PerfActionType type, const std::string& note) {}

void PerfMonitor::End(const std::string& sceneId, bool isJsApi) {}

void PerfMonitor::SetPageUrl(const std::string& pageUrl) {}

void PerfMonitor::SetFrameTime(int64_t vsyncTime, int64_t durition, double jank, const std::string& windowName) {}

void PerfMonitor::ReportJankFrameApp(double jank) {}

void PerfMonitor::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time) {}

int64_t PerfMonitor::GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    return 0;
}

std::string PerfMonitor::GetPageUrl()
{
    return "";
}

void PerfMonitor::SetAppForeground(bool isShow) {}

void PerfMonitor::SetAppStartStatus() {}
void PerfMonitor::SetPageName(const std::string& pageName) {}
void PerfMonitor::ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
                                    const std::string& pageName) {}
} // namespace OHOS::Ace
