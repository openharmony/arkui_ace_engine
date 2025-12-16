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
        ReportStatisticEvent(event);
        eventMap_.erase(event.eventName);
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
    for (auto& interval : timedSet_) {
        PostTimedEvent(interval);
    }
}

void StatisticEventManager::ReportDefaultTimedStatisticEvents()
{
    for (auto it = eventMap_.begin(); it != eventMap_.end();) {
        auto iter = customEventReportInterval_.find(it->first);
        if (iter == customEventReportInterval_.end()) {
            ReportStatisticEvent(it->second);
            it = eventMap_.erase(it);
        } else {
            ++it;
        }
    }
}

void StatisticEventManager::ReportCustomTimedStatisticEvents(int32_t interval)
{
    auto iter = timedSet_.find(interval);
    if (iter == timedSet_.end()) {
        return;
    }
    for (auto& [eventName, reportInterval] : customEventReportInterval_) {
        if (reportInterval != interval) {
            continue;
        }
        auto iter = eventMap_.find(eventName);
        if (iter == eventMap_.end()) {
            continue;
        }
        ReportStatisticEvent(iter->second);
        eventMap_.erase(iter);
    }
}

void StatisticEventManager::ReportTimedStatisticEvent(int32_t interval)
{
    if (interval == defaultReportInterval_) {
        ReportDefaultTimedStatisticEvents();
    } else {
        ReportCustomTimedStatisticEvents(interval);
    }
}

void StatisticEventManager::PostTimedEvent(int32_t interval)
{
    handler_->PostTask([interval]() {
        DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(interval);
        DelayedSingleton<StatisticEventManager>::GetInstance()->PostTimedEvent(interval);
        }, interval);
}

void StatisticEventManager::ReportStatisticEvent(StatisticEvent& event)
{
    ReporterFunc requestFunc = &StatisticEventManager::ReportCommonStatistiEvent;
    auto itFunc = customEventReportFunc_.find(event.eventName);
    if (itFunc != customEventReportFunc_.end()) {
        requestFunc = itFunc->second;
    }
    (this->*requestFunc)(event);
}

void StatisticEventManager::ReportCommonStatistiEvent(StatisticEvent& event)
{
    LOGD("ReportCommonStatistiEvent eventName: %{public}s", event.eventName.c_str());
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, "UI_STATISTIC_EVENT",
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_NAME, event.eventName,
        EVENT_COUNT, event.eventCounts,
        BUNDLE_NAME, event.bundleNames);
}

void StatisticEventManager::InitTimedMap()
{
    timedSet_.insert(defaultReportInterval_);
    // define custom event report interval in timedSet_ and customEventReportInterval_.
}

void StatisticEventManager::InitReporter()
{
    // define custom event report function in customEventReportFunc_.
    return;
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