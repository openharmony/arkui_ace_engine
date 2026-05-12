/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_RESSCHED_EVENT_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_RESSCHED_EVENT_LISTENER_H

#ifdef RESOURCE_SCHEDULE_SERVICE_ENABLE
#include <cstdint>
#include <mutex>
#include "res_sched_event_listener.h"

namespace OHOS::Ace {
class ResschedEventListener : public ResourceSchedule::ResSchedEventListener {
public:
    void OnReceiveEvent(uint32_t eventType, uint32_t eventValue,
        std::unordered_map<std::string, std::string> extInfo) override;

    void RegisterToRSS(int32_t windowId, int32_t instanceId);
    void UnRegisterFromRSS(int32_t windowId);

    static sptr<ResschedEventListener> GetInstance();

private:
    void OnComponentPreMake(std::unordered_map<std::string, std::string> extInfo);

    int32_t GetContainerId(int32_t windowId);

    std::mutex mutex_;
    std::unordered_map<int32_t, int32_t> containerMap_;
};
} // namespace OHOS::Ace
#endif // RESOURCE_SCHEDULE_SERVICE_ENABLE
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_RESSCHED_EVENT_LISTENER_H