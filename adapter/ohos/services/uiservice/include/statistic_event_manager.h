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
class StatisticEvent;

class StatisticEventManager final {
    DECLARE_DELAYED_SINGLETON(StatisticEventManager)
public:
    void SendStatisticEvents(const AppInfoParcel& appInfo, const std::vector<StatisticEventInfoParcel>& eventInfos);
    void PostTimedEvent(int32_t interval);
    void ReportTimedStatisticEvent(int32_t interval);
    void Init(std::shared_ptr<EventHandler>& handler);
private:
    void InitTimedMap();
    void StartTimedEvent();
    bool NeedReportEvent(const StatisticEvent& statisticEvent, int32_t interval) const;

    int32_t defaultReportInterval_ = 1;
    std::shared_ptr<EventHandler> handler_;
    std::set<int32_t> timedSet_;
    std::map<std::string, StatisticEvent> eventMap_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_ACE_UI_SERVICE_STATISTIC_EVENT_MANAGER_H