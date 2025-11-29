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

#include "core/common/statistic_event_adapter.h"

#include "base/log/log.h"
#include "core/common/statistic_event_reporter.h"
#ifdef UI_SERVICE_WITH_IDL
#include "ui_service_mgr_client_idl.h"
#endif

namespace OHOS::Ace {
void StatisticEventAdapter::ReportStatisticEvents(
    const StatisticAppInfo& appInfo, const std::map<StatisticEventType, StatisticEventInfo>& events)
{
#ifdef UI_SERVICE_WITH_IDL
    AppInfoParcel appInfoParcel(
        appInfo.bundleName, appInfo.abilityName, appInfo.versionName, appInfo.versionCode);
    std::vector<StatisticEventInfoParcel> eventParcelList;
    for (auto& [eventType, eventInfo] : events) {
        eventParcelList.emplace_back(eventInfo.eventName, eventInfo.eventCount);
    }
    Ace::UIServiceMgrClientIdl::GetInstance()->ReportStatisticEvents(appInfoParcel, eventParcelList);
#else
    TAG_LOGE(AceLogTag::ACE_UI_SERVICE, "ui serivce not implement");
#endif
}
} // namespace OHOS::Ace