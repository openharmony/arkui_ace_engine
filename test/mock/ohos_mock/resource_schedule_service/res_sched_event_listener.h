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
#ifndef RES_SCHED_EVENT_LISTENER_H
#define RES_SCHED_EVENT_LISTENER_H

#include <cstdint>
#include <string>

namespace OHOS {
namespace ResourceSchedule {
class ResSchedEventListener  {
public:
    ResSchedEventListener() = default;
    virtual ~ResSchedEventListener() = default;
    virtual void OnReceiveEvent(uint32_t eventType, uint32_t eventValue,
        std::unordered_map<std::string, std::string> extInfo) = 0;
};
} // namespace ResourceSchedule
} // namespace OHOS
#endif // RES_SCHED_EVENT_LISTENER_H
