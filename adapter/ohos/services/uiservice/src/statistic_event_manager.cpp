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
constexpr int32_t MAX_PENDING_EVENT_COUNT = 10;
constexpr int32_t DEFAULT_INTERVAL = 24;
constexpr int32_t ONE_HOUR_INTERVAL = 60* 60* 1000;
const char* STATISTIC_EVENT_FA_APP_START = "FA_APP_START";
const char* EVENT_NAME = "EVENT_NAME";
const char* EVENT_COUNT = "EVENT_COUNT";
const char* BUNDLE_NAME = "BUNDLE_NAME";
const char* ABILITY_NAME = "ABILITY_NAME";
const char* VERSION_NAME = "VERSION_NAME";
const char* VERSION_CODE = "VERSION_CODE";
} // namespace

StatisticEventManager::StatisticEventManager() {}

StatisticEventManager::~StatisticEventManager() {}

void StatisticEventManager::AggregateEvent(std::vector<StatisticEvent>& events,
    const AppInfoParcel& newAppInfo, const StatisticEventInfoParcel& newEventInfo)
{
    for (auto& event : events) {
        if (!event.appInfo.EqualTo(newAppInfo)) {
            continue;
        }
        event.eventInfo.SetEventCount(event.eventInfo.GetEventCount() + newEventInfo.GetEventCount());
        return;
    }
    StatisticEvent statisticEvent;
    statisticEvent.appInfo = newAppInfo;
    statisticEvent.eventInfo = newEventInfo;
    events.push_back(statisticEvent);

    if (events.size() >= MAX_PENDING_EVENT_COUNT) {
        ReportStatisticEvent(newEventInfo.GetEventName());
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
            StatisticEvent statisticEvent;
            statisticEvent.appInfo = appInfo;
            statisticEvent.eventInfo = eventInfo;
            eventMap_[eventName] = { statisticEvent };
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
    auto events = iter->second;
    for (auto& event : events) {
        (this->*requestFunc)(event);
    }
    eventMap_.erase(iter);
}

void StatisticEventManager::ReportFaAppStartEvent(StatisticEvent& event)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, "UI_SERVICE_STATISTIC_EVENT",
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_NAME, event.eventInfo.GetEventName(),
        EVENT_COUNT, event.eventInfo.GetEventCount(),
        BUNDLE_NAME, event.appInfo.GetBundleName(),
        ABILITY_NAME, event.appInfo.GetAbilityName(),
        VERSION_NAME, event.appInfo.GetVersionName(),
        VERSION_CODE, event.appInfo.GetVersionCode());
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