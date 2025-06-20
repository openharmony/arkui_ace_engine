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

#include "base/perfmonitor/perf_monitor.h"

#include "base/log/event_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_interfaces.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace {
using namespace std;
PerfMonitor* PerfMonitor::pMonitor = nullptr;
std::once_flag PerfMonitor::initFlag;
const int32_t JANK_SKIPPED_THRESHOLD = SystemProperties::GetJankFrameThreshold();
// Obtain the last three digits of the full path
constexpr uint32_t PATH_DEPTH = 3;

std::string ParsePageUrl(const std::string& pagePath)
{
    std::string res;
    std::vector<std::string> paths;
    StringUtils::StringSplitter(pagePath, '/', paths);
    uint32_t pathSize = paths.size();
    if (pathSize < PATH_DEPTH) {
        return pagePath;
    }
    for (uint32_t i = pathSize - PATH_DEPTH; i < pathSize; i++) {
        res = res + "/" + paths[i];
    }
    return res;
}

PerfMonitor* PerfMonitor::GetPerfMonitor()
{
    std::call_once(initFlag, &PerfMonitor::InitInstance);
    return pMonitor;
}

void PerfMonitor::InitInstance()
{
    pMonitor = new PerfMonitor();
}

void PerfMonitor::Start(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    if (PerfInterfaces::IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(true);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, true);
    }
    PerfInterfaces::Start(sceneId, type, note);
    if (sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH) {
        ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_start");
    }
}

void PerfMonitor::StartCommercial(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    if (PerfInterfaces::IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(true);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, true);
    }
    PerfInterfaces::StartCommercial(sceneId, type, note);
}

void PerfMonitor::End(const std::string& sceneId, bool isRsRender)
{
    if (PerfInterfaces::IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(false);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, false);
    }

    PerfInterfaces::End(sceneId, isRsRender);
    if (sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH) {
        ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_end");
    }
}

void PerfMonitor::EndCommercial(const std::string& sceneId, bool isRsRender)
{
    if (PerfInterfaces::IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(false);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, false);
    }

    PerfInterfaces::EndCommercial(sceneId, isRsRender);
}

void PerfMonitor::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time)
{
    PerfInterfaces::RecordInputEvent(type, sourceType, time);
}

void PerfMonitor::SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName)
{
    PerfInterfaces::SetFrameTime(vsyncTime, duration, jank, windowName);
}

void PerfMonitor::SetSubHealthInfo(const std::string& info, const std::string& reason, const int32_t duration)
{
    PerfInterfaces::SetSubHealthInfo(info, reason, duration);
}

void PerfMonitor::ReportJankFrameApp(double jank)
{
    PerfInterfaces::ReportJankFrameApp(jank, JANK_SKIPPED_THRESHOLD);
}

void PerfMonitor::SetPageUrl(const std::string& pageUrl)
{
    std::string newPageUrl = ParsePageUrl(pageUrl);
    PerfInterfaces::SetPageUrl(newPageUrl);
}

std::string PerfMonitor::GetPageUrl()
{
    return PerfInterfaces::GetPageUrl();
}

void PerfMonitor::SetPageName(const std::string& pageName)
{
    PerfInterfaces::SetPageName(pageName);
}

std::string PerfMonitor::GetPageName()
{
    return PerfInterfaces::GetPageName();
}

void PerfMonitor::ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
                                    const std::string& pageName)
{
    std::string newPageUrl = ParsePageUrl(pageUrl);
    PerfInterfaces::ReportPageShowMsg(newPageUrl, bundleName, pageName);
}

int64_t PerfMonitor::GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    return PerfInterfaces::GetInputTime(sceneId, type, note);
}

void PerfMonitor::SetAppStartStatus()
{
    PerfInterfaces::SetAppStartStatus();
}

void PerfMonitor::SetAppForeground(bool isShow)
{
    PerfInterfaces::SetAppForeground(isShow);
}

void PerfMonitor::RecordWindowRectResize(OHOS::Ace::WindowSizeChangeReason reason, const std::string& bundleName)
{
    switch (reason) {
        case OHOS::Ace::WindowSizeChangeReason::DRAG_START:
            PerfInterfaces::Start(PerfConstants::WINDOW_RECT_RESIZE, PerfActionType::LAST_DOWN, bundleName.c_str());
            break;
        case OHOS::Ace::WindowSizeChangeReason::DRAG_END:
            PerfInterfaces::End(PerfConstants::WINDOW_RECT_RESIZE, true);
            break;
        default:
            break;
    }
}

void PerfMonitor::NotifyAppJankStatsBegin()
{
    PerfInterfaces::NotifyAppJankStatsBegin();
}

void PerfMonitor::NotifyAppJankStatsEnd()
{
    PerfInterfaces::NotifyAppJankStatsEnd();
}

void PerfMonitor::SetApplicationInfo()
{
    PerfInterfaces::SetApplicationInfo();
}

void PerfMonitor::SetApsMonitor(const std::shared_ptr<ApsMonitor>& apsMonitor)
{
    apsMonitor_ = apsMonitor;
}

} // namespace OHOS::Ace
