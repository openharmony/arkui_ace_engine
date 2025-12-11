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

#ifndef OHOS_ACE_UI_SERVICE_STATISTIC_EVENT_MANAGER_H
#define OHOS_ACE_UI_SERVICE_STATISTIC_EVENT_MANAGER_H

#include <memory>
#include <singleton.h>
#include <list>
#include <set>

#include "event_handler.h"
#include "event_runner.h"
#include "ui_service_statistic_event.h"

namespace OHOS {
namespace Ace {
using EventHandler = OHOS::AppExecFwk::EventHandler;
struct StatisticEvent {
    std::string eventName;
    std::vector<int32_t> eventCounts;
    std::vector<std::string> bundleNames;
};

class StatisticEventManager final {
    DECLARE_DELAYED_SINGLETON(StatisticEventManager)
public:
    void SendStatisticEvents(const AppInfoParcel& appInfo, const std::vector<StatisticEventInfoParcel>& eventInfos);
    void PostTimedEvent(int32_t interval);
    void ReportTimedStatisticEvent(int32_t interval);
    void Init(std::shared_ptr<EventHandler>& handler);
private:
    void InitTimedMap();
    void InitReporter();
    void StartTimedEvent();
    void ReportStatisticEvent(StatisticEvent& event);
    void ReportCommonStatistiEvent(StatisticEvent& event);
    void ReportDefaultTimedStatisticEvents();
    void ReportCustomTimedStatisticEvents(int32_t interval);
    void AggregateEvent(StatisticEvent& event,
        const AppInfoParcel& newAppInfo, const StatisticEventInfoParcel& newEventInfo);

    int32_t defaultReportInterval_ = 1;
    std::shared_ptr<EventHandler> handler_;
    std::set<int32_t> timedSet_;
    std::map<std::string, StatisticEvent> eventMap_;
    std::map<std::string, int32_t> customEventReportInterval_;
    using ReporterFunc = void (StatisticEventManager::*)(StatisticEvent& event);
    std::map<std::string, ReporterFunc> customEventReportFunc_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_ACE_UI_SERVICE_STATISTIC_EVENT_MANAGER_H