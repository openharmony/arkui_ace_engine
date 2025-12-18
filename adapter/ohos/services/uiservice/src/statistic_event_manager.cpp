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

#include "common_statistic_event.h"
#include "parameter.h"
#include "parameters.h"
#include "ui_service_hilog.h"
namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t DEFAULT_INTERVAL = 24;
constexpr int32_t ONE_HOUR_INTERVAL = 60* 60* 1000;
constexpr int32_t MAX_EVENT_NAME_LENGTH = 100;
constexpr int32_t MAX_EVENT_MAP_SIZE = 500;
} // namespace

StatisticEventManager::StatisticEventManager() {}

StatisticEventManager::~StatisticEventManager() {}

void StatisticEventManager::SendStatisticEvents(const AppInfoParcel& appInfo,
    const std::vector<StatisticEventInfoParcel>& eventInfos)
{
    for (auto& eventInfo : eventInfos) {
        std::string eventName = eventInfo.GetEventName();
        std::string subEventName = eventInfo.GetSubEventName();
        LOGD("SendStatisticEvent eventName: %{public}s, subEventName: %{public}s, \
            eventCount: %{public}d, bundleName: %{public}s",
            eventName.c_str(), subEventName.c_str(), eventInfo.GetEventCount(), appInfo.GetBundleName().c_str());
        if (eventName.size() > MAX_EVENT_NAME_LENGTH || subEventName.size() > MAX_EVENT_NAME_LENGTH) {
            LOGE("invalid event, event name length is too long");
            continue;
        }
        bool isReported = false;
        auto iter = eventMap_.find(eventName);
        if (iter == eventMap_.end()) {
            if (eventMap_.size() >= MAX_EVENT_MAP_SIZE) {
                LOGE("invalid event, eventMap is oversize");
                continue;
            }
            StatisticEvent statisticEvent(eventName);
            isReported = statisticEvent.AggregateEvent(appInfo, eventInfo);
            eventMap_.emplace(eventName, statisticEvent);
        } else {
            isReported = iter->second.AggregateEvent(appInfo, eventInfo);
        }
        if (isReported) {
            eventMap_.erase(eventName);
        }
    }
}

void StatisticEventManager::StartTimedEvent()
{
    for (auto& interval : timedSet_) {
        PostTimedEvent(interval);
    }
}

bool StatisticEventManager::NeedReportEvent(
    const StatisticEvent& statisticEvent, int32_t interval) const
{
    if (statisticEvent.GetReportInterval() == 0 && interval == defaultReportInterval_) {
        return true;
    }
    if (statisticEvent.GetReportInterval() == interval) {
        return true;
    }
    return false;
}

void StatisticEventManager::ReportTimedStatisticEvent(int32_t interval)
{
    for (auto it = eventMap_.begin(); it != eventMap_.end();) {
        auto statisticEvent = it->second;
        if (NeedReportEvent(statisticEvent, interval)) {
            statisticEvent.ReportEvent();
            it = eventMap_.erase(it);
        } else {
            ++it;
        }
    }
}

void StatisticEventManager::PostTimedEvent(int32_t interval)
{
    handler_->PostTask([interval]() {
        DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(interval);
        DelayedSingleton<StatisticEventManager>::GetInstance()->PostTimedEvent(interval);
        }, interval);
}


void StatisticEventManager::InitTimedMap()
{
    timedSet_.insert(defaultReportInterval_);
    // define custom event report interval in timedSet_ and customEventReportInterval_.
}

void StatisticEventManager::Init(std::shared_ptr<EventHandler>& handler)
{
    if (handler == nullptr) {
        return;
    }
    handler_ = handler;
    defaultReportInterval_ =
        system::GetIntParameter("persist.ace.default_report_interval", DEFAULT_INTERVAL * ONE_HOUR_INTERVAL);
    InitTimedMap();
    StartTimedEvent();
}
} // namespace Ace
} // namespace OHOS