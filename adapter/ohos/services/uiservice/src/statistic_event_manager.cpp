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

#include "statistic_event_manager.h"

#include "parameter.h"
#include "parameters.h"
#include "ui_service_hilog.h"
#include "hisysevent.h"
namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 50;
constexpr int32_t DEFAULT_INTERVAL = 24;
constexpr int32_t ONE_HOUR_INTERVAL = 60* 60* 1000;
const char* STATISTIC_EVENT_FA_APP_START = "FA_APP_START";
const char* EVENT_NAME = "EVENT_NAME";
const char* EVENT_COUNT = "EVENT_COUNT";
const char* BUNDLE_NAME = "BUNDLE_NAME";
} // namespace

StatisticEventManager::StatisticEventManager() {}

StatisticEventManager::~StatisticEventManager() {}

void StatisticEventManager::AggregateEvent(StatisticEvent& event,
    const AppInfoParcel& newAppInfo, const StatisticEventInfoParcel& newEventInfo)
{
    for (size_t i = 0; i < event.bundleNames.size(); ++i) {
        if (event.bundleNames[i] != newAppInfo.GetBundleName()) {
            continue;
        }
        event.eventCounts[i] += newEventInfo.GetEventCount();
        return;
    }
    event.bundleNames.push_back(newAppInfo.GetBundleName());
    event.eventCounts.push_back(newEventInfo.GetEventCount());

    if (event.bundleNames.size() >= MAX_PENDING_EVENT_COUNT) {
        ReportStatisticEvent(event.eventName);
    }
}

void StatisticEventManager::SendStatisticEvents(const AppInfoParcel& appInfo,
    const std::vector<StatisticEventInfoParcel>& eventInfos)
{
    for (auto& eventInfo : eventInfos) {
        std::string eventName = eventInfo.GetEventName();
        LOGD("SendStatisticEvent eventName: %{public}s, eventCount: %{public}d, bundleName: %{public}s",
            eventName.c_str(), eventInfo.GetEventCount(), appInfo.GetBundleName().c_str());
        auto iter = eventMap_.find(eventName);
        if (iter == eventMap_.end()) {
            StatisticEvent statisticEvent = { eventName, { eventInfo.GetEventCount() }, { appInfo.GetBundleName() } };
            eventMap_[eventName] = statisticEvent;
        } else {
            AggregateEvent(iter->second, appInfo, eventInfo);
        }
    }
}

void StatisticEventManager::StartTimedEvent()
{
    for (auto& [interval, eventNames] : timedMap_) {
        PostTimedEvent(interval);
    }
}

void StatisticEventManager::ReportTimedStatisticEvent(uint32_t interval)
{
    auto iter = timedMap_.find(interval);
    if (iter == timedMap_.end()) {
        return;
    }
    for (auto& eventName : iter->second) {
        ReportStatisticEvent(eventName);
    }
}

void StatisticEventManager::PostTimedEvent(uint32_t interval)
{
    handler_->PostTask([interval]() {
        DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(interval);
        DelayedSingleton<StatisticEventManager>::GetInstance()->PostTimedEvent(interval);
        }, interval);
}

void StatisticEventManager::ReportStatisticEvent(const std::string& eventName)
{
    auto itFunc = reporterFuncMap_.find(eventName);
    if (itFunc == reporterFuncMap_.end()) {
        return;
    }
    auto requestFunc = itFunc->second;
    auto iter = eventMap_.find(eventName);
    if (iter == eventMap_.end()) {
        return;
    }
    auto event = iter->second;
    (this->*requestFunc)(event);
    eventMap_.erase(iter);
}

void StatisticEventManager::ReportFaAppStartEvent(StatisticEvent& event)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, "UI_STATISTIC_EVENT",
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_NAME, event.eventName,
        EVENT_COUNT, event.eventCounts,
        BUNDLE_NAME, event.bundleNames);
}

void StatisticEventManager::InitTimedMap()
{
    timedMap_[defaultReportInterval_] = { STATISTIC_EVENT_FA_APP_START };
}

void StatisticEventManager::InitReporter()
{
    reporterFuncMap_[STATISTIC_EVENT_FA_APP_START] = &StatisticEventManager::ReportFaAppStartEvent;
}

void StatisticEventManager::Init(std::shared_ptr<EventHandler>& handler)
{
    if (handler == nullptr) {
        return;
    }
    handler_ = handler;
    defaultReportInterval_ =
        system::GetIntParameter("persist.ace.default_report_interval", DEFAULT_INTERVAL * ONE_HOUR_INTERVAL);
    InitReporter();
    InitTimedMap();
    StartTimedEvent();
}
} // namespace Ace
} // namespace OHOS