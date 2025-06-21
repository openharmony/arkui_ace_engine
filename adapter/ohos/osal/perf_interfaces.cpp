/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/perfmonitor/perf_interfaces.h"

#include "core/common/ace_application_info.h"
#include "perf_monitor_adapter.h"
#include "xcollie/watchdog.h"

namespace OHOS::Ace {

using PerfMonitorAdapter = OHOS::HiviewDFX::PerfMonitorAdapter;

OHOS::HiviewDFX::AceAppInfo GetAceAppInfo()
{
    OHOS::HiviewDFX::AceAppInfo appInfo;
    appInfo.pid = AceApplicationInfo::GetInstance().GetPid();
    appInfo.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    appInfo.versionCode = static_cast<int32_t>(AceApplicationInfo::GetInstance().GetAppVersionCode());
    appInfo.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    appInfo.processName = AceApplicationInfo::GetInstance().GetProcessName();
    appInfo.abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    return appInfo;
}

void PerfInterfaces::SetScrollState(bool state)
{
    OHOS::HiviewDFX::Watchdog::GetInstance().SetScrollState(state);
}

void PerfInterfaces::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time)
{
    HiviewDFX::PerfActionType dfxType = static_cast<HiviewDFX::PerfActionType>(static_cast<int>(type));
    HiviewDFX::PerfSourceType dfxSourceType = static_cast<HiviewDFX::PerfSourceType>(static_cast<int>(sourceType));
    PerfMonitorAdapter::GetInstance().RecordInputEvent(dfxType, dfxSourceType, time);
}

int64_t PerfInterfaces::GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    HiviewDFX::PerfActionType dfxType = static_cast<HiviewDFX::PerfActionType>(static_cast<int>(type));
    return PerfMonitorAdapter::GetInstance().GetInputTime(sceneId, dfxType, note);
}

void PerfInterfaces::NotifyAppJankStatsBegin()
{
    PerfMonitorAdapter::GetInstance().NotifyAppJankStatsBegin();
}

void PerfInterfaces::NotifyAppJankStatsEnd()
{
    PerfMonitorAdapter::GetInstance().NotifyAppJankStatsEnd();
}

void PerfInterfaces::SetPageUrl(const std::string& pageUrl)
{
    PerfMonitorAdapter::GetInstance().SetPageUrl(pageUrl);
}

std::string PerfInterfaces::GetPageUrl()
{
    return PerfMonitorAdapter::GetInstance().GetPageUrl();
}

void PerfInterfaces::SetPageName(const std::string& pageName)
{
    PerfMonitorAdapter::GetInstance().SetPageName(pageName);
}

std::string PerfInterfaces::GetPageName()
{
    return PerfMonitorAdapter::GetInstance().GetPageName();
}

void PerfInterfaces::SetAppForeground(bool isShow)
{
    PerfMonitorAdapter::GetInstance().SetAppForeground(isShow);
}

void PerfInterfaces::SetAppStartStatus()
{
    PerfMonitorAdapter::GetInstance().SetAppStartStatus();
}

bool PerfInterfaces::IsScrollJank(const std::string& sceneId)
{
    return PerfMonitorAdapter::GetInstance().IsScrollJank(sceneId);
}

void PerfInterfaces::Start(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    auto appInfo = GetAceAppInfo();
    PerfMonitorAdapter::GetInstance().SetAppInfo(appInfo);
    HiviewDFX::PerfActionType dfxType = static_cast<HiviewDFX::PerfActionType>(static_cast<int>(type));
    PerfMonitorAdapter::GetInstance().Start(sceneId, dfxType, note);
}

void PerfInterfaces::End(const std::string& sceneId, bool isRsRender)
{
    PerfMonitorAdapter::GetInstance().End(sceneId, isRsRender);
}

void PerfInterfaces::StartCommercial(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    auto appInfo = GetAceAppInfo();
    PerfMonitorAdapter::GetInstance().SetAppInfo(appInfo);
    HiviewDFX::PerfActionType dfxType = static_cast<HiviewDFX::PerfActionType>(static_cast<int>(type));
    PerfMonitorAdapter::GetInstance().StartCommercial(sceneId, dfxType, note);
}

void PerfInterfaces::EndCommercial(const std::string& sceneId, bool isRsRender)
{
    PerfMonitorAdapter::GetInstance().EndCommercial(sceneId, isRsRender);
}

void PerfInterfaces::SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName)
{
    PerfMonitorAdapter::GetInstance().SetFrameTime(vsyncTime, duration, jank, windowName);
}

void PerfInterfaces::SetSubHealthInfo(const std::string& info, const std::string& reason, const int32_t duration)
{
    PerfMonitorAdapter::GetInstance().SetSubHealthInfo(info, reason, duration);
}

void PerfInterfaces::ReportJankFrameApp(double jank, int32_t jankThreshold)
{
    PerfMonitorAdapter::GetInstance().ReportJankFrameApp(jank, jankThreshold);
}

void PerfInterfaces::ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
    const std::string& pageName)
{
    PerfMonitorAdapter::GetInstance().ReportPageShowMsg(pageUrl, bundleName, pageName);
}

void PerfInterfaces::SetApplicationInfo()
{
    auto appInfo = GetAceAppInfo();
    PerfMonitorAdapter::GetInstance().SetAppInfo(appInfo);
}

} // namespace OHOS::Ace
